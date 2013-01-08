/******************************************************************************
 *
 * clCompAppMain.c
 *
 ***************************** Legal Notice ***********************************
 *
 * This file is autogenerated by OpenClovis IDE, Copyright (C) 2002-2008 by 
 * OpenClovis. All rights reserved.
 *
 ***************************** Description ************************************
 *
 * This file provides a skeleton for writing a SAF aware component.
 *
 * Template Version: 1.0
 *
 *****************************************************************************/

/******************************************************************************
 * Include files needed to compile this file
 *****************************************************************************/

/*
 * POSIX Includes.
 */
#include <assert.h>
#include <errno.h>

/*
 * Basic ASP Includes.
 */
#include <clCommon.h>
#include <clHandleApi.h>

/*
 * ASP Client Includes.
 */
#include <clLogApi.h>

#include <clCpmApi.h>
#include <saAmf.h>
#include <saEvt.h>

#include "clCompAppMain.h"
#include "../ev/ev.h"
#include "../common/common.h"

/******************************************************************************
 * Optional Features
 *****************************************************************************/

/*
 * This template has a few default clprintfs. These can be disabled by
 * changing clprintf to a null function
 */

ClLogStreamHandleT gEvalLogStream = CL_HANDLE_INVALID_VALUE;
#define clprintf(severity, ...)   clAppLog(gEvalLogStream, severity, 10, CL_LOG_AREA_UNSPECIFIED, CL_LOG_CONTEXT_UNSPECIFIED, __VA_ARGS__)

/******************************************************************************
 * Global Variables.
 *****************************************************************************/

pid_t mypid;
SaAmfHandleT amfHandle;
ClBoolT unblockNow = CL_FALSE;

/* csa102: high availability variables */
SaAmfHAStateT  ha_state = 0;            /* HA state           */
int              running = 1;    // run state: 0=suspended, 1=resumed
int              exiting = 0;    // Flag to tell main loop to exit

/* csa112: event channel variables */
SaNameT evtChannelName =
{
    sizeof EVENT_CHANNEL_NAME -1,
    EVENT_CHANNEL_NAME
};
SaEvtChannelHandleT   evtChannelHandle = 0;
SaEvtHandleT          evtLibHandle=0;
SaEvtEventHandleT		  eventHandle=0;

static void  csa112Comp_appEventCallback( SaEvtSubscriptionIdT	subscriptionId, SaEvtEventHandleT     eventHandle, SaSizeT eventDataSize);
ClRcT csa113Comp_PublishEvent();


/* An alternate way too handle the SAF dispatching -- just spawn a thread to handle it */
static void *saAmfDispatchThread(void *arg)
{
    saAmfDispatch (amfHandle, SA_DISPATCH_BLOCKING);
    return NULL;
}


/*
 * Declare other global variables here.
 */

/******************************************************************************
 * Application Life Cycle Management Functions
 *****************************************************************************/

/*
 * main
 * -------------------
 * This function is invoked when the application is to be initialized.
 */

int main(int argc, char *argv[])
{
    SaNameT             appName = {0};
    SaAmfCallbacksT     callbacks;
    SaVersionT          version;
    ClIocPortT          iocPort;
    SaAisErrorT         rc = SA_AIS_OK;

    SaSelectionObjectT dispatch_fd;
    fd_set read_fds;
    
    /*
     * Declare other local variables here.
     */

    /*
     * Get the pid for the process and store it in global variable.
     */

    mypid = getpid();

    /*
     * Initialize and register with CPM. 'version' specifies the
     * version of AMF with which this application would like to
     * interface. 'callbacks' is used to register the callbacks this
     * component expects to receive.
     */

    version.releaseCode  = 'B';
    version.majorVersion = 01;
    version.minorVersion = 01;
    
    callbacks.saAmfHealthcheckCallback          = NULL;
    callbacks.saAmfComponentTerminateCallback   = clCompAppTerminate;
    callbacks.saAmfCSISetCallback               = clCompAppAMFCSISet;
    callbacks.saAmfCSIRemoveCallback            = clCompAppAMFCSIRemove;
    callbacks.saAmfProtectionGroupTrackCallback = NULL;
        
    /*
     * Initialize AMF client library.
     */

    if ( (rc = saAmfInitialize(&amfHandle, &callbacks, &version)) != SA_AIS_OK) 
        goto errorexit;

    FD_ZERO(&read_fds);

    /*
     * Get the AMF dispatch FD for the callbacks
     */
    if ( (rc = saAmfSelectionObjectGet(amfHandle, &dispatch_fd)) != SA_AIS_OK)
        goto errorexit;
    
    FD_SET(dispatch_fd, &read_fds);


    /*
     * Do the application specific initialization here.
     */


    /*
     * Now register the component with AMF. At this point it is
     * ready to provide service, i.e. take work assignments.
     */

    if ( (rc = saAmfComponentNameGet(amfHandle, &appName)) != SA_AIS_OK) 
        goto errorexit;
    if ( (rc = saAmfComponentRegister(amfHandle, &appName, NULL)) != SA_AIS_OK) 
        goto errorexit;

    /* Open the log stream as soon as I've registered with AMF */
    clEvalAppLogStreamOpen((ClCharT *)appName.value, &gEvalLogStream);

    /* Handle the AMF dispatch loop by spawning a thread that does it */
    rc = clOsalTaskCreateDetached("DISPATCH-THREAD", CL_OSAL_SCHED_OTHER, 0, 0, saAmfDispatchThread, NULL);
    if(rc != CL_OK)
    {
        clprintf(CL_LOG_SEV_ERROR, "Dispatch task create failed with rc 0x%x",rc);
        return rc;
    }
    
    /*
     * Print out standard information for this component.
     */

    clEoMyEoIocPortGet(&iocPort);
    
    clprintf (CL_LOG_SEV_INFO, "Component [%.*s] : PID [%d]. Initializing\n", appName.length, appName.value, mypid);
    clprintf (CL_LOG_SEV_INFO, "   IOC Address             : 0x%x\n", clIocLocalAddressGet());
    clprintf (CL_LOG_SEV_INFO, "   IOC Port                : 0x%x\n", iocPort);

    /* csa112: initialize the event client library, open the event channel and subscribe to events */
    if (1)
    {
        const SaEvtCallbacksT evtCallbacks =
        {
            NULL,  /* Event open callback */
            csa112Comp_appEventCallback  /* Event delivery callback */
        };
        SaVersionT  evtVersion = {(ClUint8T)'B', 0x1, 0x1};
        
        rc = saEvtInitialize(&evtLibHandle, &evtCallbacks, &evtVersion);
        if (rc != SA_AIS_OK)
        {
            clprintf(CL_LOG_ERROR, "Failed to init event mechanism [0x%x]\n", rc);
            return rc;
        }
            // Open an event chanel so that we can subscribe to events on that channel
        rc = saEvtChannelOpen(evtLibHandle, &evtChannelName, (SA_EVT_CHANNEL_PUBLISHER | SA_EVT_CHANNEL_SUBSCRIBER | SA_EVT_CHANNEL_CREATE), (SaTimeT)SA_TIME_END, &evtChannelHandle);
        if (rc != SA_AIS_OK)
          {
          clprintf(CL_LOG_SEV_ERROR, "Failure opening event channel [0x%x] at %ld", rc, time(0L));
          goto errorexit;
          }
        
      rc = saEvtEventSubscribe(evtChannelHandle, NULL, 1);
      if (rc != SA_AIS_OK)
      {
        clprintf(CL_LOG_SEV_ERROR, "Failed to subscribe to event channel [0x%x]",rc);
        goto errorexit;
      }
    }

    /*csa113: create an event definition to be published */
    if (1)
    {
        SaNameT publisherName;
        clNameSet((ClNameT*) &publisherName,PUBLISHER_NAME);
        
        rc = saEvtEventAllocate(evtChannelHandle, &eventHandle);
        if (rc != SA_AIS_OK)
        {
            clprintf(CL_LOG_SEV_ERROR, "Failed to allocate event [0x%x]\n", rc);
            assert(0);
        }

        rc = saEvtEventAttributesSet(eventHandle, NULL, 1, 0, &publisherName);
        if (rc != SA_AIS_OK)
        {
            clprintf(CL_LOG_ERROR, "Failed to set event attributes [0x%x]\n",rc);
            assert(0);            
        }
    }
    
    
    while (!exiting)
    {
        /* csa112: If I am active then I'll publish an event.
           Note, any application can publish and event regardless of
           HA state.  This tutorial simply uses HA state so only
           one of the two processes are publishing.
        */
        
    if (running && ha_state == SA_AMF_HA_ACTIVE)
    {
        csa113Comp_PublishEvent();
    }
    
    sleep(1);  /* Keep the event publish rate reasonable for this tutorial*/
    }
    
    /*
     * Do the application specific finalization here.
     */

    /* csa112: close the event channel, finalize the event client library */
    if ((rc = saEvtChannelClose(evtChannelHandle)) != SA_AIS_OK)
    {
        clprintf(CL_LOG_ERROR, "Failed [0x%x] to close event channel", rc);
    }

    if ((rc = saEvtFinalize(evtLibHandle)) != SA_AIS_OK)
    {
        clprintf(CL_LOG_ERROR, "Failed [0x%x] to finalize event library", rc);
    }

    if((rc = saAmfFinalize(amfHandle)) != SA_AIS_OK)
	{
        clprintf (CL_LOG_SEV_ERROR, "AMF finalization error[0x%X]", rc);
	}

    clprintf (CL_LOG_SEV_INFO, "AMF Finalized");
    
    return 0;

errorexit:

    clprintf (CL_LOG_SEV_ERROR, "Component [%.*s] : PID [%d]. Initialization error [0x%x]\n",
              appName.length, appName.value, mypid, rc);

    return -1;
}


/*
 * clCompAppTerminate
 * ------------------
 * This function is invoked when the application is to be terminated.
 */

void clCompAppTerminate(SaInvocationT invocation, const SaNameT *compName)
{
    SaAisErrorT rc = SA_AIS_OK;

    clprintf (CL_LOG_SEV_INFO, "Component [%.*s] : PID [%d]. Terminating\n",
              compName->length, compName->value, mypid);

    
    /*
     * Unregister with AMF and respond to AMF saying whether the
     * termination was successful or not.
     */

    if ( (rc = saAmfComponentUnregister(amfHandle, compName, NULL)) != SA_AIS_OK)
        goto errorexit;

    saAmfResponse(amfHandle, invocation, SA_AIS_OK);

    clprintf (CL_LOG_SEV_INFO, "Component [%.*s] : PID [%d]. Terminated\n",
              compName->length, compName->value, mypid);
    clEvalAppLogStreamClose(gEvalLogStream);

    unblockNow = CL_TRUE;
    
    return;

errorexit:

    clprintf (CL_LOG_SEV_ERROR, "Component [%.*s] : PID [%d]. Termination error [0x%x]\n",
              compName->length, compName->value, mypid, rc);

    return;
}

/*
 * clCompAppStateChange
 * ---------------------
 * This function is invoked to change the state of an EO.
 *
 * WARNING: This function is deprecated, and may not be supported in the future.
 * Usage of this feature is discouraged.
 */

ClRcT clCompAppStateChange(ClEoStateT eoState)
{
    switch (eoState)
    {
        case CL_EO_STATE_SUSPEND:
        {
            clprintf(CL_LOG_SEV_INFO, "csa112: Suspending...");
            running = 0;
            break;
        }

        case CL_EO_STATE_RESUME:
        {
            clprintf(CL_LOG_SEV_INFO, "csa112: Resuming...");
            running = 1;
            break;
        }
        
        default:
        {
            break;
        }
    }
 
    return CL_OK;
}

/*
 * clCompAppHealthCheck
 * --------------------
 * This function is invoked to perform a healthcheck on the application. The
 * health check logic is application specific.
 */

ClRcT clCompAppHealthCheck(ClEoSchedFeedBackT* schFeedback)
{
    /*
     * Add code for application specific health check below. The
     * defaults indicate EO is healthy and polling interval is
     * unaltered.
     */

    
    schFeedback->freq   = CL_EO_DEFAULT_POLL; 
    schFeedback->status = CL_CPM_EO_ALIVE;


    return CL_OK;
}

/******************************************************************************
 * Application Work Assignment Functions
 *****************************************************************************/

/*
 * clCompAppAMFCSISet
 * ------------------
 * This function is invoked when a CSI assignment is made or the state
 * of a CSI is changed.
 */

void clCompAppAMFCSISet(SaInvocationT       invocation,
                        const SaNameT       *compName,
                        SaAmfHAStateT       haState,
                        SaAmfCSIDescriptorT csiDescriptor)
{
    /*
     * Print information about the CSI Set
     */

    clprintf (CL_LOG_SEV_INFO, "Component [%.*s] : PID [%d]. CSI Set Received\n", 
              compName->length, compName->value, mypid);

    clCompAppAMFPrintCSI(csiDescriptor, haState);

    /*
     * Take appropriate action based on state
     */

    switch ( haState )
    {
        case SA_AMF_HA_ACTIVE:
        {
            /*
             * AMF has requested application to take the active HA state 
             * for the CSI.
             */
            clprintf(CL_LOG_SEV_INFO, "csa112: ACTIVE state requested; activating service");
            running = 1;
            ha_state = haState;

            saAmfResponse(amfHandle, invocation, SA_AIS_OK);
            break;
        }

        case SA_AMF_HA_STANDBY:
        {
            /*
             * AMF has requested application to take the standby HA state 
             * for this CSI.
             */
            clprintf(CL_LOG_SEV_INFO, "csa112: State is standby");
            running = 0;
            ha_state = haState;

            saAmfResponse(amfHandle, invocation, SA_AIS_OK);
            break;
        }

        case SA_AMF_HA_QUIESCED:
        {
            /*
             * AMF has requested application to quiesce the CSI currently
             * assigned the active or quiescing HA state. The application 
             * must stop work associated with the CSI immediately.
             */
            clprintf(CL_LOG_SEV_INFO, "csa112: Stop being active or standby");
            running = 0;
            ha_state = haState;

            saAmfResponse(amfHandle, invocation, SA_AIS_OK);
            break;
        }

        case SA_AMF_HA_QUIESCING:
        {
            /*
             * AMF has requested application to quiesce the CSI currently
             * assigned the active HA state. The application must stop work
             * associated with the CSI gracefully and not accept any new
             * workloads while the work is being terminated.
             */
            clprintf(CL_LOG_SEV_INFO, "csa112: Stopping active or standby handling");
            running = 0;
            ha_state = haState;

            saAmfCSIQuiescingComplete(amfHandle, invocation, SA_AIS_OK);
            break;
        }

        default:
        {
            assert(0);
            break;
        }
    }

    return;
}

/*
 * clCompAppAMFCSIRemove
 * ---------------------
 * This function is invoked when a CSI assignment is to be removed.
 */

void clCompAppAMFCSIRemove(SaInvocationT  invocation,
                           const SaNameT  *compName,
                           const SaNameT  *csiName,
                           SaAmfCSIFlagsT csiFlags)
{
    clprintf (CL_LOG_SEV_INFO, "Component [%.*s] : PID [%d]. CSI Remove Received\n", 
              compName->length, compName->value, mypid);

    clprintf (CL_LOG_SEV_INFO, "   CSI                     : %.*s\n", csiName->length, csiName->value);
    clprintf (CL_LOG_SEV_INFO, "   CSI Flags               : 0x%d\n", csiFlags);

    /*
     * Add application specific logic for removing the work for this CSI.
     */

    saAmfResponse(amfHandle, invocation, SA_AIS_OK);

    return;
}

/******************************************************************************
 * Utility functions 
 *****************************************************************************/

/*
 * clCompAppAMFPrintCSI
 * --------------------
 * Print information received in a CSI set request.
 */

void clCompAppAMFPrintCSI(SaAmfCSIDescriptorT csiDescriptor,
                          SaAmfHAStateT haState)
{
    clprintf (CL_LOG_SEV_INFO,
              "CSI Flags : [%s]",
              STRING_CSI_FLAGS(csiDescriptor.csiFlags));

    if (SA_AMF_CSI_TARGET_ALL != csiDescriptor.csiFlags)
    {
        clprintf (CL_LOG_SEV_INFO, "CSI Name : [%s]", 
                  csiDescriptor.csiName.value);
    }

    if (SA_AMF_CSI_ADD_ONE == csiDescriptor.csiFlags)
    {
        ClUint32T i = 0;
        
        clprintf (CL_LOG_SEV_INFO, "Name value pairs :");
        for (i = 0; i < csiDescriptor.csiAttr.number; i++)
        {
            clprintf (CL_LOG_SEV_INFO, "Name : [%s]",
                      csiDescriptor.csiAttr.
                      attr[i].attrName);
            clprintf (CL_LOG_SEV_INFO, "Value : [%s]",
                      csiDescriptor.csiAttr.
                      attr[i].attrValue);
        }
    }
    
    clprintf (CL_LOG_SEV_INFO, "HA state : [%s]",
              STRING_HA_STATE(haState));

    if (SA_AMF_HA_ACTIVE == haState)
    {
        clprintf (CL_LOG_SEV_INFO, "Active Descriptor :");
        clprintf (CL_LOG_SEV_INFO,
                  "Transition Descriptor : [%d]",
                  csiDescriptor.csiStateDescriptor.
                  activeDescriptor.transitionDescriptor);
        clprintf (CL_LOG_SEV_INFO,
                  "Active Component : [%s]",
                  csiDescriptor.csiStateDescriptor.
                  activeDescriptor.activeCompName.value);
    }
    else if (SA_AMF_HA_STANDBY == haState)
    {
        clprintf (CL_LOG_SEV_INFO, "Standby Descriptor :");
        clprintf (CL_LOG_SEV_INFO,
                  "Standby Rank : [%d]",
                  csiDescriptor.csiStateDescriptor.
                  standbyDescriptor.standbyRank);
        clprintf (CL_LOG_SEV_INFO, "Active Component : [%s]",
                  csiDescriptor.csiStateDescriptor.
                  standbyDescriptor.activeCompName.value);
    }
}

/*
 * Insert any other utility functions here.
 */

static void csa112Comp_appEventCallback(SaEvtSubscriptionIdT subscriptionId, SaEvtEventHandleT eventHandle, SaSizeT eventDataSize)
{
    SaAisErrorT     rc = SA_AIS_OK;
    static ClPtrT   resTest = 0;
    
    clprintf(CL_LOG_SEV_INFO,"We've got an event to receive\n");

    /* A high performance implementation would keep the buffer
       if it was big enough for the next event, OR even faster
       preallocate buffer(s) of the the maximum event size which
       can be known by controlling what processes publish to
       a particular event channel.

       This tutorial will simply free an realloc the event buffer.
    */
    if (resTest != 0)
    {
        clHeapFree((char *)resTest);
        resTest = 0;
    }
    resTest = clHeapAllocate(eventDataSize + 1);
    if (resTest == 0)
    {
        clprintf(CL_LOG_SEV_ERROR, "Failed to allocate space for event");
        return;
    }

    /* This API can be used outside of the callback routine, which is why
       you need to pass the size of the buffer you've allocated. */
    rc = saEvtEventDataGet(eventHandle, resTest, &eventDataSize);
    if (rc!= SA_AIS_OK)
    {
        clprintf(CL_LOG_SEV_ERROR, "Failed to get event data [0x%x]",rc);
        return;
    }
    
    /* This tutorial just prints the event.  Rather then rely on the correct
       null termination at the publisher side, I'm going to append a 0 at
       the end before printing it. */
    *(((char *)resTest) + eventDataSize) = 0;
    clprintf(CL_LOG_SEV_INFO,"received event: %s\n", (char *)resTest);
}

static void
generate_time_of_day(char **data, ClSizeT *data_len)
{
    time_t t;

    // minimal error checking
    if (data == 0 || data_len == 0)
    {
        clprintf(CL_LOG_SEV_ERROR, "generate_time_of_day passed null pointer");
        return;
    }

    // magic number, but well, that's what ctime_r needs
    *data_len = 26;
    *data = clHeapAllocate(*data_len);
    if (*data == 0)
    {
        *data_len = 0;
        return;
    }
    time(&t);
    ctime_r(&t, *data);
    *(*data + 24) = 0;
    (*data_len) -= 1;
    return;
}

static void generate_load_average(char **data, ClSizeT *data_len)
{
    int fd;
    char *tmp_ptr;
    char buf[500];                  // insane over doing it
    ssize_t num_read;

    // minimal error checking
    if (data == 0 || data_len == 0)
    {
        clprintf(CL_LOG_SEV_ERROR, "generate_load_average passed null pointer\n ");
        return;
    }
    
    // Now open the load average file in /proc, read the file into a local
    // buffer, allocate memory to hold the file contents, copy the contents
    // of the file into the newly allocated buffer.
    if ((fd = open("/proc/loadavg", O_RDONLY, 0)) == -1)
    {
        clprintf(CL_LOG_SEV_ERROR,"failed to open /proc/loadavg");
        return;
    }

    num_read = read(fd, buf, sizeof buf);
    if (num_read == 0 || num_read == -1)
    {
        clprintf(CL_LOG_SEV_ERROR, "Bogus result from read of loadavg\n");
        return;
    }
    close(fd);
    *data_len = num_read + 1;
    *data = clHeapAllocate(*data_len);
    if (data == 0)
    {
        clprintf(CL_LOG_SEV_ERROR,"Failed to allocate memory for loadavg contents");
        *data_len = 0;
        close(fd);
        return;
    }
    *(*data + (*data_len) - 1) = 0;     // preemptively null-terminate the line
    strncpy(*data, buf, *data_len);

    //
    // Do MINIMAL parsing in that we look for the third space in the buffer
    // (which comes after the load average information proper) and we replace
    // the space with a nul character to terminate the string.
    // If there is no third space character, just return the buffer unchanged.
    tmp_ptr = strchr(*data, ' ');
    if (tmp_ptr == 0)
    {
        return;
    }
    tmp_ptr = strchr(tmp_ptr + 1, ' ');
    if (tmp_ptr == 0)
    {
        return;
    }
    tmp_ptr = strchr(tmp_ptr + 1, ' ');
    if (tmp_ptr == 0)
    {
        return;
    }
    *tmp_ptr = 0;
    return;
}


ClRcT csa113Comp_PublishEvent()
{
    SaEvtEventIdT      eventId         = 0;
    static int      index           = 0;
    SaSizeT         data_len        = 0;
    SaAisErrorT	    rc              = SA_AIS_OK;
    char            *data           = 0;
    typedef void (*Generator)(char **, ClSizeT*);

    //
    // Note: to add a new generator, just define it above and then include
    // the new functions name in the generators list.
    // Next, maybe something that gets disk free info by way of getfsent
    // and statfs?
    static Generator generators[]   =
    {
        generate_time_of_day,
        generate_load_average
    };

    //
    // every time through increment index and then set index to
    // it's value modulo the number of entries in the generators
    // array.  This will cause us to cycle through the list of
    // generators as we're called to publish events.
    (*generators[index++])(&data, &data_len);
    index %= (int)(sizeof generators / sizeof generators[0]);
    if (data == 0 || data_len == 0)
    {
        clprintf(CL_LOG_SEV_ERROR, "No event data generated.");
        return CL_ERR_NO_MEMORY;
    }
    clprintf(CL_LOG_SEV_INFO,"Publishing Event: %.*s\n",(int)data_len, data);
    rc = saEvtEventPublish(eventHandle, (void *)data, data_len, &eventId);
    if (rc != SA_AIS_OK)
    {
        clprintf(CL_LOG_SEV_ERROR,"Event publish attempt failed with error [%x]", rc);
    }
    clHeapFree(data);

    return CL_OK;
}

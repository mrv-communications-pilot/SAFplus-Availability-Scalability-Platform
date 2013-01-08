/******************************************************************************
 *
 * clCompAppProv.c
 *
 ***************************** Legal Notice ***********************************
 *
 * This file is autogenerated by OpenClovis IDE, Copyright (C) 2002-2008 by 
 * OpenClovis. All rights reserved.
 *
 ***************************** Description ************************************
 *
 * This file provides a skeleton for writing a SAF aware component. Application
 * specific code should be added between the ---BEGIN_APPLICATION_CODE--- and
 * ---END_APPLICATION_CODE--- separators.
 *
 * Template Version: 1.0
 *
 ***************************** Editor Commands ********************************
 * For vi/vim
 * :set shiftwidth=4
 * :set softtabstop=4
 * :set expandtab
 *****************************************************************************/

/******************************************************************************
 * Include files needed to compile this file
 *****************************************************************************/

/*
 * POSIX Includes.
 */
 
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

/*
 * Basic ASP Includes.
 */

#include <clCommon.h>
#include <clOsalApi.h>
#include <clIocServices.h>

/*
 * ASP Client Includes.
 */
#include <clLogApi.h>
#include <clCorUtilityApi.h>
#include <clProvApi.h>

/*
 * ---BEGIN_APPLICATION_CODE---
 */
 
#include "clCompAppProv.h"

/*
 * ---END_APPLICATION_CODE---
 */

/******************************************************************************
 * Optional Features
 *****************************************************************************/

#define clprintf(severity, ...)   clAppLog(CL_LOG_HANDLE_APP, severity, 10, \
                                  CL_LOG_AREA_UNSPECIFIED, CL_LOG_CONTEXT_UNSPECIFIED,\
                                  __VA_ARGS__)

/*
 * ---BEGIN_APPLICATION_CODE---
 */

/*
 * ---END_APPLICATION_CODE---
 */

/******************************************************************************
 * Global Variables.
 *****************************************************************************/

/*
 * ---BEGIN_APPLICATION_CODE---
 */

/*
 * ---END_APPLICATION_CODE---
 */


/******************************************************************************
 * Application Transaction Life Cycle Management Functions
 *****************************************************************************/

/*
 * clCompAppTxnStart
 * -----------------
 * This function is invoked before forwarding any of the transaction requests
 * to this application. Please refer the detailed documentation for this function
 * in clCompAppProv.h file.
 */

void
clCompAppProvTxnStart(ClHandleT txnHandle)
{
    /*
     * ---BEGIN_APPLICATION_CODE---
     */

    clprintf(CL_LOG_SEV_INFO, "**** Inside the function : [%s] ****", __FUNCTION__);

    /*
     * ---END_APPLICATION_CODE---
     */
}

/*
 * clCompAppTxnEnd
 * ---------------
 * This function is invoked after all the transaction requests for this application
 * are completed. Please refer the detailed documentation for this function
 * in clCompAppProv.h file.
 */
void
clCompAppProvTxnEnd(ClHandleT txnHandle)
{
    /*
     * ---BEGIN_APPLICATION_CODE---
     */

    clprintf(CL_LOG_SEV_INFO, "**** Inside the function : [%s] ****", __FUNCTION__);

    /*
     * ---END_APPLICATION_CODE---
     */
}

/**
 * This is used assign the Provisioning Transaction callbacks, which will be
 * called before and end of a transaction. Both are optional, it can be 
 * disabled by passing NULL for the callbacks.
 */
ClProvTxnCallbacksT clProvTxnCallbacks =
{
    clCompAppProvTxnStart,      /* Transaction start callback               */
    clCompAppProvTxnEnd         /* Transaction end callback                 */
};


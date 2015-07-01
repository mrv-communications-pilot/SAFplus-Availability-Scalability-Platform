/*********************************************************************
* ModuleName  : idl
*********************************************************************/
/*********************************************************************
* Description :Server Stub routines
*     
* THIS FILE IS AUTO-GENERATED BY OPENCLOVIS IDE. EDIT THIS FILE AT
* YOUR OWN RISK. ANY CHANGE TO THIS FILE WILL BE OVERWRITTEN ON
* RE-GENERATION.
*     
*********************************************************************/
#include <netinet/in.h>
#include <clBufferApi.h>
#include <clRmdApi.h>
#include <clEoApi.h>
#include <ipi/clRmdIpi.h>
#include <string.h>
#include "ckptEockptServerExtCliServerFuncPeerServer.h"
#include "ckptEoServer.h"

extern ClUint32T  ckptEoidlSyncKey;
extern ClHandleDatabaseHandleT  ckptEoidlDatabaseHdl;



ClRcT _ckptClientInfoGetServer_6_0_0(ClEoDataT eoData, ClBufferHandleT inMsgHdl, ClBufferHandleT outMsgHdl)
{
    ClIdlContextInfoT *pIdlCtxInfo = NULL;
    ClRcT rc = CL_OK;
    ClHandleT  ckptHdl;
    ClCkptClientInfoListT_4_0_0  pClientInfoList;

    memset(&(ckptHdl), 0, sizeof(ClHandleT));
    memset(&(pClientInfoList), 0, sizeof(ClCkptClientInfoListT_4_0_0));


    rc = clXdrUnmarshallClHandleT( inMsgHdl,&(ckptHdl));
    if (CL_OK != rc)
    {
        goto LL0;
    }

    pIdlCtxInfo = (ClIdlContextInfoT *)clHeapAllocate(sizeof(ClIdlContextInfoT));
    if(pIdlCtxInfo == NULL)
    {
       return CL_IDL_RC(CL_ERR_NO_MEMORY);
    }
    memset(pIdlCtxInfo, 0, sizeof(ClIdlContextInfoT));
    pIdlCtxInfo->idlDeferMsg = outMsgHdl; 
    pIdlCtxInfo->inProgress  = CL_FALSE;
    rc = clIdlSyncPrivateInfoSet(ckptEoidlSyncKey, (void *)pIdlCtxInfo);
    if (CL_OK != rc)
    {
        clHeapFree(pIdlCtxInfo);
        goto L0;
    }
    rc = _ckptClientInfoGet_6_0_0(ckptHdl, &(pClientInfoList));
    if(pIdlCtxInfo->inProgress == CL_FALSE)
    {
      clHeapFree(pIdlCtxInfo);
      pIdlCtxInfo = NULL;
    }
    if (CL_OK != rc)
    {
       goto L0;
    }
    
    rc = clXdrMarshallClHandleT(&(ckptHdl), 0, 1);
    if (CL_OK != rc)
    {
        goto L1;
    }

    if(pIdlCtxInfo != NULL)
    {
      clHeapFree(pIdlCtxInfo);
      return rc;
    }
    
    rc = clXdrMarshallClCkptClientInfoListT_4_0_0(&(pClientInfoList), outMsgHdl, 1);
    if (CL_OK != rc)
    {
        goto L2;
    }

L2:    return rc;

LL0:  clXdrMarshallClHandleT(&(ckptHdl), 0, 1);

    return rc;

L0:  clXdrMarshallClHandleT(&(ckptHdl), 0, 1);

L1:  clXdrMarshallClCkptClientInfoListT_4_0_0(&(pClientInfoList), 0, 1);

    return rc;
}

ClRcT _ckptClientInfoGetResponseSend_6_0_0(ClIdlHandleT idlHdl,ClRcT retCode,CL_OUT  ClCkptClientInfoListT_4_0_0  pClientInfoList)
{
    ClIdlSyncInfoT    *pIdlSyncDeferInfo = NULL;
    ClRcT              rc                = CL_OK;
    ClBufferHandleT outMsgHdl     = 0;
    
    rc = clHandleCheckout(ckptEoidlDatabaseHdl,idlHdl,(void **)&pIdlSyncDeferInfo);
    if( rc != CL_OK)
    {
      goto Label0; 
    }
    outMsgHdl = pIdlSyncDeferInfo->idlRmdDeferMsg;
    
    rc = clXdrMarshallClCkptClientInfoListT_4_0_0(&(pClientInfoList), outMsgHdl, 1);
    if (CL_OK != rc)
    {
        goto L2;
    }

    rc = clIdlSyncResponseSend(pIdlSyncDeferInfo->idlRmdDeferHdl,outMsgHdl,
                                retCode);
    goto Label1; 
L2:  clXdrMarshallClCkptClientInfoListT_4_0_0(&(pClientInfoList), 0, 1);

    clHandleCheckin(ckptEoidlDatabaseHdl, idlHdl);
    clHandleDestroy(ckptEoidlDatabaseHdl, idlHdl);
    return rc;
Label1:
    clHandleCheckin(ckptEoidlDatabaseHdl, idlHdl);
    clHandleDestroy(ckptEoidlDatabaseHdl, idlHdl);
Label0:
    return rc;
}

ClRcT _ckptCheckpointReadSectionsServer_6_0_0(ClEoDataT eoData, ClBufferHandleT inMsgHdl, ClBufferHandleT outMsgHdl)
{
    ClIdlContextInfoT *pIdlCtxInfo = NULL;
    ClRcT rc = CL_OK;
    ClHandleT  ckptHdl;
    ClCkptIOVectorElementT_4_0_0*  pIOVec;
    ClUint32T  pNumVecs;

    memset(&(ckptHdl), 0, sizeof(ClHandleT));
    memset(&(pIOVec), 0, sizeof(ClCkptIOVectorElementT_4_0_0*));
    memset(&(pNumVecs), 0, sizeof(ClUint32T));


    rc = clXdrUnmarshallClHandleT( inMsgHdl,&(ckptHdl));
    if (CL_OK != rc)
    {
        goto LL0;
    }


    pIdlCtxInfo = (ClIdlContextInfoT *)clHeapAllocate(sizeof(ClIdlContextInfoT));
    if(pIdlCtxInfo == NULL)
    {
       return CL_IDL_RC(CL_ERR_NO_MEMORY);
    }
    memset(pIdlCtxInfo, 0, sizeof(ClIdlContextInfoT));
    pIdlCtxInfo->idlDeferMsg = outMsgHdl; 
    pIdlCtxInfo->inProgress  = CL_FALSE;
    rc = clIdlSyncPrivateInfoSet(ckptEoidlSyncKey, (void *)pIdlCtxInfo);
    if (CL_OK != rc)
    {
        clHeapFree(pIdlCtxInfo);
        goto L0;
    }
    rc = _ckptCheckpointReadSections_6_0_0(ckptHdl, &pIOVec, &(pNumVecs));
    if(pIdlCtxInfo->inProgress == CL_FALSE)
    {
      clHeapFree(pIdlCtxInfo);
      pIdlCtxInfo = NULL;
    }
    if (CL_OK != rc)
    {
       goto L0;
    }
    
    rc = clXdrMarshallClHandleT(&(ckptHdl), 0, 1);
    if (CL_OK != rc)
    {
        goto L1;
    }

    if(pIdlCtxInfo != NULL)
    {
      clHeapFree(pIdlCtxInfo);
      return rc;
    }
    
    rc = clXdrMarshallClUint32T(&(pNumVecs), outMsgHdl, 1);
    if (CL_OK != rc)
    {
        goto L2;
    }

    rc = clXdrMarshallPtrClCkptIOVectorElementT_4_0_0(pIOVec, pNumVecs, outMsgHdl, 1);
    if (CL_OK != rc)
    {
        goto L3;
    }

L3:    return rc;

LL0:  clXdrMarshallClHandleT(&(ckptHdl), 0, 1);

    return rc;

L0:  clXdrMarshallClHandleT(&(ckptHdl), 0, 1);

L1:  clXdrMarshallClUint32T(&(pNumVecs), 0, 1);
L2:  clXdrMarshallPtrClCkptIOVectorElementT_4_0_0(pIOVec, pNumVecs, 0, 1);

    return rc;
}

ClRcT _ckptCheckpointReadSectionsResponseSend_6_0_0(ClIdlHandleT idlHdl,ClRcT retCode,ClCkptIOVectorElementT_4_0_0*  pIOVec,CL_OUT  ClUint32T  pNumVecs)
{
    ClIdlSyncInfoT    *pIdlSyncDeferInfo = NULL;
    ClRcT              rc                = CL_OK;
    ClBufferHandleT outMsgHdl     = 0;
    
    rc = clHandleCheckout(ckptEoidlDatabaseHdl,idlHdl,(void **)&pIdlSyncDeferInfo);
    if( rc != CL_OK)
    {
      goto Label0; 
    }
    outMsgHdl = pIdlSyncDeferInfo->idlRmdDeferMsg;
    
    rc = clXdrMarshallClUint32T(&(pNumVecs), outMsgHdl, 1);
    if (CL_OK != rc)
    {
        goto L2;
    }

    rc = clXdrMarshallPtrClCkptIOVectorElementT_4_0_0(pIOVec, pNumVecs, outMsgHdl, 1);
    if (CL_OK != rc)
    {
        goto L3;
    }

    rc = clIdlSyncResponseSend(pIdlSyncDeferInfo->idlRmdDeferHdl,outMsgHdl,
                                retCode);
    goto Label1; 
L2:  clXdrMarshallClUint32T(&(pNumVecs), 0, 1);
L3:  clXdrMarshallPtrClCkptIOVectorElementT_4_0_0(pIOVec, pNumVecs, 0, 1);

    clHandleCheckin(ckptEoidlDatabaseHdl, idlHdl);
    clHandleDestroy(ckptEoidlDatabaseHdl, idlHdl);
    return rc;
Label1:
    clHandleCheckin(ckptEoidlDatabaseHdl, idlHdl);
    clHandleDestroy(ckptEoidlDatabaseHdl, idlHdl);
Label0:
    return rc;
}

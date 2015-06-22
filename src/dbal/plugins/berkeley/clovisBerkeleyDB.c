/*
 * Copyright (C) 2002-2012 OpenClovis Solutions Inc.  All Rights Reserved.
 *
 * This file is available  under  a  commercial  license  from  the
 * copyright  holder or the GNU General Public License Version 2.0.
 * 
 * The source code for  this program is not published  or otherwise 
 * divested of  its trade secrets, irrespective  of  what  has been 
 * deposited with the U.S. Copyright office.
 * 
 * This program is distributed in the  hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied  warranty  of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 * 
 * For more  information, see  the file  COPYING provided with this
 * material.
 */
/*******************************************************************************
 * ModuleName  : dbal
 * File        : clovisBerkeleyDB.c
 *******************************************************************************/

/*******************************************************************************
 * Description :
 * This file contains Clovis Database Abstraction Layer implementation for   
 * Berkeley database.                                                       
 *****************************************************************************/
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <cltypes.h>
#include <db.h>
#include <clCommon6.h>
#include <clCommonErrors6.h>
#include <clDbalApi.h>
#include "clClistApi.h"
#include "../../clovisDbalInternal.h"
#include <clCommon.hxx>
#include <clLogApi.hxx>
#include <clDbg.hxx>
#include <clDbalCfg.h>

#ifdef __cplusplus
extern "C" {
#endif

#define CL_DB_SYNC_OVERRIDE 2

/*****************************************************************************/
extern DBEngineInfo_t gDBEngineInfo;
extern ClDbalFunctionPtrsT *gDbalFunctionPtrs;
/*****************************************************************************/
typedef struct BerkeleyDBHandle_t {
    DB_TXN* pCurrentTxn;    
    DB* pDatabase;
    DBC *pCursor;
    ClClistT transactionStackHandle;
    ClUint32T bdbFlags;
}BerkeleyDBHandle_t;
/*****************************************************************************/
typedef struct BerkeleyDBEnvHandle_t {
    DB_ENV* pDBEnv;
    ClUint32T validity;
    ClUint32T isInitialized;
}BerkeleyDBEnvHandle_t;
/*****************************************************************************/
ClRcT clDbalInterface(ClDbalFunctionPtrsT *);
/*****************************************************************************/
static ClRcT  
cdbBerkeleyDBOpen(ClDBFileT    dbFile,
        ClDBNameT    dbName, 
        ClDBFlagT    dbFlag,
        ClUint32T   maxKeySize,
        ClUint32T   maxRecordSize,
        ClDBHandleT* pDBHandle);
/*****************************************************************************/
static ClRcT
cdbBerkeleyDBClose(ClDBHandleT dbHandle);
/*****************************************************************************/
static ClRcT
cdbBerkeleyDBSync(ClDBHandleT dbHandle,
                  ClUint32T   flags);
/*****************************************************************************/
static ClRcT
cdbBerkeleyDBRecordAdd(ClDBHandleT      dbHandle,
                       ClDBKeyT         dbKey,
                       ClUint32T       keySize,
                       ClDBRecordT      dbRec,
                       ClUint32T       recSize);
/*****************************************************************************/
static ClRcT
cdbBerkeleyDBRecordReplace(ClDBHandleT      dbHandle,
                           ClDBKeyT         dbKey,
                           ClUint32T       keySize,
                           ClDBRecordT      dbRec,
                           ClUint32T       recSize);
/*****************************************************************************/
static ClRcT  
cdbBerkeleyDBRecordGet(ClDBHandleT      dbHandle,
                       ClDBKeyT         dbKey,
                       ClUint32T       keySize,
                       ClDBRecordT*     pDBRec,
                       ClUint32T*      pRecSize);
/*****************************************************************************/
static ClRcT
cdbBerkeleyDBRecordDelete(ClDBHandleT      dbHandle,
                          ClDBKeyT         dbKey,
                          ClUint32T       keySize);
/*****************************************************************************/
static ClRcT
cdbBerkeleyDBFirstRecordGet(ClDBHandleT      dbHandle,
                            ClDBKeyT*        pDBKey,
                            ClUint32T*      pKeySize,
                            ClDBRecordT*     pDBRec,
                            ClUint32T*      pRecSize);
/*****************************************************************************/
static ClRcT
cdbBerkeleyDBNextRecordGet(ClDBHandleT      dbHandle,
                           ClDBKeyT         currentKey,
                           ClUint32T       currentKeySize,
                           ClDBKeyT*        pDBNextKey,
                           ClUint32T*      pNextKeySize,
                           ClDBRecordT*     pDBNextRec,
                           ClUint32T*      pNextRecSize);
/*****************************************************************************/
#if ( DB_VERSION_MAJOR >= 4 && DB_VERSION_MINOR >= 0 )
static ClRcT  
cdbBerkeleyDBTxnOpen(ClDBFileT    dbFile,
                     ClDBNameT    dbName, 
                     ClDBFlagT    dbFlag,
                     ClUint32T   maxKeySize,
                     ClUint32T   maxRecordSize,
                     ClDBHandleT* pDBHandle);
/*****************************************************************************/
static ClRcT
cdbBerkeleyDBTransactionBegin(ClDBHandleT  dbHandle);
/*****************************************************************************/
static ClRcT
cdbBerkeleyDBTransactionCommit(ClDBHandleT  dbHandle);
/*****************************************************************************/
static ClRcT
cdbBerkeleyDBTransactionAbort(ClDBHandleT  dbHandle);
/*****************************************************************************/
#else
static ClRcT  
cdbBerkeleyDummyTxnOpen(ClDBFileT    dbFile,
                        ClDBNameT    dbName, 
                        ClDBFlagT    dbFlag,
                        ClUint32T   maxKeySize,
                        ClUint32T   maxRecordSize,
                        ClDBHandleT* pDBHandle);
/*****************************************************************************/
static ClRcT
cdbBerkeleyDummyTransactionBegin(ClDBHandleT  dbHandle);
/*****************************************************************************/
static ClRcT
cdbBerkeleyDummyTransactionCommit(ClDBHandleT  dbHandle);
/*****************************************************************************/
static ClRcT
cdbBerkeleyDummyTransactionAbort(ClDBHandleT  dbHandle);
#endif
/*****************************************************************************/
static ClRcT
cdbBerkeleyDBRecordFree(ClDBHandleT  dbHandle,
                        ClDBRecordT  dbRec );
/*****************************************************************************/
static ClRcT
cdbBerkeleyDBKeyFree(ClDBHandleT  dbHandle,
                     ClDBKeyT     dbKey );
/*****************************************************************************/

void* clPluginAllocate(uint_t amt)
  {
  return malloc(amt);
  }

void clPluginFree(void* v)
  {
  free(v);
  }


static void
myDummyDeleteCallBack(ClClistDataT userData)
{
return;
}

/*****************************************************************************/
/* Globals */
BerkeleyDBEnvHandle_t gDBEnvironment;
/*****************************************************************************/

ClRcT
cdbBerkeleyDBInitialize(ClDBFileT    dbEnvFile,
                        ClDBEngineT* pEngineHandle)
{
    ClRcT errorCode = CL_OK;
    ClUint32T rc = 0;

    
    if(gDBEnvironment.isInitialized == 1) {
        logWarning(CL_LOG_AREA_UNSPECIFIED, CL_LOG_CONTEXT_UNSPECIFIED,"DBAL already initialized");
        
        return (CL_OK);
    }
    
    NULL_CHECK(pEngineHandle);

    rc = db_env_create(&(gDBEnvironment.pDBEnv), 0);
    if(0 != rc) {
        errorCode = CL_DBAL_RC(CL_DBAL_ERR_DB_ERROR);
        return(errorCode);
    }
    gDBEnvironment.pDBEnv->set_errpfx(gDBEnvironment.pDBEnv,"DBAL");
    gDBEnvironment.pDBEnv->set_errfile(gDBEnvironment.pDBEnv,stderr);

    rc = (gDBEnvironment.pDBEnv)->open(gDBEnvironment.pDBEnv, NULL, DB_CREATE | DB_INIT_LOG | DB_INIT_MPOOL | DB_INIT_TXN | DB_PRIVATE | DB_THREAD, 0);

    if(0 != rc) {
        errorCode = CL_DBAL_RC(CL_DBAL_ERR_DB_ERROR);
        goto error_out;
    }

#if 0 
   /* Stone: the DB_DSYNC operation seems to do a write and sync in a single 
      system call, if available, as opposed to a separate flush system call.
      This functionality adjusts precisely when a sync happens, not whether
      or not it happens at all!

      From the docs:
B_DSYNC_DB
    Configure Berkeley DB to flush database writes to the backing disk before returning from the write system call, rather than flushing database writes explicitly in a separate system call, as necessary.
   */
    ClCharT *syncEnvVar = NULL;
    gDBEnvironment.syncMode = CL_FALSE;

    syncEnvVar = getenv("ASP_DB_SYNC");
    if(syncEnvVar)
      {
        if (0 == strcasecmp(syncEnvVar, "TRUE"))
          {
            rc = (gDBEnvironment.pDBEnv)->set_flags(gDBEnvironment.pDBEnv, 
                                                DB_DSYNC_DB | DB_DSYNC_LOG, 1);
            if(0 != rc) 
              {
                errorCode = CL_DBAL_RC(CL_DBAL_ERR_DB_ERROR);
                goto error_out;
              }
            gDBEnvironment.syncMode = CL_TRUE;
          }
        else if (0 == strcasecmp(syncEnvVar, "FALSE"))
          {
            /* Nothing to do */
          }
        else
          {
            logWarning(CL_LOG_AREA_UNSPECIFIED, CL_LOG_CONTEXT_UNSPECIFIED,"Invalid value [%s] for environment variable [ASP_DB_SYNC].  Expecting 'TRUE' or 'FALSE'.",syncEnvVar);
          }
      }
#endif

    gDBEnvironment.validity = DATABASE_ENGINE_ID;
    gDBEnvironment.isInitialized = 1;

    *pEngineHandle = (ClDBEngineT)&gDBEnvironment;
    logTrace(CL_LOG_AREA_UNSPECIFIED, CL_LOG_CONTEXT_UNSPECIFIED,"DBAL initialize : DONE ");
    
    return (CL_OK);

error_out:
    (gDBEnvironment.pDBEnv)->err(gDBEnvironment.pDBEnv, rc, "environment open");
    (gDBEnvironment.pDBEnv)->close(gDBEnvironment.pDBEnv, 0);
    logWarning(CL_LOG_AREA_UNSPECIFIED, CL_LOG_CONTEXT_UNSPECIFIED,"DBAL initialize : NOT DONE");
    
    return(errorCode);
}
/*****************************************************************************/
ClRcT
cdbBerkeleyDBShutdown(ClDBEngineT engineHandle)
{
    ClRcT errorCode = CL_OK;
    ClUint32T rc = 0;
    

    if(gDBEnvironment.isInitialized == 0) 
    {
        errorCode = CL_DBAL_RC(CL_DBAL_ERR_DB_ERROR);
        logTrace(CL_LOG_AREA_UNSPECIFIED, CL_LOG_CONTEXT_UNSPECIFIED,"Berkeley DB not initialized");
        
        return(errorCode);
    }

    rc = (gDBEnvironment.pDBEnv)->close(gDBEnvironment.pDBEnv, 0);
    if(0 != rc) 
    {
        errorCode = CL_DBAL_RC(CL_DBAL_ERR_DB_ERROR);
        logWarning(CL_LOG_AREA_UNSPECIFIED, CL_LOG_CONTEXT_UNSPECIFIED,"Berkeley Shutdown failed.");
        
        return(errorCode);
    }

    gDBEnvironment.isInitialized = 0;
    gDBEnvironment.validity = 0;
    
    
    return(CL_OK);
}

ClRcT
clDbalConfigInitialize(void* pDbalConfiguration)
{
    ClRcT errorCode = CL_OK;
    ClDbalConfigurationT* pConfig = NULL;

    
    pConfig = (ClDbalConfigurationT *)pDbalConfiguration;

    NULL_CHECK(pConfig);

    errorCode = cdbBerkeleyDBInitialize((ClDBFileT)pConfig->Database.berkeleyConfig.engineEnvironmentPath, &gDBEngineInfo.engineHandle);
    if(CL_OK != errorCode) 
    {
        logWarning(CL_LOG_AREA_UNSPECIFIED, CL_LOG_CONTEXT_UNSPECIFIED,"Berkeley Initialize failed.");
        
        return(errorCode);
    }

    gDBEngineInfo.dbEngineType = 0;
    
    return(CL_OK);
}
/*****************************************************************************/
ClRcT
clDbalEngineFinalize() 
{
    ClRcT errorCode = CL_OK;

    
    errorCode = cdbBerkeleyDBShutdown(gDBEngineInfo.engineHandle);
    if(CL_OK != errorCode) 
    {
        logWarning(CL_LOG_AREA_UNSPECIFIED, CL_LOG_CONTEXT_UNSPECIFIED,"Berkeley DB Engine Shutdown failed.");
        
        return(errorCode);                    
    }
    
    return(CL_OK);
}
/*****************************************************************************/
/*****************************************************************************/

#if ( DB_VERSION_MAJOR >= 4 && DB_VERSION_MINOR >= 5 )

static void
cdbBerkeleyLsnReset(DB_ENV *env,
                    const ClCharT *dbFile)
{
    ClInt32T ret;
    struct stat statbuf;
    ret = stat(dbFile, &statbuf);
    if ((ret == -1) && (errno == ENOENT))
        goto failure;
    else if (ret == -1)
    {
        logWarning(CL_LOG_AREA_UNSPECIFIED, CL_LOG_CONTEXT_UNSPECIFIED,
                       "Accessing [%s] failed, error [%s]",
                        dbFile,
                        strerror(errno));
        goto failure;
    }

    env->lsn_reset(env, dbFile, 0);

failure:
    return;
}

#else

#define cdbBerkeleyLsnReset(env, dbFile) do {;}while(0)

#endif

static ClRcT  
cdbBerkeleyDBOpen(ClDBFileT    dbFile,
        ClDBNameT    dbName, 
        ClDBFlagT    dbFlag,
        ClUint32T   maxKeySize,
        ClUint32T   maxRecordSize,
        ClDBHandleT* pDBHandle)
{
    ClRcT errorCode = CL_OK;
    BerkeleyDBHandle_t* pBerkeleyHandle = NULL;
    ClUint32T rc = 0;
    DBTYPE berkeleyDBType = DB_BTREE;

    
    if(gDBEnvironment.isInitialized == 0) 
    {
        errorCode = CL_DBAL_RC(CL_DBAL_ERR_DB_ERROR);
        logError(CL_LOG_AREA_UNSPECIFIED, CL_LOG_CONTEXT_UNSPECIFIED,"Berkeley DB NOT initialized.");
        
        return(errorCode);
    }

    NULL_CHECK(pDBHandle);

    if(dbFlag >= CL_DB_MAX_FLAG) 
    {
        errorCode = CL_DBAL_RC(CL_ERR_INVALID_PARAMETER);
        logWarning(CL_LOG_AREA_UNSPECIFIED, CL_LOG_CONTEXT_UNSPECIFIED,"Berkeley DB Open failed: Invalid flag.");
        
        return(errorCode);
    }

    pBerkeleyHandle = (BerkeleyDBHandle_t *)clPluginAllocate(sizeof(BerkeleyDBHandle_t));
    if(NULL == pBerkeleyHandle) 
    {
        errorCode = CL_DBAL_RC(CL_ERR_NO_MEMORY);
        logWarning(CL_LOG_AREA_UNSPECIFIED, CL_LOG_CONTEXT_UNSPECIFIED,"Berkeley DB Open failed: No Memory.");
        
        return(errorCode);
    }

    errorCode = clClistCreate(0, CL_NO_DROP, myDummyDeleteCallBack, myDummyDeleteCallBack, &(pBerkeleyHandle->transactionStackHandle));
    if(CL_OK != errorCode)
    {
        goto err_cleanup;
    }

    pBerkeleyHandle->pCurrentTxn = NULL;
    
    cdbBerkeleyLsnReset(gDBEnvironment.pDBEnv, dbFile);

    rc = db_create(&(pBerkeleyHandle->pDatabase), gDBEnvironment.pDBEnv, 0);
    if(0 != rc)
    {        
        goto err_cleanup;
    }

    /* DB_SYNC is the only flag that we care about*/
    pBerkeleyHandle->bdbFlags = dbFlag & CL_DB_SYNC;
    dbFlag &= ~CL_DB_SYNC; /* Remove the Sync flag since the rest of this routine assumes it does not exist */

    if (1) /* Let the environment variable override the coded behavior */
    {
        if (getenv("ASP_DB_SYNC"))
        {
            if (SAFplus::clParseEnvBoolean("ASP_DB_SYNC") == CL_TRUE)
            {
                pBerkeleyHandle->bdbFlags |= CL_DB_SYNC | CL_DB_SYNC_OVERRIDE;
            }
            else
            {
                pBerkeleyHandle->bdbFlags &= ~CL_DB_SYNC;
                pBerkeleyHandle->bdbFlags |= CL_DB_SYNC_OVERRIDE;
            }
        }
    }

    if (dbFlag == CL_DB_CREAT)
    {
#if ( DB_VERSION_MAJOR >= 4 && DB_VERSION_MINOR >= 1 )
        rc = pBerkeleyHandle->pDatabase->open(pBerkeleyHandle->pDatabase, NULL, (ClCharT*)dbFile, 
                (ClCharT*)dbName, berkeleyDBType, DB_CREATE | DB_EXCL, 0);    
#else
        rc = pBerkeleyHandle->pDatabase->open(pBerkeleyHandle->pDatabase, (ClCharT*)dbFile, 
                (ClCharT*)dbName, berkeleyDBType, DB_CREATE | DB_EXCL, 0);
#endif

        if(0 == rc)
            goto open_done;

        if(EEXIST == rc)
        {
            rc = pBerkeleyHandle->pDatabase->remove(pBerkeleyHandle->pDatabase, (ClCharT*)dbFile, (ClCharT*)dbName, 0);
            if (0 != rc)
            {
                goto err_cleanup;
            }

            rc = db_create(&(pBerkeleyHandle->pDatabase), gDBEnvironment.pDBEnv, 0);
            if(0 != rc) 
            {
                goto err_cleanup;
            }

#if ( DB_VERSION_MAJOR >= 4 && DB_VERSION_MINOR >= 1 )
            rc = pBerkeleyHandle->pDatabase->open(pBerkeleyHandle->pDatabase, NULL, (ClCharT*)dbFile,
                    (ClCharT*)dbName, berkeleyDBType, DB_CREATE, 0);    
#else
            rc = pBerkeleyHandle->pDatabase->open(pBerkeleyHandle->pDatabase, (ClCharT*)dbFile, 
                    (ClCharT*)dbName, berkeleyDBType, DB_CREATE, 0);
#endif
            if(0 != rc) 
            {
                goto err_open_failed;
            }
        }
        else
        {
            goto err_open_failed;
        }
    }
    else if(dbFlag == CL_DB_OPEN)
    {
#if ( DB_VERSION_MAJOR >= 4 && DB_VERSION_MINOR >= 1 )
        rc = pBerkeleyHandle->pDatabase->open(pBerkeleyHandle->pDatabase, NULL, (ClCharT*)dbFile, (ClCharT*)dbName, berkeleyDBType, 0, 0);    

#else
        rc = pBerkeleyHandle->pDatabase->open(pBerkeleyHandle->pDatabase, (ClCharT*)dbFile, (ClCharT*)dbName, berkeleyDBType, 0, 0);
#endif
        if(0 != rc) 
        {
            goto err_open_failed;
        }
    }
    else if(dbFlag == CL_DB_APPEND)
    {

#if ( DB_VERSION_MAJOR >= 4 && DB_VERSION_MINOR >= 1 )
        rc = pBerkeleyHandle->pDatabase->open(pBerkeleyHandle->pDatabase, NULL, (ClCharT*)dbFile, (ClCharT*)dbName, berkeleyDBType, DB_CREATE, 0);    

#else
        rc = pBerkeleyHandle->pDatabase->open(pBerkeleyHandle->pDatabase, (ClCharT*)dbFile, (ClCharT*)dbName, berkeleyDBType, DB_CREATE, 0);
#endif

        if(0 != rc) 
        {
            goto err_open_failed;
        }
    }
    else
    {
        logError(CL_LOG_AREA_UNSPECIFIED, CL_LOG_CONTEXT_UNSPECIFIED,"Invalid DB flag [0x%x].  Cannot open database [%s].",dbFlag,(ClCharT*)dbFile);
        goto err_cleanup;
    }

open_done:    

    rc = pBerkeleyHandle->pDatabase->cursor(pBerkeleyHandle->pDatabase, pBerkeleyHandle->pCurrentTxn, &pBerkeleyHandle->pCursor, 0);
    if(0 != rc) 
    {
        goto err_open_failed;
    }    

    *pDBHandle = pBerkeleyHandle;

    
    return(CL_OK);

err_open_failed:   
    pBerkeleyHandle->pDatabase->err(pBerkeleyHandle->pDatabase,rc,"%d\n",rc);
    pBerkeleyHandle->pDatabase->close(pBerkeleyHandle->pDatabase, 0);
err_cleanup:
    clPluginFree(pBerkeleyHandle);
    errorCode = CL_DBAL_RC(CL_DBAL_ERR_DB_ERROR);
    logWarning(CL_LOG_AREA_UNSPECIFIED, CL_LOG_CONTEXT_UNSPECIFIED,"Berkeley DB open failed.");
    
    return(errorCode);
}
/*****************************************************************************/
static ClRcT
cdbBerkeleyDBClose(ClDBHandleT dbHandle)
{
    ClRcT errorCode = CL_OK;
    BerkeleyDBHandle_t* pBerkeleyHandle = NULL;
    ClUint32T rc = 0;
    
    pBerkeleyHandle = (BerkeleyDBHandle_t *)dbHandle;  

    errorCode = clClistDelete(&(pBerkeleyHandle->transactionStackHandle));
    if(CL_OK != errorCode)
    {
        goto err_out;
    }

    rc = pBerkeleyHandle->pCursor->c_close(pBerkeleyHandle->pCursor);
    if(0 != rc)
    {
        goto err_out;
    }

    rc = pBerkeleyHandle->pDatabase->close(pBerkeleyHandle->pDatabase, 0);
    if(rc != 0)
    {
        goto err_out;
    }

    clPluginFree(pBerkeleyHandle);
    
    return (CL_OK);    

err_out:    
    errorCode = CL_DBAL_RC(CL_DBAL_ERR_DB_ERROR);
    logWarning(CL_LOG_AREA_UNSPECIFIED, CL_LOG_CONTEXT_UNSPECIFIED,"Berkeley DB close failed.");
    
    return(errorCode);
}

static ClRcT
berkeleyDBSync(BerkeleyDBHandle_t *pBerkeleyHandle, ClUint32T flags)
{
    ClRcT rc = CL_OK;
    ClRcT errorCode = CL_OK;

    if(!pBerkeleyHandle) return CL_DBAL_RC(CL_ERR_INVALID_PARAMETER);
    rc = pBerkeleyHandle->pDatabase->sync(pBerkeleyHandle->pDatabase, 0);
    if(0 != rc) 
    {
        if(EINVAL == rc)
        {
            errorCode = CL_DBAL_RC(CL_ERR_INVALID_PARAMETER);
            logWarning(CL_LOG_AREA_UNSPECIFIED, CL_LOG_CONTEXT_UNSPECIFIED,"DB sync failed : Passed invalid flag.");
            
            return(errorCode);
        }
        errorCode = CL_DBAL_RC(CL_DBAL_ERR_DB_ERROR);
        logTrace(CL_LOG_AREA_UNSPECIFIED, CL_LOG_CONTEXT_UNSPECIFIED,"Berkeley DB sync failed.");
        
        return(errorCode);
    }  

    rc = (gDBEnvironment.pDBEnv)->log_flush(gDBEnvironment.pDBEnv, NULL);
    if (rc == EINVAL) /* dont return a sync error because the database was synced... */
    {
        logWarning(CL_LOG_AREA_UNSPECIFIED, CL_LOG_CONTEXT_UNSPECIFIED,"DB log sync failed");    
    }

    
    return (CL_OK);

}

/*****************************************************************************/
static ClRcT
cdbBerkeleyDBRecordAdd(ClDBHandleT      dbHandle,
                       ClDBKeyT         dbKey,
                       ClUint32T       keySize,
                       ClDBRecordT      dbRec,
                       ClUint32T       recSize)
{   
    ClRcT errorCode = CL_OK;
    BerkeleyDBHandle_t* pBerkeleyHandle = NULL;
    ClUint32T rc = 0;
    DBT key;
    DBT record;
    
    pBerkeleyHandle = (BerkeleyDBHandle_t *)dbHandle;

    NULL_CHECK(dbKey);
    NULL_CHECK(dbRec);

    memset(&key, 0, sizeof(key));
	memset(&record, 0, sizeof(record));

    key.data = (void *)dbKey;
    key.size = keySize;

    record.data = (void *)dbRec;
    record.size = recSize;

    rc = pBerkeleyHandle->pDatabase->put(pBerkeleyHandle->pDatabase, pBerkeleyHandle->pCurrentTxn, &key, &record, DB_NOOVERWRITE);
    
    if(DB_KEYEXIST == rc)
    {
        /* Berkeley returned duplicate error, so return CL_ERR_DUPLICATE */
        errorCode = CL_DBAL_RC(CL_ERR_DUPLICATE);
        logTrace(CL_LOG_AREA_UNSPECIFIED, CL_LOG_CONTEXT_UNSPECIFIED,"Duplicate key");
        
        return(errorCode);
    }

    if(0 != rc) {
        errorCode = CL_DBAL_RC(CL_DBAL_ERR_DB_ERROR);
        logTrace(CL_LOG_AREA_UNSPECIFIED, CL_LOG_CONTEXT_UNSPECIFIED,"Berkeley DB record add failed.");
        
        return(errorCode);
    }

    if (pBerkeleyHandle->bdbFlags & CL_DB_SYNC) berkeleyDBSync(pBerkeleyHandle, 0);

    
    return (CL_OK);
}

/*****************************************************************************/
static ClRcT
cdbBerkeleyDBSync(ClDBHandleT      dbHandle,
                  ClUint32T        flags)
{
    BerkeleyDBHandle_t* pBerkeleyHandle = NULL;

    

    pBerkeleyHandle = (BerkeleyDBHandle_t *)dbHandle;
    if(!pBerkeleyHandle) return CL_DBAL_RC(CL_ERR_INVALID_PARAMETER);

    if(!(pBerkeleyHandle->bdbFlags & CL_DB_SYNC))
        return berkeleyDBSync(pBerkeleyHandle, 0);
    
    return CL_OK;
}
/*****************************************************************************/
static ClRcT
cdbBerkeleyDBRecordReplace(ClDBHandleT      dbHandle,
                     ClDBKeyT         dbKey,
                     ClUint32T       keySize,
                     ClDBRecordT      dbRec,
                     ClUint32T       recSize)
{
    ClRcT errorCode = CL_OK;
    BerkeleyDBHandle_t* pBerkeleyHandle = NULL;
    ClUint32T rc = 0;
    DBT key;
    DBT record;

    
    pBerkeleyHandle = (BerkeleyDBHandle_t *)dbHandle;
    
    NULL_CHECK(dbKey);
    NULL_CHECK(dbRec);

    memset(&key, 0, sizeof(key));
	memset(&record, 0, sizeof(record));

    key.data = (void *)dbKey;
    key.size = keySize;

    record.data = (void *)dbRec;
    record.size = recSize;

    rc = pBerkeleyHandle->pDatabase->put(pBerkeleyHandle->pDatabase, pBerkeleyHandle->pCurrentTxn, &key, &record, 0);
    if(0 != rc) {
        errorCode = CL_DBAL_RC(CL_DBAL_ERR_DB_ERROR);
        logTrace(CL_LOG_AREA_UNSPECIFIED, CL_LOG_CONTEXT_UNSPECIFIED,"Berkeley DB record replace failed.");
        
        return(errorCode);
    }  

    if (pBerkeleyHandle->bdbFlags & CL_DB_SYNC) berkeleyDBSync(pBerkeleyHandle, 0);

    
    return (CL_OK);
}
/*****************************************************************************/
static ClRcT  
cdbBerkeleyDBRecordGet(ClDBHandleT      dbHandle,
                 ClDBKeyT         dbKey,
                 ClUint32T       keySize,
                 ClDBRecordT*     pDBRec,
                 ClUint32T*      pRecSize)
{
    ClRcT errorCode = CL_OK;
    BerkeleyDBHandle_t* pBerkeleyHandle = NULL;
    ClUint32T rc = 0;
    DBT key;
    DBT record;

    
    NULL_CHECK(dbKey);
    NULL_CHECK(pDBRec);
    NULL_CHECK(pRecSize);

    pBerkeleyHandle = (BerkeleyDBHandle_t *)dbHandle;

    memset(&key, 0, sizeof(key));
    memset(&record, 0, sizeof(record));
	
    key.data = (void *)dbKey;
    key.size = keySize;
    record.flags = DB_DBT_MALLOC;
    rc = pBerkeleyHandle->pDatabase->get(pBerkeleyHandle->pDatabase, pBerkeleyHandle->pCurrentTxn, &key, &record,0);
    if(0 != rc) {
        errorCode = CL_DBAL_RC(CL_DBAL_ERR_DB_ERROR);
        logTrace(CL_LOG_AREA_UNSPECIFIED, CL_LOG_CONTEXT_UNSPECIFIED,"Berkeley DB record get failed.");
        
        return(errorCode);
    }

    *pDBRec = (ClDBRecordT) clPluginAllocate(record.size);
    if(NULL == *pDBRec) {
        free(record.data);
        errorCode = CL_DBAL_RC(CL_ERR_NO_MEMORY);
        logTrace(CL_LOG_AREA_UNSPECIFIED, CL_LOG_CONTEXT_UNSPECIFIED,"Berkeley DB record get failed.");
        
        return(errorCode);
    }

    memcpy(*pDBRec, record.data, record.size);
    *pRecSize = (ClUint32T)record.size;
    free(record.data);
    
    return (CL_OK);
}
/*****************************************************************************/
static ClRcT
cdbBerkeleyDBRecordDelete(ClDBHandleT      dbHandle,
                    ClDBKeyT         dbKey,
                    ClUint32T       keySize)
{
    ClRcT errorCode = CL_OK;
    BerkeleyDBHandle_t* pBerkeleyHandle = NULL;
    ClUint32T rc = 0;
    DBT key;

    
    pBerkeleyHandle = (BerkeleyDBHandle_t *)dbHandle;

    NULL_CHECK(dbKey);
    
    memset(&key, 0, sizeof(key));

    key.data = (void *)dbKey;
    key.size = keySize;

    rc = pBerkeleyHandle->pDatabase->del(pBerkeleyHandle->pDatabase, pBerkeleyHandle->pCurrentTxn, &key, 0);
    if(0 != rc) {
        if(DB_NOTFOUND == rc) {
            errorCode = CL_DBAL_RC(CL_ERR_NOT_EXIST);
            logTrace(CL_LOG_AREA_UNSPECIFIED, CL_LOG_CONTEXT_UNSPECIFIED,"Berkeley DB record delete failed:Record not found.");
            
            return(errorCode);
        }
        errorCode = CL_DBAL_RC(CL_DBAL_ERR_DB_ERROR);
        logTrace(CL_LOG_AREA_UNSPECIFIED, CL_LOG_CONTEXT_UNSPECIFIED,"Berkeley DB record delete failed.");
        
        return(errorCode);
    }

    if (pBerkeleyHandle->bdbFlags & CL_DB_SYNC) berkeleyDBSync(pBerkeleyHandle,0);

    
    return (CL_OK);
}
/*****************************************************************************/
static ClRcT
cdbBerkeleyDBFirstRecordGet(ClDBHandleT      dbHandle,
                      ClDBKeyT*        pDBKey,
                      ClUint32T*      pKeySize,
                      ClDBRecordT*     pDBRec,
                      ClUint32T*      pRecSize)
{
    ClRcT errorCode = CL_OK;
    BerkeleyDBHandle_t* pBerkeleyHandle = NULL;
    ClUint32T rc = 0;
    DBT key;
    DBT record;    

    
    NULL_CHECK(pDBKey);
    NULL_CHECK(pKeySize);

    NULL_CHECK(pDBRec);
    NULL_CHECK(pRecSize);

    pBerkeleyHandle = (BerkeleyDBHandle_t *)dbHandle;

    memset(&key, 0, sizeof(key));
	memset(&record, 0, sizeof(record));
    key.flags = DB_DBT_MALLOC;
    record.flags = DB_DBT_MALLOC;
    rc = pBerkeleyHandle->pCursor->c_get(pBerkeleyHandle->pCursor, &key, &record, DB_FIRST);
    if(0 != rc) {
        if(DB_NOTFOUND == rc) {
            errorCode = CL_DBAL_RC(CL_ERR_NOT_EXIST);
            logTrace(CL_LOG_AREA_UNSPECIFIED, CL_LOG_CONTEXT_UNSPECIFIED,"Berkeley DB first record get failed.");
            
            return(errorCode);
        }
        errorCode = CL_DBAL_RC(CL_DBAL_ERR_DB_ERROR);
        logTrace(CL_LOG_AREA_UNSPECIFIED, CL_LOG_CONTEXT_UNSPECIFIED,"Berkeley DB first record get failed.");
        
        return(errorCode);
    }

    *pDBKey = (ClDBKeyT) clPluginAllocate(key.size);
    if(NULL == *pDBKey) {
        free(key.data);
        free(record.data);
        errorCode = CL_DBAL_RC(CL_ERR_NO_MEMORY);
        logTrace(CL_LOG_AREA_UNSPECIFIED, CL_LOG_CONTEXT_UNSPECIFIED,"Berkeley DB first record get failed.");
        
        return(errorCode);
    }

    memcpy(*pDBKey, key.data, key.size);    
    *pKeySize = (ClUint32T)key.size;

    *pDBRec = (ClDBRecordT) clPluginAllocate(record.size);
    if(NULL == *pDBRec) {
        free(key.data);
        free(record.data);
        errorCode = CL_DBAL_RC(CL_ERR_NO_MEMORY);
        logTrace(CL_LOG_AREA_UNSPECIFIED, CL_LOG_CONTEXT_UNSPECIFIED,"Berkeley DB first record get failed.");
        
        return(errorCode);
    }

    memcpy(*pDBRec, record.data, record.size);
    *pRecSize = (ClUint32T)record.size;
    free(key.data);
    free(record.data);
    
    return (CL_OK);
}
/*****************************************************************************/
static ClRcT
cdbBerkeleyDBNextRecordGet(ClDBHandleT      dbHandle,
                     ClDBKeyT         currentKey,
                     ClUint32T       currentKeySize,
                     ClDBKeyT*        pDBNextKey,
                     ClUint32T*      pNextKeySize,
                     ClDBRecordT*     pDBNextRec,
                     ClUint32T*      pNextRecSize)
{
    ClRcT errorCode = CL_OK;
    BerkeleyDBHandle_t* pBerkeleyHandle = NULL;
    ClUint32T rc = 0;
    DBT key;
    DBT record;

    
    NULL_CHECK(currentKey);
    NULL_CHECK(pDBNextKey);
    NULL_CHECK(pNextKeySize);

    NULL_CHECK(pDBNextRec);
    NULL_CHECK(pNextRecSize);

    pBerkeleyHandle = (BerkeleyDBHandle_t *)dbHandle;

    memset(&key, 0, sizeof(key));
	memset(&record, 0, sizeof(record));
	
    key.data = (void *)currentKey;
    key.size = currentKeySize;
    key.flags = DB_DBT_MALLOC;
    record.flags = DB_DBT_MALLOC;

    rc = pBerkeleyHandle->pCursor->c_get(pBerkeleyHandle->pCursor, &key, &record, DB_NEXT);
    if(0 != rc) {
        if(DB_NOTFOUND == rc) {
            errorCode = CL_DBAL_RC(CL_ERR_NOT_EXIST);
            logTrace(CL_LOG_AREA_UNSPECIFIED, CL_LOG_CONTEXT_UNSPECIFIED,"Berkeley DB next record get failed.");
            
            return(errorCode);
        }
        errorCode = CL_DBAL_RC(CL_DBAL_ERR_DB_ERROR);
        logTrace(CL_LOG_AREA_UNSPECIFIED, CL_LOG_CONTEXT_UNSPECIFIED,"Berkeley DB next record get failed.");
        
        return(errorCode);
    }

    *pDBNextKey = (ClDBKeyT) clPluginAllocate(key.size);
    if(NULL == *pDBNextKey) {
        free(key.data);
        free(record.data);
        errorCode = CL_DBAL_RC(CL_ERR_NO_MEMORY);
        logTrace(CL_LOG_AREA_UNSPECIFIED, CL_LOG_CONTEXT_UNSPECIFIED,"Berkeley DB next record get failed.");
        
        return(errorCode);
    }

    memcpy(*pDBNextKey, key.data, key.size);    
    *pNextKeySize = (ClUint32T)key.size;

    *pDBNextRec = (ClDBRecordT) clPluginAllocate(record.size);
    if(NULL == *pDBNextRec) {
        free(key.data);
        free(record.data);
        errorCode = CL_DBAL_RC(CL_ERR_NO_MEMORY);
        logTrace(CL_LOG_AREA_UNSPECIFIED, CL_LOG_CONTEXT_UNSPECIFIED,"Berkeley DB next record get failed.");
        
        return(errorCode);
    }

    memcpy(*pDBNextRec, record.data, record.size);
    *pNextRecSize = (ClUint32T)record.size;
    free(key.data);
    free(record.data);
    
    return (CL_OK);
}

/*****************************************************************************/
static ClRcT  
cdbBerkeleyDBTxnOpen(ClDBFileT    dbFile,
                     ClDBNameT    dbName, 
                     ClDBFlagT    dbFlag,
                     ClUint32T   maxKeySize,
                     ClUint32T   maxRecordSize,
                     ClDBHandleT* pDBHandle)
{
    ClRcT errorCode = CL_OK;
    BerkeleyDBHandle_t* pBerkeleyHandle = NULL;
    ClUint32T rc = 0;
    DBTYPE berkeleyDBType = DB_BTREE;

    
    if(gDBEnvironment.isInitialized == 0) {
        errorCode = CL_DBAL_RC(CL_DBAL_ERR_DB_ERROR);
        logWarning(CL_LOG_AREA_UNSPECIFIED, CL_LOG_CONTEXT_UNSPECIFIED,"Berkeley DB NOT initialized.");
        
        return(errorCode);
    }

    NULL_CHECK(pDBHandle);

    if(dbFlag >= CL_DB_MAX_FLAG) {
        errorCode = CL_DBAL_RC(CL_ERR_INVALID_PARAMETER);
        logWarning(CL_LOG_AREA_UNSPECIFIED, CL_LOG_CONTEXT_UNSPECIFIED,"Berkeley DB Open failed: Invalid flag.");
        
        return(errorCode);
    }

    pBerkeleyHandle = (BerkeleyDBHandle_t *)clPluginAllocate(sizeof(BerkeleyDBHandle_t));
    if(NULL == pBerkeleyHandle) {
        errorCode = CL_DBAL_RC(CL_ERR_NO_MEMORY);
        logWarning(CL_LOG_AREA_UNSPECIFIED, CL_LOG_CONTEXT_UNSPECIFIED,"Berkeley DB Open failed: No Memory.");
        
        return(errorCode);
    }

    errorCode = clClistCreate(0, CL_NO_DROP, myDummyDeleteCallBack, myDummyDeleteCallBack, &(pBerkeleyHandle->transactionStackHandle));
    if(CL_OK != errorCode) 
    {
        goto err_cleaup;
    }

    pBerkeleyHandle->pCurrentTxn = NULL;

    cdbBerkeleyLsnReset(gDBEnvironment.pDBEnv, dbFile);

    rc = db_create(&(pBerkeleyHandle->pDatabase), gDBEnvironment.pDBEnv, 0);
    if(0 != rc) 
    {        
        goto err_cleaup;
    }

    /* DB_SYNC is the only flag that we care about*/
    pBerkeleyHandle->bdbFlags = dbFlag & CL_DB_SYNC;
    dbFlag &= ~CL_DB_SYNC; /* Remove the Sync flag since the rest of this routine assumes it does not exist */

    if (1) /* Let the environment variable override the coded behavior */
    {
        if (getenv("ASP_DB_SYNC"))
        {
            if (SAFplus::clParseEnvBoolean("ASP_DB_SYNC") == CL_TRUE)
            {
                pBerkeleyHandle->bdbFlags |= CL_DB_SYNC | CL_DB_SYNC_OVERRIDE;
            }
            else
            {
                pBerkeleyHandle->bdbFlags &= ~CL_DB_SYNC;
                pBerkeleyHandle->bdbFlags |= CL_DB_SYNC_OVERRIDE;
            }
        }
    }

    if (dbFlag == CL_DB_CREAT)
    {
#if ( DB_VERSION_MAJOR >= 4 && DB_VERSION_MINOR >= 1 )
        rc = pBerkeleyHandle->pDatabase->open(pBerkeleyHandle->pDatabase, NULL, (ClCharT*)dbFile, 
                (ClCharT*)dbName, berkeleyDBType, DB_CREATE | DB_EXCL | DB_AUTO_COMMIT, 0);    
#else
        rc = pBerkeleyHandle->pDatabase->open(pBerkeleyHandle->pDatabase, (ClCharT*)dbFile, 
                (ClCharT*)dbName, berkeleyDBType, DB_CREATE | DB_EXCL | DB_AUTO_COMMIT, 0);
#endif

        if(0 == rc)
            goto txnOpen_done;

        if(EEXIST == rc)
        {
            rc = pBerkeleyHandle->pDatabase->remove(pBerkeleyHandle->pDatabase, (ClCharT*)dbFile, (ClCharT*)dbName, 0);
            if (0 != rc)
            {
                goto err_cleaup;
            }

            rc = db_create(&(pBerkeleyHandle->pDatabase), gDBEnvironment.pDBEnv, 0);
            if(0 != rc)
            {
                goto err_cleaup;
            }

#if ( DB_VERSION_MAJOR >= 4 && DB_VERSION_MINOR >= 1 )
            rc = pBerkeleyHandle->pDatabase->open(pBerkeleyHandle->pDatabase, NULL, (ClCharT*)dbFile,
                    (ClCharT*)dbName, berkeleyDBType, DB_CREATE | DB_AUTO_COMMIT, 0);    
#else
            rc = pBerkeleyHandle->pDatabase->open(pBerkeleyHandle->pDatabase, (ClCharT*)dbFile, 
                    (ClCharT*)dbName, berkeleyDBType, DB_CREATE | DB_AUTO_COMMIT, 0);
#endif
            if(0 != rc) {
                goto err_open_failed;
            }
        }
        else
        {
            goto err_open_failed;
        }

    }

    else if(dbFlag == CL_DB_OPEN)
    {
#if ( DB_VERSION_MAJOR >= 4 && DB_VERSION_MINOR >= 1 )
        rc = pBerkeleyHandle->pDatabase->open(pBerkeleyHandle->pDatabase,
                NULL, (ClCharT*)dbFile, (ClCharT*)dbName, berkeleyDBType,
                DB_AUTO_COMMIT, 0);    

#else
        rc = pBerkeleyHandle->pDatabase->open(pBerkeleyHandle->pDatabase,
                (ClCharT*)dbFile, (ClCharT*)dbName, berkeleyDBType,
                DB_AUTO_COMMIT, 0);
#endif
        if(0 != rc) 
        {
            goto err_open_failed;
        }
    }
    else if(dbFlag == CL_DB_APPEND)
    {

#if ( DB_VERSION_MAJOR >= 4 && DB_VERSION_MINOR >= 1 )
        rc = pBerkeleyHandle->pDatabase->open(pBerkeleyHandle->pDatabase,
                NULL, (ClCharT*)dbFile, (ClCharT*)dbName, berkeleyDBType,
                DB_CREATE | DB_AUTO_COMMIT, 0);    

#else
        rc = pBerkeleyHandle->pDatabase->open(pBerkeleyHandle->pDatabase,
                (ClCharT*)dbFile, (ClCharT*)dbName, berkeleyDBType, 
                DB_CREATE | DB_AUTO_COMMIT, 0);
#endif

        if(0 != rc) 
        {
            goto err_open_failed;
        }
    }
    else
    {
        logError(CL_LOG_AREA_UNSPECIFIED, CL_LOG_CONTEXT_UNSPECIFIED,"Invalid DB flag [0x%x].  Cannot open database [%s].",dbFlag,(ClCharT*)dbFile);
        goto err_cleaup;
    }

txnOpen_done:

    rc = pBerkeleyHandle->pDatabase->cursor(pBerkeleyHandle->pDatabase, pBerkeleyHandle->pCurrentTxn, &pBerkeleyHandle->pCursor, 0);
    if(0 != rc) 
    {
        goto err_open_failed;
    }    

    *pDBHandle = pBerkeleyHandle;
    
    return(CL_OK);

err_open_failed:    
    pBerkeleyHandle->pDatabase->err(pBerkeleyHandle->pDatabase,rc,"%d\n",rc);
    pBerkeleyHandle->pDatabase->close(pBerkeleyHandle->pDatabase, 0);
err_cleaup:    
    clPluginFree(pBerkeleyHandle);
    errorCode = CL_DBAL_RC(CL_DBAL_ERR_DB_ERROR);
    logWarning(CL_LOG_AREA_UNSPECIFIED, CL_LOG_CONTEXT_UNSPECIFIED,"Berkeley DB open failed.");
    
    return(errorCode);
}

/*****************************************************************************/
#if ( DB_VERSION_MAJOR >= 4 && DB_VERSION_MINOR >= 0 )
static ClRcT
cdbBerkeleyDBTransactionBegin(ClDBHandleT  dbHandle)
{
    ClRcT errorCode = CL_OK;
    BerkeleyDBHandle_t* pBerkeleyHandle = NULL;
    ClUint32T rc = 0;
    ClUint32T flags = 0;
    DB_TXN* pParentTxn = NULL;

    
    pBerkeleyHandle = (BerkeleyDBHandle_t *)dbHandle;

    pParentTxn = pBerkeleyHandle->pCurrentTxn;

    rc = pBerkeleyHandle->pCursor->c_close(pBerkeleyHandle->pCursor);
    if(0 != rc) 
    {
        goto err_out;
    }

    if (pBerkeleyHandle->bdbFlags & CL_DB_SYNC) flags = DB_TXN_SYNC;
    else flags = DB_TXN_NOSYNC;

    rc = (gDBEnvironment.pDBEnv)->txn_begin(gDBEnvironment.pDBEnv, pParentTxn, &(pBerkeleyHandle->pCurrentTxn), flags);

    if(0 != rc) 
    {
        goto err_out;
    }

    rc = pBerkeleyHandle->pDatabase->cursor(pBerkeleyHandle->pDatabase, pBerkeleyHandle->pCurrentTxn, &pBerkeleyHandle->pCursor, 0);
    if(0 != rc) 
    {
        goto err_out;
    }

    errorCode = clClistLastNodeAdd(pBerkeleyHandle->transactionStackHandle, (ClClistDataT)pParentTxn);
    if(CL_OK != errorCode)
    {
        goto err_out;
    }

    
    return (CL_OK);

err_out:
    errorCode = CL_DBAL_RC(CL_DBAL_ERR_DB_ERROR);
    logWarning(CL_LOG_AREA_UNSPECIFIED, CL_LOG_CONTEXT_UNSPECIFIED,"Berkeley DB transaction begin failed.");
    
    return(errorCode);
}
/*****************************************************************************/
static ClRcT
cdbBerkeleyDBTransactionCommit(ClDBHandleT  dbHandle)
{
    ClRcT errorCode = CL_OK;
    BerkeleyDBHandle_t* pBerkeleyHandle = NULL;
    ClUint32T rc = 0;
    ClUint32T flags = 0;
    DB_TXN* pParentTxn = NULL;
    ClClistNodeT nodeHandle = 0;

    
    pBerkeleyHandle = (BerkeleyDBHandle_t *)dbHandle;

    errorCode = clClistLastNodeGet(pBerkeleyHandle->transactionStackHandle, &nodeHandle);
    if(CL_OK != errorCode) 
    {
        goto err_out;
    }

    errorCode = clClistDataGet(pBerkeleyHandle->transactionStackHandle, nodeHandle, (ClClistDataT *)&pParentTxn);
    if(CL_OK != errorCode) 
    {
        goto err_out;
    }

    errorCode = clClistNodeDelete(pBerkeleyHandle->transactionStackHandle, nodeHandle);
    if(CL_OK != errorCode) 
    {
        goto err_out;
    }

    rc = pBerkeleyHandle->pCursor->c_close(pBerkeleyHandle->pCursor);
    if(0 != rc) 
    {
        goto err_out;
    }

    if (pBerkeleyHandle->bdbFlags & CL_DB_SYNC) flags = DB_TXN_SYNC;
    else flags = DB_TXN_NOSYNC;

    rc = pBerkeleyHandle->pCurrentTxn->commit(pBerkeleyHandle->pCurrentTxn, flags);
    if(0 != rc) 
    {
        goto err_out;
    }

    pBerkeleyHandle->pCurrentTxn = pParentTxn;    

    rc = pBerkeleyHandle->pDatabase->cursor(pBerkeleyHandle->pDatabase, pBerkeleyHandle->pCurrentTxn, &pBerkeleyHandle->pCursor, 0);
    if(0 != rc) 
    {
        goto err_out;
    }

    
    return (CL_OK);

err_out:
    errorCode = CL_DBAL_RC(CL_DBAL_ERR_COMMIT_FAILED);
    logWarning(CL_LOG_AREA_UNSPECIFIED, CL_LOG_CONTEXT_UNSPECIFIED,"Berkeley DB transaction commit failed.");
    
    return(errorCode);
}
/*****************************************************************************/
static ClRcT
cdbBerkeleyDBTransactionAbort(ClDBHandleT  dbHandle)
{
    ClRcT errorCode = CL_OK;
    BerkeleyDBHandle_t* pBerkeleyHandle = NULL;
    ClUint32T rc = 0;
    DB_TXN* pParentTxn = NULL;
    ClClistNodeT nodeHandle = 0;

    
    pBerkeleyHandle = (BerkeleyDBHandle_t *)dbHandle;

    errorCode = clClistLastNodeGet(pBerkeleyHandle->transactionStackHandle, &nodeHandle);
    if(CL_OK != errorCode) 
    {
        goto err_out;
    }

    errorCode = clClistDataGet(pBerkeleyHandle->transactionStackHandle, nodeHandle, (ClClistDataT *)&pParentTxn);
    if(CL_OK != errorCode) 
    {
        goto err_out;
    }

    errorCode = clClistNodeDelete(pBerkeleyHandle->transactionStackHandle, nodeHandle);
    if(CL_OK != errorCode) 
    {
        goto err_out;
    }

    rc = pBerkeleyHandle->pCursor->c_close(pBerkeleyHandle->pCursor);
    if(0 != rc) 
    {
        goto err_out;
    }

    rc = pBerkeleyHandle->pCurrentTxn->abort(pBerkeleyHandle->pCurrentTxn);
    if(0 != rc) 
    {
        goto err_out;
    }

    pBerkeleyHandle->pCurrentTxn = pParentTxn;

    rc = pBerkeleyHandle->pDatabase->cursor(pBerkeleyHandle->pDatabase, pBerkeleyHandle->pCurrentTxn, &pBerkeleyHandle->pCursor, 0);
    if(0 != rc) 
    {
        goto err_out;
    }

    
    return (CL_OK);

err_out:
    errorCode = CL_DBAL_RC(CL_DBAL_ERR_ABORT_FAILED);
    logWarning(CL_LOG_AREA_UNSPECIFIED, CL_LOG_CONTEXT_UNSPECIFIED,"Berkeley DB transaction abort failed.");
    
    return(errorCode);
}
#else
static ClRcT  
cdbBerkeleyDummyTxnOpen(ClDBFileT    dbFile,
                        ClDBNameT    dbName, 
                        ClDBFlagT    dbFlag,
                        ClUint32T   maxKeySize,
                        ClUint32T   maxRecordSize,
                        ClDBHandleT* pDBHandle)
{
    return CL_OK;
}
/*****************************************************************************/
static ClRcT
cdbBerkeleyDummyTransactionBegin(ClDBHandleT  dbHandle)
{
    return CL_OK;
}

/*****************************************************************************/
static ClRcT
cdbBerkeleyDummyTransactionCommit(ClDBHandleT  dbHandle)
{
    return CL_OK;
}
/*****************************************************************************/
static ClRcT
cdbBerkeleyDummyTransactionAbort(ClDBHandleT  dbHandle)
{
    return CL_OK;
}
#endif

/*****************************************************************************/
static ClRcT
cdbBerkeleyDBRecordFree(ClDBHandleT  dbHandle,
                        ClDBRecordT  dbRec)
{
    ClRcT errorCode = CL_OK;
    
    
    NULL_CHECK(dbRec);
    clPluginFree(dbRec);
    
    return (CL_OK);
}
/*****************************************************************************/
static ClRcT
cdbBerkeleyDBKeyFree(ClDBHandleT  dbHandle,
                     ClDBKeyT     dbKey)
{
    ClRcT errorCode = CL_OK;

    
    NULL_CHECK(dbKey);
    clPluginFree(dbKey);
    
    return (CL_OK);
}

/*****************************************************************************/
ClRcT clDbalInterface(ClDbalFunctionPtrsT  *funcDbPtr)
{
    ClDbalConfigT* pDbalConfiguration = NULL;
    ClRcT          rc = CL_OK;
    
    pDbalConfiguration = (ClDbalConfigT*)clPluginAllocate(sizeof(ClDbalConfigT));
    if ( NULL == pDbalConfiguration )
    {
        logTrace(CL_LOG_AREA_UNSPECIFIED, CL_LOG_CONTEXT_UNSPECIFIED,"DBAL init Failed\n");
        return CL_DBAL_RC(CL_ERR_NO_MEMORY);
    }

    memset(pDbalConfiguration, '\0', sizeof(ClDbalConfigT));  
    strcpy((ClCharT*)pDbalConfiguration->Database.berkeleyConfig.engineEnvironmentPath, CL_DBAL_BERKELEY_ENV_PATH);
    if ((rc = clDbalConfigInitialize((void *)pDbalConfiguration)) != CL_OK )
    {
        logTrace(CL_LOG_AREA_UNSPECIFIED, CL_LOG_CONTEXT_UNSPECIFIED,"DBAL init Failed\n");
        return rc;
    }

    funcDbPtr->fpCdbOpen              = cdbBerkeleyDBOpen;
    funcDbPtr->fpCdbClose             = cdbBerkeleyDBClose;
    funcDbPtr->fpCdbSync              = cdbBerkeleyDBSync;
    funcDbPtr->fpCdbRecordAdd         = cdbBerkeleyDBRecordAdd;
    funcDbPtr->fpCdbRecordReplace     = cdbBerkeleyDBRecordReplace;
    funcDbPtr->fpCdbRecordGet         = cdbBerkeleyDBRecordGet;
    funcDbPtr->fpCdbRecordDelete      = cdbBerkeleyDBRecordDelete;
    funcDbPtr->fpCdbFirstRecordGet    = cdbBerkeleyDBFirstRecordGet;
    funcDbPtr->fpCdbNextRecordGet     = cdbBerkeleyDBNextRecordGet;
#if ( DB_VERSION_MAJOR >= 4 && DB_VERSION_MINOR >= 0 )
    funcDbPtr->fpCdbTxnOpen           = cdbBerkeleyDBTxnOpen;
    funcDbPtr->fpCdbTransactionBegin  = cdbBerkeleyDBTransactionBegin;
    funcDbPtr->fpCdbTransactionCommit = cdbBerkeleyDBTransactionCommit;
    funcDbPtr->fpCdbTransactionAbort  = cdbBerkeleyDBTransactionAbort;
#else
    funcDbPtr->fpCdbTxnOpen           = cdbBerkeleyDummyTxnOpen;
    funcDbPtr->fpCdbTransactionBegin  = cdbBerkeleyDummyTransactionBegin;
    funcDbPtr->fpCdbTransactionCommit = cdbBerkeleyDummyTransactionCommit;
    funcDbPtr->fpCdbTransactionAbort  = cdbBerkeleyDummyTransactionAbort;
#endif
    funcDbPtr->fpCdbRecordFree        = cdbBerkeleyDBRecordFree;
    funcDbPtr->fpCdbKeyFree           = cdbBerkeleyDBKeyFree;
    funcDbPtr->fpCdbFinalize          = clDbalEngineFinalize;
    funcDbPtr->validDatabase          = DATABASE_ID;

    clPluginFree(pDbalConfiguration);

    return rc; 
}

#ifdef __cplusplus
 }
#endif

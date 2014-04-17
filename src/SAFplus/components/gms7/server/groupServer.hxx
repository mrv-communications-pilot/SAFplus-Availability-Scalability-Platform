#ifndef groupServer_hxx
#define groupServer_hxx

// Standard includes
#include <string>

// SAFplus includes
#include <clHandleApi.hxx>
#include <clGroup.hxx>
#include <clCpmApi.h>
#include "groupMessageHandler.hxx"
#include "clNodeCache.h"
#include <clIocIpi.h>

#define IOC_PORT 0
#define GMS_PORT CL_IOC_GMS_PORT

typedef enum
{
  NODE_JOIN_FROM_SC = 0,
  CLUSTER_NODE_ROLE_NOTIFY = 1,
  NODE_JOIN_FROM_CACHE = 2
} GroupMessageTypeT;

typedef enum
{
  ROLE_ACTIVE,
  ROLE_STANDBY
} GroupRoleNotifyTypeT;

typedef enum
{
  SEND_BROADCAST,
  SEND_TO_MASTER,
  LOCAL_ROUND_ROBIN
} GroupMessageSendModeT;

typedef enum
{
  GMS_MESSAGE = 1,
  AMF_MESSAGE = 2
} MessageHandlerCookie;

typedef struct
{
  GroupMessageTypeT  messageType;
  GroupRoleNotifyTypeT  roleType;
  char                data[1]; //Will be malloc on larger memory
} GroupMessageProtocolT;

/* Functions to process message from Master Node */
void nodeJoinFromMaster(GroupMessageProtocolT *msg);
void roleChangeFromMaster(GroupMessageProtocolT *msg);

/* Functions to process notification from AMF */
void nodeJoin(ClIocNodeAddressT nAddress);
void nodeLeave(ClIocNodeAddressT nAddress);
void componentJoin(ClIocAddressT address);
void componentLeave(ClIocAddressT address);
void elect();

/* Utility functions */
ClRcT timerCallback( void *arg );
ClRcT initializeServices();
ClRcT initializeClusterNodeGroup();
ClRcT  getNodeInfo(ClIocNodeAddressT nAddress, SAFplus::GroupIdentity *grpIdentity, int pid = 0);
bool  isMasterNode();
void fillSendMessage(void* data, GroupMessageTypeT msgType,GroupMessageSendModeT msgSendMode = SEND_BROADCAST, GroupRoleNotifyTypeT roleType = ROLE_ACTIVE);
void  sendNotification(void* data, int dataLength, GroupMessageSendModeT messageMode =  SEND_BROADCAST);
SAFplus::EntityIdentifier createHandleFromAddress(ClIocNodeAddressT nAddress, int pid = 0);
ClRcT iocNotificationCallback(ClIocNotificationT *notification, ClPtrT cookie);
/* Global variables */


#endif

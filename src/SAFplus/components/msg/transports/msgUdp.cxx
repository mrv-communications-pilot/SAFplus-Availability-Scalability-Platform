//#define _GNU_SOURCE // needed so that sendmmsg is available

#include <clMsgTransportPlugin.hxx>
#include <sys/socket.h>
#include "clPluginHelper.hxx"
#include <clCommon.hxx>  // For exceptions

namespace SAFplus
  {

  class Udp:public MsgTransportPlugin_1
    {
  public:
    MsgPool*  pool;
    Wakeable* wake;
    in_addr_t netAddr;
    Udp(); 

    virtual MsgTransportConfig& initialize(MsgPool& msgPool, Wakeable* notification);

    virtual MsgSocket* createSocket(uint_t port);
    virtual void deleteSocket(MsgSocket* sock);
    };

  class UdpSocket:public MsgSocket
    {
    public:
    UdpSocket(uint_t port,MsgPool* pool,MsgTransportPlugin_1* transport);
    virtual ~UdpSocket();
    virtual void send(Message* msg);
    virtual Message* receive(uint_t maxMsgs,int maxDelay=-1);

    protected:
    int sock;
    };


  Udp::Udp()
    {
    pool = NULL; wake = NULL;
    }

  MsgTransportConfig& Udp::initialize(MsgPool& msgPool, Wakeable* notification)
    {
    pool = &msgPool;
    wake = notification;

    config.nodeId = 0; // TODO
    config.maxMsgSize = SAFplusI::UdpTransportMaxMsgSize;
    config.maxPort    = SAFplusI::UdpTransportNumPorts;
    config.maxMsgAtOnce = SAFplusI::UdpTransportMaxMsg;

    char* interface = getenv("SAFPLUS_BACKPLANE_INTERFACE");
    char* ip = getenv("SAFPLUS_BACKPLANE_IP");
    if (!interface)
      {
      interface = "eth1";  // GAS REMOVE ME
      // temp comment out assert(!"Required env variable not defined");
      }
    if (ip)
      {
      // TODO: assign this IP to the interface and set the SAFPLUS_NODEADDR appropriately
      }
    else
      {
      struct in_addr bip = SAFplusI::devToIpAddress(interface);
      int nodeMask = 0xff;  // TODO: get this from ~SAFplusI::devNetMask(interface)
      config.nodeId = ntohl(bip.s_addr)&nodeMask;
      netAddr = ntohl(bip.s_addr)&(~nodeMask);
      }

    return config;
    }

  MsgSocket* Udp::createSocket(uint_t port)
    {
    if (port >= SAFplusI::UdpTransportNumPorts) return NULL;
    return new UdpSocket(port, pool,this);
    }

  void Udp::deleteSocket(MsgSocket* sock)
    {
    delete sock;
    }


   UdpSocket::UdpSocket(uint_t pt,MsgPool*  pool,MsgTransportPlugin_1* xp)
     {
     port = pt;
     msgPool = pool;
     transport = xp;
     node = xp->config.nodeId;

     if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) 
       {
       int err = errno;
       throw Error(Error::SYSTEM_ERROR,errno, strerror(errno),__FILE__,__LINE__);
       }

     struct sockaddr_in myaddr;
     memset((char *)&myaddr, 0, sizeof(myaddr));
     myaddr.sin_family = AF_INET;
     myaddr.sin_addr.s_addr = htonl(INADDR_ANY);  // TODO: bind to the interface specified in env var
     if (port == 0) // any port
       myaddr.sin_port = htons(0);
     else myaddr.sin_port = htons(port + SAFplusI::UdpTransportStartPort);

     if (bind(sock, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) 
       {
       int err = errno;
       throw Error(Error::SYSTEM_ERROR,errno, strerror(errno),__FILE__,__LINE__);
       }
     }

    UdpSocket::~UdpSocket()
      {
      close(sock);
      sock = -1;
      }

    void UdpSocket::send(Message* next)
      {
      mmsghdr msgvec[SAFplusI::UdpTransportMaxMsg];  // We are doing this for perf so we certainly don't want to new or malloc it!
      struct iovec iovecBuffer[SAFplusI::UdpTransportMaxFragments];
      mmsghdr* curvec = &msgvec[0];
      int msgCount = 0;
      int fragCount= 0;  // frags in this message
      int totalFragCount = 0; // total number of fragments
      Message* msg;
      MsgFragment* nextFrag;
      MsgFragment* frag;
      struct sockaddr_in to[SAFplusI::UdpTransportMaxMsg];
      //in_addr inetAddr;
      //inet_aton("127.0.0.1",&inetAddr);  // TODO create the real address
      //inetAddr.s_addr = htonl(((Udp*)transport)->netAddr | 

      do {
        msg = next;
        next = msg->nextMsg;  // Save the next message so we use it next

        struct iovec *msg_iov = iovecBuffer + totalFragCount;
        struct iovec *curIov = msg_iov;
        fragCount=0;
        nextFrag = msg->firstFragment;
        do {
          frag = nextFrag;
          nextFrag = frag->nextFragment;

          // Fill the iovector with messages
          curIov->iov_base = frag->data();     //((char*)frag->buffer)+frag->start;
          assert((frag->len > 0) && "The UDP protocol allows sending zero length messages but I think you forgot to set the fragment len field.");
          curIov->iov_len = frag->len;

          fragCount++;
          totalFragCount++;
          curIov++;
          } while(nextFrag);

        bzero(&to[msgCount],sizeof(struct sockaddr_in));
        to[msgCount].sin_family = AF_INET;
        to[msgCount].sin_addr.s_addr= htonl(((Udp*)transport)->netAddr | msg->node);
        to[msgCount].sin_port=htons(msg->port + SAFplusI::UdpTransportStartPort);

        curvec->msg_hdr.msg_controllen = 0;
        curvec->msg_hdr.msg_control = NULL;
        curvec->msg_hdr.msg_flags = 0;
        curvec->msg_hdr.msg_name = &to[msgCount];
        curvec->msg_hdr.msg_namelen = sizeof (struct sockaddr_in);
        curvec->msg_hdr.msg_iov = msg_iov;
        curvec->msg_hdr.msg_iovlen = fragCount;

        curvec++;
        msgCount++;
        } while (next != NULL);


      int retval = sendmmsg(sock, &msgvec[0], msgCount, 0);  // TODO flags
      if (retval == -1)
        {
        int err = errno;
        throw Error(Error::SYSTEM_ERROR,errno, strerror(errno),__FILE__,__LINE__);
        }
      else
        {
        assert(retval == msgCount);  // TODO, retry if all messages not sent
        printf("%d messages sent\n", retval);
        }

      // Your send routine releases the message whenever you are ready to do so
      MsgPool* temp = msg->pool;
      temp->free(msg);
      }

#if 0
tv.tv_sec = 10; /* seconds */
tv.tv_usec = 0;

if(setsockopt(socket, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv)) < 0)
        printf("Cannot Set SO_SNDTIMEO for socket\n");

if(setsockopt(socket, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) < 0)
        printf("Cannot Set SO_RCVTIMEO for socket\n");
#endif

//#define BUFSIZE 300
    Message* UdpSocket::receive(uint_t maxMsgs,int maxDelay)
      {

      // TODO receive multiple messages
      Message* ret = msgPool->allocMsg();
      MsgFragment* frag = ret->append(SAFplusI::UdpTransportMaxMsgSize);

      mmsghdr msgs[SAFplusI::UdpTransportMaxMsg];  // We are doing this for perf so we certainly don't want to new or malloc it!
      struct iovec iovecs[SAFplusI::UdpTransportMaxFragments];
      struct timespec timeoutMem;
      struct timespec* timeout;
      uint_t flags = MSG_WAITFORONE;

      if (maxDelay > 0)
        {
        timeout = &timeoutMem;
        timeout->tv_sec = maxDelay/1000;
        timeout->tv_nsec = (maxDelay%1000)*1000L;  // convert milli to nano, multiply by 1 million
        }
      else if (maxDelay == 0)
        {
        timeout = NULL;
        flags = MSG_DONTWAIT;
        }
      else 
        {
        timeout = NULL;
        }

      memset(msgs,0,sizeof(msgs));
      for (int i = 0; i < 1; i++)
        {
        // In an inline fragment the message buffer is located right after the MsgFragment object and shares some bytes with the buffer "pointer" (its not used as a pointer)
        if (frag->flags & SAFplus::MsgFragment::InlineFragment) iovecs[i].iov_base         = (void*) &frag->buffer;
        // If the fragment is not inline then the buffer variable works as a normal pointer.
        else iovecs[i].iov_base         = frag->buffer;

        iovecs[i].iov_len          = frag->allocatedLen;
        msgs[i].msg_hdr.msg_iov    = &iovecs[i];
        msgs[i].msg_hdr.msg_iovlen = 1;
        }

      int retval = recvmmsg(sock, msgs, 1, flags, timeout);
      if (retval == -1)
        {
        int err = errno;
        ret->pool->free(ret);  // clean up this unused message.  TODO: save it for the next receive call
        if (errno == EAGAIN) return NULL;  // its ok just no messages received.  This is a "normal" error not an exception
        throw Error(Error::SYSTEM_ERROR,errno, strerror(errno),__FILE__,__LINE__);
        }
      else
        {
#if 0  // Its possible to send a zero length message!  If that happens you'll receive it!  Did you forget to set the len field of your fragment?
        if ((retval==1)&&(msgs[0].msg_len==0))  // Got one empty message.  Not sure why this happens
          {
          ret->pool->free(ret);
          return NULL;
          }
#endif

        //printf("%d messages received. [%s]\n", retval,(char*) &frag->buffer);
        Message* cur = ret;
        for (int msgIdx = 0; (msgIdx<retval); msgIdx++,cur = cur->nextMsg)
          {
          int msgLen = msgs[msgIdx].msg_len;
          MsgFragment* curFrag = cur->firstFragment;
          for (int fragIdx = 0; (fragIdx < msgs[msgIdx].msg_hdr.msg_iovlen) && msgLen; fragIdx++,curFrag=curFrag->nextFragment)
            {
            // Apply the received size to this fragment.  If the fragment is bigger then the entire msgLen must be in this buffer
            if (curFrag->allocatedLen >= msgLen)
              {
              curFrag->len = msgLen;
              msgLen=0;
              }
            else // If the fragment is smaller, the buffer is full and reduce the size of the msgLen temporary by the amount in this buffer
              {
              curFrag->len = curFrag->allocatedLen;
              msgLen -= curFrag->allocatedLen;
              }
            }
          }
        }

      return ret;
      }

  static Udp api;
  };


extern "C" SAFplus::ClPlugin* clPluginInitialize(uint_t preferredPluginVersion)
  {
  // We can only provide a single version, so don't bother with the 'preferredPluginVersion' variable.

  // Initialize the pluginData structure
  SAFplus::api.pluginId         = SAFplus::CL_MSG_TRANSPORT_PLUGIN_ID;
  SAFplus::api.pluginVersion    = SAFplus::CL_MSG_TRANSPORT_PLUGIN_VER;
  SAFplus::api.type = "UDP";

  // return it
  return (SAFplus::ClPlugin*) &SAFplus::api;
  }

#pragma once
#include <boost/thread.hpp>
#include <clMsgBase.hxx>
#include <ReliableFragment.hxx>
#include <boost/unordered_map.hpp>

//TODO
u_int RELIABLE_MSG_TYPE = 0x50;
static u_int MAX_FRAGMENT_NUMBER        = 255;

namespace SAFplus
{

  enum connectionNotification
  {
    OPENED=0,
    REFUSED,
    CLOSE,
    FAILURE,
    RESET
  };

  enum connectionState
  {
    CONN_CLOSED      = 0, /* There is not an active or pending connection */
    CONN_SYN_RCVD, /* Request to connect received, waiting ACK */
    CONN_SYN_SENT, /* Request to connect sent */
    CONN_ESTABLISHED, /* Data transfer state */
    CONN_CLOSE_WAIT /* Request to close the connection */
  };

  class queueInfomation
  {
  public:
    queueInfomation()
    {
      fragNumber =0;
      lastFrag=0;
      numberOfCumAck=0;
      numberOfOutOfSeq=0;
      numberOfNakFrag=0; /* Outstanding segments counter */
    }

    int nextSequenceNumber()
    {
      fragNumber = fragNumber+1;
      return fragNumber;
    }

    int setSequenceNumber(int n)
    {
      fragNumber = n;
      return fragNumber;
    }

    int setLastInSequence(int n)
    {
      lastFrag = n;
      return lastFrag;
    }

    int getLastInSequence()
    {
      return lastFrag;
    }

    void increaseCumulativeAckCounter()
    {
      numberOfCumAck++;
    }

    int getCumulativeAckCounter()
    {
      return numberOfCumAck;
    }

    int getAndResetCumulativeAckCounter()
    {
      int tmp = numberOfCumAck;
      numberOfCumAck = 0;
      return tmp;
    }

    void increaseOutOfSequenceCounter()
    {
      numberOfOutOfSeq++;
    }

    int getOutOfSequenceCounter()
    {
      return numberOfOutOfSeq;
    }

    int getAndResetOutOfSequenceCounter()
    {
      int tmp = numberOfOutOfSeq;
      numberOfOutOfSeq = 0;
      return tmp;
    }

    void incOutstandingFragmentsCounter()
    {
      numberOfNakFrag++;
    }

    int getOutstandingFragmentsCounter()
    {
      return numberOfNakFrag;
    }

    int getAndResetOutstandingFragmentsCounter()
    {
      int tmp = numberOfNakFrag;
      numberOfNakFrag = 0;
      return tmp;
    }

    void reset()
    {
      numberOfOutOfSeq = 0;
      numberOfNakFrag  = 0;
      numberOfCumAck   = 0;
    }
    int fragNumber;             /* Fragment sequence number */
    int lastFrag;   /* Last in-Fragment received segment */
    /*
     * The receiver maintains a counter of unacknowledged segments received
     * without an acknowledgment being sent to the transmitter. T
     */
    int numberOfCumAck; /* Cumulative acknowledge counter */

    /*
     * The receiver maintains a counter of the number of segments that have
     * arrived out-of-sequence.
     */
    int numberOfOutOfSeq; /* Out-of-sequence acknowledgments counter */

    /*
     * The transmitter maintains a counter of the number of segments that
     * have been sent without getting an acknowledgment. This is used
     * by the receiver as a mean of flow control.
     */
    int numberOfNakFrag; /* Outstanding segments counter */
  };
  enum TimerStatus
  {
    TIMER_RUN =0,
    TIMER_PAUSE
  };
  class SAFplusTimer
  {
  public:
    bool isStop;
    TimerStatus status;
    SAFplus::Mutex timerLock;
    int interval;
  };

  class MsgSocketReliable : public MsgSocketAdvanced //, SAFPlusLockable
  {
  private:
    /*
     * When this timer expires, the connection is considered broken.
     */
    int sendQueueSize = 32; /* Maximum number of received segments */
    int recvQueueSize = 32; /* Maximum number of sent segments */
    int sendBufferSize;
    int recvBufferSize;
    bool isClosed    = false; //socket status closed
    bool isConnected = false; //socket status connected
    bool isReset     = false; //socket status reset
    bool iskeepAlive = true; //socket status keep alive
    int  state     = connectionState::CONN_CLOSED;
    int  timeout   = 0; /* (ms) */ //wait to receive fragment
    queueInfomation queueInfo; //socket queue Infomation
    boost::thread rcvThread; //thread to receive and handle fragment
    ReliableFragmentList unackedSentQueue; // list of fragment sended without receive ACK
    ReliableFragmentList outOfSeqQueue;  // list of out-of-sequence fragments
    ReliableFragmentList inSeqQueue; // list of in-sequence fragments
    SAFplus::Mutex closeMutex;
    SAFplus::Mutex resetMutex;
    ThreadCondition resetCond;
    SAFplus::Mutex recvQueueLock;
    ThreadCondition recvQueueCond;
    SAFplus::Mutex unackedSentQueueLock;
    ThreadCondition unackedSentQueueCond;
    SAFplus::Mutex thisMutex;
    ThreadCondition thisCond;

    //Handle close socket
    void handleCloseImpl(void);
    //process fragment : push fragment to in-sequence or out-of-sequence queue
    void handleReliableFragment(ReliableFragment frag);
    // handle SYN fragment : update connection profile, update connection state
    void handleSYNReliableFragment(SYNFragment *frag);
    //Handle ACK fragment
    void handleACKReliableFragment(ReliableFragment *frag);
    //Handle NAK fragment : Removed acknowledged fragments from unacked-sent queue
    void handleNAKReliableFragment(NAKFragment *frag);
    //Checks for in-sequence segments in the out-of-sequence queue that can be moved to the in-sequence queue
    void checkRecvQueues(void);
    // Send acknowledged fragment to sender
    void sendACK();
    // Send list of received fragment id in out of sequence queue to sender
    void sendNAK();
    // Send the last received fragment id to sender (out-of-sequence is empty)
    void sendSingleAck();
    // no used
    void sendSYN();
    // Piggy back any pending acknowledgments : Sets the ACK flag and number of a segment if there is at least one received segment to be acknowledged.
    void setACK(ReliableFragment *frag);
    // ????
    void getACK(ReliableFragment *frag);
    static int nextSequenceNumber(int seqn);
    //Thread to receive fragment
    //static void ReliableSocketThread(void * arg);
    //send a reliable fragment
    void sendReliableFragment(ReliableFragment *frag);
    // send fragment and store it in uncheck ack
    void queueAndSendReliableFragment(ReliableFragment* frag);
    //Handle Retransmission un-ack fragment
    void retransmitFragment(ReliableFragment* frag);
    // set connection state
    void setconnection(connectionNotification state);
    void connectionOpened(void);
    //initial a reliable socket : start thread to receive fragment
    void init();

  public:
    void handleReliableSocketThread(void);
    Handle destination; //destination of this connection (node id, port)
    uint_t messageType; //type of the message
    ReliableSocketProfile* profile; //socket connection profile
    SAFplusTimer nullFragmentTimer; //If this timer expired , send null fragment if unackedQueue is empty
    SAFplusTimer retransmissionTimer; //If this timer expired, retransmission all un-ack fragment
    SAFplusTimer cumulativeAckTimer;//If this timer expired, send acknowledge fragment to sender
    SAFplusTimer keepAliveTimer; // TODO
    boost::intrusive::list_member_hook<> m_reliableSocketmemberHook;
    //receive fragment from socket
    virtual ReliableFragment* receiveReliableFragment(Handle &handle);
    MsgSocketReliable(uint_t port,MsgTransportPlugin_1* transport);
    MsgSocketReliable(uint_t port,MsgTransportPlugin_1* transport,Handle destination);
    MsgSocketReliable(MsgSocket* socket);
    virtual ~MsgSocketReliable();
    // Send a bunch of messages.  You give up ownership of msg.
    virtual void send(Message* msg);
    //Send a buffer data 
    virtual void send(SAFplus::Handle destination, void* buffer, uint_t length,uint_t msgtype);
    //Receiver a message
    virtual Message* receive(uint_t maxMsgs,int maxDelay=-1);
    virtual void flush();
    //Add socket client to socket  server list 
    virtual void connectionClientOpen(MsgSocketReliable* sock){};
    //read maximum len byte data
    int readReliable(Byte* buffer, int offset, int len);
    //write maximum len byte data
    void writeReliable(Byte* buffer, int offset, int len);
    //connect to destination
    void connect(Handle destination, int timeout);
    //close socket
    void close(void);
    void closeImpl();
    static void closeImplThread(void*);
    //Puts the connection in a closed state and notifies
    void connectionFailure();
    void handleRetransmissionTimerFunc(void);
    void handleNullFragmentTimerFunc(void);
    void handleCumulativeAckTimerFunc(void);
    void handleKeepAliveTimerFunc(void);
    void handleReliableFragment(ReliableFragment *frag);
  };


  //The disposer object function
  struct delete_disposer
  {
    void operator()(ReliableFragment *delete_this)
    {
      delete delete_this;
    }
  };
  typedef member_hook<MsgSocketReliable, list_member_hook<>,
      &MsgSocketReliable::m_reliableSocketmemberHook> ReliableSocketMemberHookOption;
  typedef list<MsgSocketReliable, ReliableSocketMemberHookOption> ReliableSocketList;

  class MsgSocketServerReliable;

  class MsgSocketClientReliable : public MsgSocketReliable
  {
  public:
    MsgSocketServerReliable *sockServer;
    MsgSocketClientReliable(MsgSocket* socket) : MsgSocketReliable(socket)
    {
    };
    MsgSocketClientReliable(MsgSocket* socket,Handle destinationAddress) : MsgSocketReliable(socket)
    {
      destination=destinationAddress;
    };
    virtual ReliableFragment* receiveReliableFragment(Handle &handle);
    void receiverFragment(ReliableFragment* frag);
    virtual void connectionClientOpen(void* sock);
  };

  class MsgSocketServerReliable : public MsgSocketAdvanced
  {
    int timeout;
    bool isClosed;
    boost::thread ServerRcvThread;
    void removeClientSocket(Handle destAddress);
    void addClientSocket(Handle destAddress);
    void handleRcvThread();
  public:
    void init();
    static void rcvThread(void * arg);
    MsgSocketServerReliable(uint_t port,MsgTransportPlugin_1* transport);
    MsgSocketServerReliable(MsgSocket* socket);
    ReliableSocketList listenSock;
    ThreadCondition listenSockCond;
    SAFplus::Mutex listenSockMutex;
    ReliableFragmentList fragmentQueue;
    SAFplus::Mutex fragmentQueueLock;
    ThreadCondition fragmentQueueCond;
    MsgSocketClientReliable* accept();
    typedef boost::unordered_map < SAFplus::Handle, MsgSocketClientReliable*, boost::hash<SAFplus::Handle>, std::equal_to<SAFplus::Handle> > HandleSockMap;
    HandleSockMap clientSockTable;
  };
};
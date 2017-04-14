//QueueWrapper.h
/*
  class: QueueWrapper
  -uses SystemV message queue API

  Author: Karl (Speed) Redman
*/
//#ifndef _QUEUEWRAPPER_H_

#ifndef POSIX_SOURCE
#define POSIX_SOURCE 1

#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 199506L
#endif

#endif //end POSIX_SOURCE


#ifdef __linux__

#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE 1
#endif

#endif //end linux



#include <sys/types.h>
//#include <sys/ipc.h>
//#include <sys/msg.h>

/* DEFINITIONS */

//Q TYPES
#define Q_CREATOR 	0x1	/* exclusive creator of a queue */
#define Q_CLIENT	0x2	/* attach to an existing queie*/

#define Q_BLOCKING	0x4	/* a blocking read or write used for
				   ORing with either a Q_CREATOR or a
				   Q_CLIENT*/
#define Q_NO_BLOCKING   0x8	/* a non-blocking read or write used
				   for ORing with either Q_CREATOR or
				   a Q_CLIENT*/


//PERMISSIONS & SIZES
#define Q_DEFAULT_PERM	0660	/* owner and group have rw permissions */
#define Q_IPC_PRIVATE	0000	/* make a process private queue */
#define Q_MAX_SIZE	4096	/* something most systems allow */
#define Q_PMAX_TRIES	2	/* max tries for the producer to
				   attach to a que */
//ERRORS
#define QERR_SUCCESS		0	/* successfull call */
#define QERR_SIZE_TOO_BIG	500	/* size specified for max size of q
					   buf too big */
#define QERR_MEM_ALLOC		501	/* memory allocation error */ 
#define QERR_QTYPE		502	/* bad queue attach type */
#define QERR_KEY		503	/* key creation failed */
#define QERR_UNKNOWN		504	/* unknown error */
#define QERR_INIT		505	/* int() failed to attach */
#define QERR_ATTACH		506	/* failed to get que from
					   system*/
#define QERR_DETACH		507	/* failed to remove que from
					   system*/
#define QERR_MAX_ATTACH		508	/* max attempts to attach
					   reached and failed*/

					  
/* STRUCTURES */

//SysV msg queue structure
typedef struct {
  long int type;
  char *buffer;
}q_message;

//internal message
typedef struct {
  q_message qm;
  int qmbufsz;
  int qmsgsz;
}QMESSAGE;

typedef struct
{
  key_t key;
  int perms;
  int qtype;
  int quesz;
  int priority;
  int blocking;
  int msqid;
}Q_INFO;


class QueueWrapper
{

 public:
  /* 
     -keystr is a null terminated string. If keystr is NULL then the
     queue is created as IPC_PRIVATE. 
     -qtype is the type of queue (see Q TYPES). 
     -qperms is the permissions on the queue (user configurable).
  */
  QueueWrapper(char *keystr, const int qtype, const int qperms);

  /*
    -key is an ftok() returned key (assumed to be valid). key may be
    ORed with IPC_PRIVATE (just like msgget()).
    -queuesz is the max size of the que for a receive (default is
    4096).
  */
  //QueueWrapper(key_t key, const qtype, const qperms, int queuesz);

  ~QueueWrapper();

  /* create que, etc. This is the main entrypoint. if rmQ is called
     after an init is called, init() may be called again to create a
     new queue */
  int init();


  /* DATA MANIPULATIONS */

  /* send a buffer:
     -buffer is the data we're sending
     -bufsz is the size of the buffer
     -pri is the priority of the message (also known as the message type)
     -msgflg specifies blocking or nonblocking
     -qm is a user's QMESSAGE
  */
  //int send(char *buffer, int bufsz, int pri, int msgflg);
  //int send(QMESSAGE *qm, int msgflg);
  //int send(QMESSAGE *qm);

  //int msgsnd(int msqid, struct msgbuf *msgp, int msgsz, int msgflg );

  /* recieve a message:
     -msgsz is the size of the max size of the message
     -pri is the type (or priority) of message you want to grab 
     -msgflg specifies blocking or nonblocking
  */
  //QMESSAGE *recv(int  msgsz, long pri, int msgflg );
  //QMESSAGE *recv(long pri, msgflg);
  //QMESSAGE *recv();

  //return a pointer to the current QMESSAGE
  //QMESSAGE *getQMsg();

  /* set users QMESSAGE pointer from our stored NOTE: user responsible
     for delet of mem*/
  //QMESSAGE *getQMsg(QMESSAGE *qm); 


  /* MSG QUEUE CONTROL FUCNTIONS */
  //get msg queue data sructure status or state info
  //msqid_ds *ds_status();

  //set msg queue data structure
  //int ds_set(msqid_ds *buf);

  //remove message que (only createor or owner can do this!)
  //int rmQ();
  
  //set max size of a received message (dynamic mem)
  int set_quesz(int size);

  //set functionality to blocking or nonblocking
  int set_blocking(const int type);

  //set priority of send or recv messages
  //void set_priority(int type);

  int get_error(){return lasterror;}


 private:
  QMESSAGE *msg;
  //msqid_ds *qid_ds;
  Q_INFO qinfo;


  int lasterror;

  //how the que gets created
  int create_producer();
  int create_client();
};

//#endif

/*
  class: QueueWrapper
  -uses SystemV message queue API

  Author: Karl (Speed) Redman
*/

#include <QueueWrapper.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include <errno.h>
#include <string.h>

#ifndef NULL
#include <malloc.h>
#endif

//TEMPORARY
#include <stdio.h>


QueueWrapper::
QueueWrapper(char *keystr, const int qtype, const int qperms):
  lasterror(0),
  msg(NULL)
{
  //initalize internal queue info structure
  memset(&qinfo, 0, sizeof(qinfo));

  //key generation
  if(keystr == NULL)
    {
      qinfo.key = (key_t)IPC_PRIVATE;
    }
  else
    {
      char proj = 0;
      int i = 0;

      //create key from keyname
      for(i=0; i < strlen(keystr);i++)
	{
	  proj += keystr[i];
	}
      
      if( (qinfo.key = ftok(".", proj)) == -1)
	{
	  qinfo.key = 0;
	  lasterror = QERR_KEY;
	  return;
	}
    }//end else

  //set up queue permissions
  if(qperms == Q_IPC_PRIVATE)
    {
      qinfo.perms = IPC_PRIVATE;
    }
  else
    {
      //user permissions
      qinfo.perms = (int)qperms;
    }

  //determin the quetype
  if((qtype & Q_CREATOR) == Q_CREATOR)
    {
      printf("Q_CREATOR\n");
      qinfo.qtype = Q_CREATOR;
      qinfo.perms |= IPC_CREAT | IPC_EXCL;
    }
  else
    if((qtype & Q_CLIENT) == Q_CLIENT)
     {
      printf("Q_CLIENT\n");
       qinfo.qtype = Q_CLIENT;
       //qinfo.perms |= IPC_CREAT;
     }
  else
    printf("qinfo.qtype not set\n");

  //figure out blocking 
 if((qtype & Q_NO_BLOCKING) == Q_NO_BLOCKING)
     {
       qinfo.blocking = IPC_NOWAIT;
     }
   else
     if((qtype & Q_BLOCKING) == Q_BLOCKING)
     {
       qinfo.blocking = 0;
     }

  //create a QMESSAGE for internal use
  if( (msg = new QMESSAGE) == NULL)
    {
      lasterror = QERR_MEM_ALLOC;
      return;
    }

  //set the max size of the messages
  set_quesz(Q_MAX_SIZE);

  //catch all messsages
  qinfo.priority = 0;
  msg->qm.type = qinfo.priority;
  
  lasterror = QERR_SUCCESS;
  return;
}

QueueWrapper::
~QueueWrapper()
{
  if(msg->qm.buffer != NULL)
    { delete [] msg->qm.buffer; }

  if(msg != NULL)
    { delete msg; }

  //remove self form queue list (try to delete queue)
  msgctl(qinfo.msqid, IPC_RMID, NULL);
}

int QueueWrapper::
init()
{
  /* 
     create a queue: special instructions based on Q_type
     note: lasterror may get set by called functions
  */ 
  switch(qinfo.qtype)
    {
    case Q_CREATOR:
      return(create_producer());
      break;
    case Q_CLIENT:
      return(create_client());
      break;
    default:
      break;
    }
  lasterror = QERR_INIT;
  return -1;
}

/* set the max size of the internal message buffer */
int QueueWrapper::
set_quesz(int size)
{
  if( size < Q_MAX_SIZE)
    {
	{
	  delete [] msg->qm.buffer;
	}

      if( (msg->qm.buffer = new char [size]) == NULL)
	{
	  return(QERR_MEM_ALLOC);
	}
      else
	{ 
	  msg->qmbufsz = size;
	  return(QERR_SUCCESS); 
	}
    }
  else
    return(QERR_SIZE_TOO_BIG);
}
  
int QueueWrapper::
set_blocking(const int type)
{ 
  if(type == Q_BLOCKING || type == Q_NO_BLOCKING)
    { 
      qinfo.blocking = type; 
      return 0;
    } 
  lasterror = QERR_UNKNOWN;
  return -1;
}
  
int QueueWrapper::
create_producer()
{
  int max_try_counter = 0;
  int i = 0;

 PRODUCER_MSGGET:
  if( (qinfo.msqid = msgget(qinfo.key, qinfo.perms)) == -1)
    {
      switch(errno)
	{
	case EACCES:
	case EEXIST:
	  //attemp to delete resource and try again
	  printf("Producer msgget: resource already exists, attemting"
		 "reset\n");
	  fflush(NULL);
	  
	  //attach to current resource
	  if( (qinfo.msqid = msgget(qinfo.key, IPC_CREAT)) == -1)
	    {
	      //fatal error
	      perror("Producer, msgget");
	      lasterror = QERR_ATTACH;
	      return(-1);
	    }
	  else
	    {
	      if(max_try_counter < Q_PMAX_TRIES)
		{
		  //...attached. now delete and try again
		  if(msgctl(qinfo.msqid, IPC_RMID, NULL) < 0)
		    {
		      //fatal error
		      perror("Producer, msgctl");
		      lasterror = QERR_DETACH;
		      return(-1);
		    }
		  else
		    {
		      //resource deleted, try again
		      goto PRODUCER_MSGGET;
		    }
		}//end if
	      else
		{
		  //too many tries
		  //fatal error
		  perror("Producer, msgget TOO MANY");
		  lasterror = QERR_MAX_ATTACH;
		  return(-1);
		  //pthread_exit(&msid);
		}
	    }//end else
	 
	  break;
	case EIDRM:
	case ENOENT:
	case ENOMEM:
	case ENOSPC:
	default:
	  //fatal error
	  perror("Producer, msgget; detaching");
	  printf("errno = %d\n", errno);
	  msgctl(qinfo.msqid, IPC_RMID, NULL);
	  lasterror = QERR_UNKNOWN;
	  return(-1);
	  break;
	}//end switch
    }//end if

  printf("producer msgget:SUCCESS\n");
  return(0);

}

int QueueWrapper::
create_client()
{
  if( (qinfo.msqid = msgget(qinfo.key, qinfo.perms)) == -1)
    {
      switch(errno)
	{
	case EACCES:
	case EIDRM:
	case ENOENT:
	default:
	  //fatal error
	  perror("Consumer, msgget");
	  printf("errno = %d\n", errno);
	  lasterror = QERR_ATTACH;
	  return(-1);
	  break;
	}//end switch
    }//end if

  printf("Consumer msgget:SUCCESS\n");
  return(0);
}

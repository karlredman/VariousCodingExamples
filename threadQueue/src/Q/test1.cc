#define POSIX_SOURCE 1
#define _POSIX_C_SOURCE 199506L

#ifdef __linux__
	#define _XOPEN_SOURCE
#endif

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include <pthread.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>



#define MQ_BUFF_SIZE 256
#define MQ_SIZE 2048


#define NUM_THREADS 2
#define PRODUCER_MAX_TRIES 2

void *producer(void *);
void *consumer(void *);

typedef struct {
  long int type;
  char buffer[MQ_BUFF_SIZE];
}MESSAGE;


pthread_mutex_t msgq_mutex = PTHREAD_MUTEX_INITIALIZER;
key_t msgq_key;

int keep_alive = 1;

int main()
{
  pthread_t prodtid, constid;

  //create message queue key
  if( (msgq_key = ftok(".", ('v'+'e'+'r'+'a'+'s'+'c'+'a'+'p'+'e'))) == -1)
    {
      perror("key generation");
      exit(1);
    }

  //lock the consumer until resources are allocated
  pthread_mutex_lock(&msgq_mutex);

  //create threads
  pthread_create(&prodtid, NULL, producer, NULL);
  pthread_create(&constid, NULL, consumer, NULL);

  //join threads
  pthread_join(prodtid, NULL);
  pthread_join(constid, NULL);

  return(EXIT_SUCCESS);
}


void *producer(void *)
{
  int max_try_counter = 0;
  int ret_val = 0;
  int msid;
  int i = 0;
  MESSAGE Q;


 PRODUCER_MSGGET:
  if( (msid = msgget(msgq_key, IPC_CREAT | IPC_EXCL | 0660)) == -1)
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
	  if( (msid = msgget(msgq_key, IPC_CREAT)) == -1)
	    {
	      //fatal error
	      perror("Producer, msgget");
	      return(&msid);
	      //pthread_exit(&msid);
	    }
	  else
	    {
	      if(max_try_counter < PRODUCER_MAX_TRIES)
		{
		  //...attached. now delete and try again
		  if(msgctl(msid, IPC_RMID, NULL) < 0)
		    {
		      //fatal error
		      perror("Producer, msgctl");
		      return(&msid);
		      //pthread_exit(&msid);
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
		  return(&msid);
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
	  msgctl(msid, IPC_RMID, NULL);
	  return(&msid);
	  //pthread_exit(&msid);
	  break;
	}//end switch
    }//end if

  printf("producer msgget:SUCCESS\n");

  //let client know we're ready to go
  pthread_mutex_unlock(&msgq_mutex);


  while(keep_alive)
    {
      memset(Q.buffer, 0, sizeof(Q.buffer));

      //put something into Q.buffer
      sprintf(Q.buffer, "Q.buffer =  %d / %d", i, i%100);
      Q.type = 1;

      i++;

      //send the message (no waiting)
      /* note: the size of the data being sent would normally
	 have to be calculated
      */
      if(msgsnd(msid, &Q, strlen(Q.buffer),IPC_NOWAIT) == -1)
	{
	  switch(errno)
	    {
	    case EAGAIN:
	      /* queue is full -waiting for client to remove something
		 NOTE: this will unlocked only when either the client
		 unlocks or if the thread is terminated by some other
		 mechanism
	      */
	      printf("\n producer blocked...\n");
	      fflush(NULL);
	      pthread_mutex_unlock(&msgq_mutex);
	      sleep(1);
	      break;
	    default:
	      //fatal error
	      perror("Producer msgsnd");
	      return(&ret_val);
	      //pthread_exit(&ret_val);
	      break;

	    }//end switch
	}

    }//end while


  //remove queue
  if(msgctl(msid, IPC_RMID, NULL) < 0)
    {
      perror("Producer, msgctl");
    }

  return(&ret_val);

}//end producer()


void *consumer(void *)
{
  int ret_val = 0;
  int msid;
  char buffer[1024];
  int i= 0;

  //wait for producer to initialize
  pthread_mutex_unlock(&msgq_mutex);

  if( (msid = msgget(msgq_key, 0)) == -1)
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
	  return(&msid);
	  break;
	}//end switch
    }//end if

  printf("Consumer msgget:SUCCESS\n");


  while(keep_alive)
    {
      /* get data from producer from queue
	 critical section in case producer needs to block
       */
      memset(buffer, 0, sizeof(buffer));

      pthread_mutex_lock(&msgq_mutex);

      if(msgrcv(msid, buffer, MQ_SIZE, 0, 0 ) == -1)
	{
	  perror("consumer msgrcv");
	  pthread_mutex_unlock(&msgq_mutex);
	  printf("errno = %d\n", errno);
	  break;
	}

      pthread_mutex_unlock(&msgq_mutex);
      
      printf("value of buffer is :%s\n", ((MESSAGE *)buffer)->buffer);

      if( ((i%100) == 0) && (i != 0))
	{
	  printf("sleeping...\n");
	  sleep(5);
	  fflush(NULL);
	  i=0;
	}
	else
	  {
	    i++;
	  }
    }

  //exit cleanly
  return(&ret_val);
}
 
 
void *hbeat_motitor(void *)
{
  return(NULL);
}     
     

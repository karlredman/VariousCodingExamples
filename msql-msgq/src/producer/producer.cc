//producer.cc
#include <QueueWrapper.h>

#include <stdio.h>

#include <pthread.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include <errno.h>


pthread_mutex_t msgq_mutex = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char **argv)
{
  int retval = 0;

  //lock any clients from trying to attach until que is created
  //pthread_mutex_lock(&msgq_mutex);

  //create Q obj: create queue
  QueueWrapper *Q = new QueueWrapper("verascape", Q_CLIENT,
				     Q_DEFAULT_PERM);
  
  retval = Q->init();
  printf("Q->init() returns %d:lasterror = %d\n", retval,
	 Q->get_error());

/*
  while(true)
  {
  Q->send(
  }
*/
  delete Q;
  return 0;
}

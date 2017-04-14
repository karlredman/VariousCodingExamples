//Thread.cc

#include <mThread.h>

#include <pthread.h>

#include <stdio.h>
#include <unistd.h>

/* for use when we want to use this as a regular class
 */ 
mThread::mThread(void *func, void *args):
  attr(NULL)
{
  pthread_create(&tid, attr, (void *(*)(void *))func, (void *)args);
}

/* for use when we want to use this class as a parent
 */
mThread::mThread()
{
}

/* for use when we want to use this class as a parent
 */
int
mThread::run()
{
  return(pthread_create(&tid, attr, (void *(*)(void *))thread_func, 
			(void *)args));
}

int
mThread::join(void **ret)
{
  return(pthread_join(tid, ret));
}

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
  //create a thread using func and args
  pthread_create(&tid, attr, (void *(*)(void *))func, (void *)args);
}

/* for use when we want to use this class as a parent
 */
mThread::mThread()
{
  //nothing to worry about here
}

/* for use when we want to use this class as a parent
 */
int
mThread::run()
{
  //create a thread using func and args
  return(pthread_create(&tid, attr, (void *(*)(void *))thread_func, 
			(void *)args));
}

int
mThread::join(void **ret)
{
  //join on the thread
  return(pthread_join(tid, ret));
}

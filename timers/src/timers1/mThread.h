//Thread.h

/* A basic Thread class implimentation
 */

#ifndef __MTHREAD_H__
#define __MTHREAD_H__

#include <pthread.h>

class mThread
{
 public:

  // Constructor for use as a basic thread
  mThread(void *func, void * args);

  // Constructor for use in derived classes
  mThread();

  // run function for use with derived classes
  int run();
  
  // plain old join 
  int join(void **ret);


  void			*thread_func; /* a pointer to the function
					 called by the thread */

  pthread_t		tid;	/*thread ID*/
  pthread_attr_t	*attr;	/*thread attributes*/

  void			*args;	/* thread function arguments */
};

#endif

//Thread.h

#include <pthread.h>

class mThread
{
 public:
  mThread(void *func, void * args);
  mThread();

  int run();
  
  int join(void **ret);

  void			*thread_func;
  pthread_t		tid;
  pthread_attr_t	*attr;
  void *args;
};

/*!\file C_ThreadDeath.cc
  Example class that manages threads and the detection of their exits
  through the use of condition variables.
*/


#include "debug.h"
#include "C_ThreadDeath.h"

ThreadMgr::ThreadMgr()
{
  m_threadData = new ThreadData();
}



ThreadMgr::~ThreadMgr()
{
  //delete thread data
  delete m_threadData;
}

int 
ThreadMgr::cancelThread(pthread_t *tid)
{
  return pthread_cancel(*tid);
}

/**
   \return SUCESS = thread ID of thread, FAIL = NULL

   \param thread_func user defined function to call when thread is
   started 
   \param arg user defined argument (passed to thread_func)
   
   \todo return type should be a const!!!
*/
int 
ThreadMgr::createThread(pthread_t *tid, pthread_attr_t *attr, void *(*thread_func)(void *), void *arg)
{
  int ret_val = 0;

  func_params *params = new func_params;
  params->thread_func=thread_func;
  params->arguments=arg;
  params->thisObj=this;

  pthread_t tmp_tid;
  ret_val = pthread_create(&tmp_tid, (pthread_attr_t *) attr, this->func, (void *)params);
  *tid = tmp_tid;

  //std::cout << "createThread:self="<<pthread_self()<<",tid="<<*tid<<std::endl;

  if(ret_val == 0)
    {
      m_threadData->addThread(tid, arg);
    }

  return ret_val;
}

int
ThreadMgr::createThread(void *(*thread_func)(void *), void *arg)
{
  pthread_t tid;
  return ( createThread(&tid, NULL, thread_func, arg) );
}


/**
   \return SUCCESS = return is 0 and thread_return is non NULL, FAIL =
   return is non-zero [see pthread_join()] and thread_return is NULL

   \param tid the thread id to join
   \param thread_return a pointer to the return value of the user
   defined thread function
*/
int 
ThreadMgr::joinThread(pthread_t tid, void **thread_return)
{
  int ret = 0;

  //ret = pthread_join(tid, thread_return);

  //char *pc = ((char *)(char *)*thread_return);
  //std::cout << "join:" << tid << "|" << pc << std::endl;
  if( (ret = pthread_join(tid, thread_return)) == 0)
    {
      m_threadData->removeThread(tid);
    }
  
  return ret;
}

pthread_t
ThreadMgr::joinThread(void **thread_return)
{
  //wait for a thread to terminate

  //join terminated thread

  //return a copy of the thread id (slow)
  return (pthread_t)0;
}

void *
ThreadMgr::func(void *arg)
{

  /** \note user does a joinThread to remove thread from managed list
   */

  //get the object pointer
  func_params *param = (func_params *)arg;
  
  //register thread with current object
  pthread_t t = pthread_self();
  param->thisObj->m_threadData->addThread(&t, param->arguments);

  //call user's thread function
  void *return_value = param->thread_func(param->arguments);

  //std::cout << "func:" << pthread_self() << "|" << (char *)return_value << std::endl;

  //do pthread_exit with user's thread func. ret. val.
  pthread_exit((void *)return_value);

  return return_value;			// we never get here!!!
}

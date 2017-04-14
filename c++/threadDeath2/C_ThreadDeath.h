/*!\file C_ThreadDeath.h
  Example class that manages threads and the detection of their exits
  through the use of condition variables.
*/

#include <map>
#include <pthread.h>

struct ThreadArgs
{
  void *(*user_func)(void *);
  void *user_func_arg;
  //ThreadMgr *mgr;
};

typedef std::pair<std::_Rb_tree_iterator<std::pair<const pthread_t, void*>, 
					 std::pair<const pthread_t, void*>&, 
					 std::pair<const pthread_t, void*>*>, 
		  bool> ThreadDataIterator;

class ThreadData
{
 public:
  ThreadData()
    {
      static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; 
      m_mutex = &mutex; 
    }

  ~ThreadData()
    {
      //erase all m_data elements
      //for(blah, blah, blah)
      //delete fooBlah;
    }

  //ThreadDataIterator addThread(pthread_t *tid, void *arg)
  int addThread(pthread_t *tid, void *arg)
    {
      //lock the data mutex
      pthread_mutex_lock(m_mutex);

      //add the thread to the mutex
      //ThreadDataIterator pos = m_data.insert(std::make_pair(*tid, arg));
      this->m_data.insert(std::make_pair(*tid, arg));

      //unlock the data mutex
      pthread_mutex_unlock(m_mutex);

      return 0;
    }

  int removeThread(pthread_t tid)
    {
      //lock the data mutex
      pthread_mutex_lock(m_mutex);

      //delete user function argument -must check size!
      //delete m_data.find(*tid)->second;

      //erase map element
      int ret = this->m_data.erase(tid);
      
      //unlock the data mutex
      pthread_mutex_unlock(m_mutex);

      return ret;
    }

  int numThreads()
    {
      pthread_mutex_lock(m_mutex);
      int ret =  m_data.size(); 
      pthread_mutex_unlock(m_mutex);
      return ret;
    }

  ///map of thread IDs and object data
 public:
  std::map<pthread_t, void *> m_data;


 private:
  //mutex to protect data access
  pthread_mutex_t *m_mutex;
};


//forward declaration
struct func_params;

class ThreadMgr
{
 public:
  ///constructor
  ThreadMgr();
  
  ///destructor
  ~ThreadMgr();

 public:
  ///cancel a thread
  int cancelThread(pthread_t *tid);

  ///create a thread
  int createThread(pthread_t *tid, pthread_attr_t *attr, void *(*thread_func)(void *), void *arg);
  ///create a thread -short version
  int createThread( void *(*thread_func)(void *), void *arg);
  
  ///join a thread
  int joinThread(pthread_t tid, void **thread_return);
  ///join a thread -short version
  pthread_t joinThread(void **thread_return);

 protected:
  ///internal function to initialize a thread
  static void *func(void *arg);

  ThreadData *m_threadData;
};


/**
   \note Yes, there is a circular dependency here. That is the
   price we pay for having static functions. (no choice here)
*/
struct func_params
{
  void *(*thread_func)(void *);
  void *arguments;
  ThreadMgr *thisObj;
};

/*!\file main.cc
  Example demonstration of a class that manages threads and the
  detection of their exits through the use of condition variables.
*/

#include "C_ThreadDeath.h"
#include <iostream>

using namespace std;

void *func1(void *)
{
  /** \warning
      This function must be joined at the user level using the
      ThreadMgr joinThread function
  */
  cout << "GOT HERE: func1()" << endl;
 pthread_exit((void *)NULL);

 //we should not get here
  return NULL;
}

void *func2(void *)
{
  char *p_c = new char[256];
  memset(p_c, 0, 256);
  strcpy(p_c, "string from func2");

  cout << "func2 return string:" << p_c << endl;

  //pthread_exit((void *)p_c);
  return p_c;
}


int main(int argc, char *argv[])
{
  ThreadMgr *m = new ThreadMgr;
  void **thread_return;
  int ret=0;

  //basic thread create and join
  pthread_t tid;
  //m->createThread(&tid, NULL, func1, NULL);
  //if( (ret = m->joinThread(tid, thread_return)) != 0)
    //cout << "main:joinThread failed." << endl;
  pthread_create(&tid, NULL, func1, NULL);
  pthread_join(tid, thread_return);

  //basic thread create and join with return
  //pthread_t tid2; 
  //m->createThread(&tid2, NULL, func2, NULL);
  //cout << "main:tid=" << tid2<< endl;
  //m->joinThread(tid2, thread_return);

  //char *pc = ((char *)(char *)*thread_return);
  //cout << "main:" << pc << endl;
  //delete pc;

  //cout << ((char *)(char *)*thread_return) << endl;
  //delete ((char *)(char *)*thread_return);
  

  delete m;
  return(0);
}


//timertest.cc
#define POSIX_SOURCE

#include <Timer.h>

#include <signal.h>

#include <stdio.h>
#include <unistd.h>

#include <sys/time.h>

void myfunc(void *)
{
  printf("basic thread functionality working....\n");
  return;
}

char astbuf[]="*";
static void myhandler(int s)
{
  write (STDERR_FILENO, astbuf, sizeof(char));
  printf(": SIGNAL SIGALRM CAUGHT!\n");
}

int main()
{
  /* Demonstrate thread class calling a function
   */
  mThread t((void *)&myfunc, NULL);


  /* Demonstrate timer class, derived from thread class,
     calling int's own static functon and timing out
  */
  struct sigaction newact;
  newact.sa_handler = myhandler;
  newact.sa_flags = SA_RESTART;
  sigemptyset(&newact.sa_mask);
  sigaction(SIGALRM, &newact, NULL);

  Timer t1(5, NULL);
  t1.run();





  /*
  for(int i = 0; i < 10000000; i++);
  for(int i = 0; i < 10000000; i++);
  for(int i = 0; i < 10000000; i++);
  for(int i = 0; i < 10000000; i++);
  for(int i = 0; i < 10000000; i++);
  for(int i = 0; i < 10000000; i++);
  for(int i = 0; i < 10000000; i++);
  for(int i = 0; i < 10000000; i++);
  for(int i = 0; i < 10000000; i++);
  for(int i = 0; i < 10000000; i++);
  for(int i = 0; i < 10000000; i++);
  for(int i = 0; i < 10000000; i++);
  for(int i = 0; i < 10000000; i++);
  for(int i = 0; i < 10000000; i++);
  for(int i = 0; i < 10000000; i++);
  for(int i = 0; i < 10000000; i++);
  for(int i = 0; i < 10000000; i++);
  for(int i = 0; i < 10000000; i++);
  for(int i = 0; i < 10000000; i++);
  for(int i = 0; i < 10000000; i++);
  for(int i = 0; i < 10000000; i++);
  for(int i = 0; i < 10000000; i++);
  for(int i = 0; i < 10000000; i++);
  for(int i = 0; i < 10000000; i++);
  for(int i = 0; i < 10000000; i++);
  for(int i = 0; i < 10000000; i++);
  for(int i = 0; i < 10000000; i++);
  for(int i = 0; i < 10000000; i++);
  */

  printf("main program sleeping...\n");
  sleep(60);

  printf("main program sleeping...\n");
  sleep(60);

  //struct itimerspec value;
  //struct itimerspec ovalue;
  //long timedif;

  //if(CLOCK_REALTIME)
    //printf("has xxx\n");





  printf("main waiting at t.join()...\n");
  t.join(NULL);

  printf("main waiting at t1.join()...\n");
  t1.join(NULL);


  printf("exiting...\n");
  return 0;
}

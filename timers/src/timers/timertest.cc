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
  printf("xxxxx\n");
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


  t.join(NULL);
  t1.join(NULL);



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

  //printf("sleeping...\n");
  //sleep(10);


  //struct itimerspec value;
  //struct itimerspec ovalue;
  //long timedif;

  //if(CLOCK_REALTIME)
    //printf("has xxx\n");





  return 0;
}

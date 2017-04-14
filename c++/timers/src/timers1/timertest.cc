//timertest.cc
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

#include <Timer.h>

void function_to_time();
static void myhandler(int s);
void myfunc(void *);

char astbuf[]="*";


int main()
{
  /* Demonstrate thread class calling a function
     (does not do much, just executes the thread and stopps)
   */
  mThread t((void *)&myfunc, NULL);


  /* Demonstrate timer class, derived from thread class,
     calling int's own static functon and timing out
  */

  //install a new signal handler for the timer stuff
  struct sigaction newact;
  newact.sa_handler = myhandler;
  newact.sa_flags = SA_RESTART;
  sigemptyset(&newact.sa_mask);
  sigaction(SIGUSR1, &newact, NULL);

  //run the timer and have it execute function_to_time
  Timer t1(5, (void *)&function_to_time);

  //execute the thread
  t1.run();


  //join on the threads
  t.join(NULL);
  t1.join(NULL);

  //do nothing
  printf("sleeping...\n");
  sleep(10);

  return 0;
}


//a function that will get called when the timer fires
void function_to_time()
{
  printf("xxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
  for(int i=0; i < 1000000; i++);
  for(int i=0; i < 1000000; i++);
  for(int i=0; i < 1000000; i++);
  for(int i=0; i < 1000000; i++);
  for(int i=0; i < 1000000; i++);
  for(int i=0; i < 1000000; i++);
  for(int i=0; i < 1000000; i++);
  for(int i=0; i < 1000000; i++);
  for(int i=0; i < 1000000; i++);
  for(int i=0; i < 1000000; i++);
  for(int i=0; i < 1000000; i++);
  for(int i=0; i < 1000000; i++);
  for(int i=0; i < 1000000; i++);
  for(int i=0; i < 1000000; i++);
  for(int i=0; i < 1000000; i++);
  for(int i=0; i < 1000000; i++);
}


//a function for a thread to call
void myfunc(void *)
{
  printf("basic thread functionality working....\n");
  return;
}


/* 
    a really cheezy signal handler that would normaly not
call printf or write
*/
static void myhandler(int s)
{
  write (STDERR_FILENO, astbuf, sizeof(char));
  printf("xxxxx\n");
}

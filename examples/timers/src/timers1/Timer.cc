//Timer.cc

//class includes
#include <Timer.h>

//system includes
#include <time.h>

#ifdef __linux__
#define _POSIX_TIMERS 1
#include <posix_time.h>
#endif

#include <stdio.h>
#include <unistd.h>


//file defs
#ifndef MILLION
#define MILLION		1000000
#endif

#ifndef THOUSAND
#define THOUSAND 	1000
#endif


//code


Timer::Timer(long time, void *callback)
{
  /* allocate some memory for the Thread function argument parameter
   */ 
  int **p = NULL;
  p = new int*[2];

  /* get a copy of the thread function pointer */
  thread_func = (void *)&func;

  /* we don't do anything with the attributes in this implimentation
   */ 
  attr = NULL;
		      
  /* copy the arguments for the thread function to use */
  p[0] = (int *)&time;
  p[1] = (int *)callback;

  /* set mThread classes args variable to the argument list we want
     for the thread function */
  args = (void **)p;
}

Timer::~Timer()
{
  /* free memory allocated for args */
  if(args)
    {
      int **p=NULL;
      p = (int **)args;
      delete [] p;
    }
}

void 
Timer::func(void *args)
{
  /*
    this function tracks the time that the callback in args takes to
    execute. 
  */

  int **c = (int **)args; //convenience 

  //get the callback function from the argument list
  void (*callback)() = (void (*)())c[1];

  //setup the timer
  timer_t time_ID;
  struct itimerspec value;
  struct itimerspec ovalue;
  long timedif;

  //create a new timer
  if(timer_create(CLOCK_REALTIME, NULL, &time_ID) < 0)
    {
      perror("Could not create a timer based on Clock_REALTIME");
      exit(1);
    }

  //set timer interval (max)
  value.it_interval.tv_sec=0;
  value.it_interval.tv_nsec=0;
  value.it_value.tv_sec = MILLION;
  value.it_value.tv_nsec=0;
  
  timer_settime(time_ID, 0, &value, NULL);
  timer_gettime(time_ID, &ovalue);

  //call the callback
  callback();
  
  
  /* find out how much time it took to execute the callback function
   */
  timer_gettime(time_ID, &value);
  timedif = MILLION*(ovalue.it_value.tv_sec - value.it_value.tv_sec) +
    (ovalue.it_value.tv_nsec - value.it_value.tv_nsec)/THOUSAND;

  //report our findings
  printf("It took %ld microseconds\n", timedif);
}

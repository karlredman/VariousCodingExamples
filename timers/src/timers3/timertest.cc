//timertest.cc

/* 
   Program that demonstrates the mytimers class. various timer 
   configurations are used to show common sceneraios of timer 
   usage.
*/

//system includes
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//my includes
#include "mytimers.h"

int main(int argc, char **argv, char **env)
{
  int ret = -1;		//return values
  int i = 0;		//generic

  //5 seconds is a good time to use here
  if(argc !=2)
    {
      printf("usage: prog microseconds\n");
      printf("suggestion: 5 seconds (5000000)\n");
      exit(1);
    }

  //initialize everyting
  mytimers t;			// object
  t.init_timers();		// initilization

  printf("######################################n");
  /* TEST 1 demonstrates various timers running that have
     been started at various times. sleep() is used to provide
     latency between starting some timers. 
  */

  //start the timer with command line args
  t.start_timer(0, atoi(argv[1]));

  sleep(1);
  printf("done sleeping\n");

  t.start_timer(1, atoi(argv[1])/2);
  sleep(1);
  t.start_timer(3, atoi(argv[1])*4);
  t.start_timer(2, atoi(argv[1])/2+1000000);
  sleep(1);
  t.start_timer(4, atoi(argv[1])*2);

  printf("--------------------------------------\n");

  //detect timer expiration in a busy wait loop
  //while(t.remove_top_event() == -1);

  //or

  //use a wait_for_event, kind of thing
  while(t.get_running_timer() != -1)
    {

      /* the wait_for_event() of this mytimers implimentation
	 uses a sigwait() instead of some other mechanism (like a
	 condition variable). the repracussions of this are that
	 a timer that under some circumstances a signal might get
	 lost, or an event could take place that isn't caught until
	 a later loop of the wile statement
      */
      printf("wait_for... running %d\n", t.get_running_timer());

      t.wait_for_timer_event();
      printf("timer expired\n");

      //loop throught event list to get all of them
      for(i=0;i <= t.get_number_events();i++)
	{
	  t.stop_timer(ret = t.remove_top_event());
	  printf("main: removed timer %d\n", ret);
	}
    }


  printf("######################################\n");
  /* TEST 2 demonstrates timers that timeout durring
     the time that another timer is running
  */

  t.start_timer(0, atoi(argv[1]));
  sleep(1);
  t.start_timer(1, atoi(argv[1])+2000000);
  t.start_timer(2, atoi(argv[1])/2);
  t.start_timer(3, atoi(argv[1])*6);
  t.start_timer(4, atoi(argv[1])*4);

  printf("--------------------------------------\n");

  while(t.get_running_timer() != -1)
    {
      printf("\n");
      printf("wait_for... running %d\n", t.get_running_timer());
      t.wait_for_timer_event();

      for(i=0;i <= t.get_number_events();i++)
	{
	  t.stop_timer(ret = t.remove_top_event());
	  printf("main: removed timer %d\n", ret);
	  
	}
      
      //cause multiple timers to expire
      sleep(2);
    }



  printf("######################################\n");
  /* TEST 3 
     demonstrates a timer that expires and is restarted, then
     cancled. Also demonstrates a timer that is removed from the
     active list as a result of latency
  */
  t.start_timer(0, atoi(argv[1]));
  t.start_timer(1, atoi(argv[1])+2000000);
  t.start_timer(2, atoi(argv[1])/2);
  t.start_timer(3, atoi(argv[1])*6);
  t.start_timer(4, atoi(argv[1])*4);

  printf("--------------------------------------\n");

  int k = 0;
  while(t.get_running_timer() != -1)
    {
      printf("\n");
      printf("wait_for... running %d\n", t.get_running_timer());
      t.wait_for_timer_event();

      for(i=0;i <= t.get_number_events();i++)
	{
	  t.stop_timer(ret = t.remove_top_event());
	  printf("main: removed timer %d\n", ret);

	  //restart a timer
	  if(i == 0)
	    {
	      printf("\n");
	      printf("starting timer %d @ %d\n", i, atoi(argv[1])); 
	      
	      t.start_timer(i, atoi(argv[1]));

	      //cause latency
	      sleep(1);

	      if(i == 0)
		{
		  //cause latency
		  printf("sleeping.....\n");
		  sleep(2);
		  
		  printf("canceling timer...\n");
		  
		  //attempt to cancel timer
		  if(!t.cancel_timer(i))
		    printf("timer cancel confirmed\n");
		  else
		    printf("timer cancel failed\n");
		}
		
	      k++;
	    }
	}
    }

  //output timer expired
  printf("done\n");

  return 0;
}

////////// PUBLIC

#include "mytimers.h"
#include <unistd.h>

#include <stdio.h>

timer_data_t mytimers::timers;
long mytimers::last_timer_val;

mytimers::mytimers()
{
  last_timer_val=0;
}


mytimers::~mytimers()
{
}

int 
mytimers::init_timers(void)
{
  int i;

  //timer_data_t timers;

  //set up the timers struct
  timers.running = -1;

  //initialize array to inactive 
  for(i=0; i < MAXTIMERS; i++)
    {	
      timers.active[i]= -1;
    }
	
  //initialize events array (not really necessary)
  for(i=0; i < MAXTIMERS; i++)
    {	
      timers.events[i] = -1;
    }
	
  //no events in queue
  timers.num_events = 0;

  //set timer to 0
  stop_hardware_timer();

  //set up the signal handler
  return(catch_timer_interrupt(&myhandler));
}

int 
mytimers::get_number_events(void)
{
  //return the number of events on event list
  return(timers.num_events);
}

int 
mytimers::get_event(int event_number)
{
  //return an event (-1 if no events or value
  //is not set for this element of the event array
  if(timers.num_events)
    return(timers.events[event_number]);
  else
    return(-1);
}

long 
mytimers::get_timer_value(int n)
{
  //return the time value of an active timer
  return(timers.active[n]);
}

int 
mytimers::get_running_timer(void)
{
  //return the timer that is running
  return(timers.running);
}

void 
mytimers::start_timer(int n, long interval)
{
  //start a timer

  int set_timer = 0;

  //get the relative time for the hw timer. adjusting the interval...

  //if there is a running timer...
  if(get_running_timer() != -1)
    {
      //calc. the timer remaining on the timer before next fire
      int runtime = timers.active[timers.running]- get_hardware_timer(); 

      //if the new interval is < time remaining on the timer...
      if( interval < get_hardware_timer() )
	{
	  set_timer = 1;
	  
	  /* loop through active timers and adjust their time values
	     to accomidate for the new time that the hw timer will
	     fire off.
	  */
	  for(int i = 0; i < MAXTIMERS; i++)
	    {
	      if(timers.active[i]!= -1 )
		{
		  //active timer is decremented by the runtime
		  timers.active[i]-= runtime;
		}
	    }

	  //set a new running timer -the old one has been adjusted
	  timers.running = n;
	}
      else
	{
	  //the interval is adjusted to accomidate for lapsed time
	  //relative to the running timer
	  interval += runtime;
	}
    }
  else
    {
      //no timers running, just set running timer
      set_timer = 1;
      timers.running = n;
    }

  //set active[n]to the appropriate time value
  timers.active[n]= interval;

  if( (set_timer) )
    {
      //start the interval timer by calling the set_hardware_timer function
      //in the hardware_timer object
      set_hardware_timer(interval);
    }

  //print status of the active timers
  printf("\nstart_timer\n");
  for(int i=0; i < MAXTIMERS; i++)
    printf("timers.active[%d]=%ld, set_timer=%ld," \
	   "timers.running=%d\n", i, timers.active[i], set_timer,
	   timers.running); 
  printf("\n");

}

void 
mytimers::stop_timer(int n)
{
  //stop timer n
	
  //stops a timer if it is running and removes the timer from
  // the event list if it is there

  //if timer not valid -return
  if(n <= -1 || n >= MAXTIMERS)
    {
      return;
    }

  int set_timer=0;
  int i = 0;
  int make_running = 0;

  /* loop through active timers to find the next one and adjust their
     time to accomidate for the timer value that last fired
  */
  for(i=0;i<MAXTIMERS;i++)
    {
      if(timers.active[i]!= -1)
	{
	  timers.active[i]-= last_timer_val;

	  if(timers.active[i]<=0)
	    {
		
	      block_timer_interrupt();
	      put_on_event_list_and_deactivate(i);
	      unblock_timer_interrupt();

	      printf("stop:put_on_event_list_and_deactivate()," \
		     "timer %d\n", i);
	    }
	  
	  /* select the timer to be made active */
	  if(timers.active[i]< timers.active[make_running]
	     ||timers.active[make_running]== -1 )
	    {
	      make_running = i;
	    }
	}
    }

  //if there will be a running timer...
  if(timers.active[make_running]!= -1)
    {
      //set the running timer
      timers.running = make_running;

      //reset the hw timer
      set_hardware_timer(timers.active[make_running]);

      //value for a later printf
      set_timer = 1;
    }
  else
    {
      //no timers will be made running
      timers.running = -1;
    }

  if(timers.running == -1)
    stop_hardware_timer();


  //report status
  printf("\nstop_timer\n");
  for(int i=0; i < MAXTIMERS; i++)
    printf("timers.active[%d]=%ld, set_timer=%d,"
	   "timers.running=%d\n", i, timers.active[i],
	   set_timer, timers.running); 
}

int
mytimers::cancel_timer(int n)
{
  //cancel a timer

  //if the timer is active...
  if(timers.active[n]!= -1)
    {
      //if it is not the currently running timer
      if(n != timers.running)
	{
	  //remove from active list
	  timers.active[n]= -1;
	}
      else
	{
	  //timer is active and running

	  //get the timer value for this timer
	  long canceled_timer_val = timers.active[n];

	  int make_running = 0;
	  int set_timer = 0;

	  //get the elapsed time of the hw timer, relative to the
	  //timer value we want to cancel
	  int runtime = timers.active[timers.running]-
	    get_hardware_timer();  

	  timers.active[n]= -1;

	  /* select new timer and adjust times (pretty close to a
	     stop_timer() call
	  */
	  for(int i=0;i<MAXTIMERS;i++)
	    {
	      //if active...
	      if(timers.active[i]!= -1)
		{
		  /*decriment timer by the time elapsed in the hw
		    timer and the timer we're canceling
		  */
		  timers.active[i]-= runtime -
		    canceled_timer_val;

		  //if the timer has been made invalid
		  if(timers.active[i]<=0)
		    {
		      block_timer_interrupt();
		      put_on_event_list_and_deactivate(i);
		      unblock_timer_interrupt();

		      printf("cancel:put_on_event_list_and_deactivate()," \
			     "timer %d, runtime %d, htimer %d\n", i, runtime,
			     get_hardware_timer());
		    }
	  
		  //select the next running timer
		  if(timers.active[i]< timers.active[make_running]
		     ||timers.active[make_running]== -1 )
		    {
		      make_running = i;
		    }
		}
	    }

	  //update the hardware timer
	  if(timers.active[make_running]!= -1)
	    {
	      //new running timer
	      timers.running = make_running;

	      //set hw timer
	      set_hardware_timer(timers.active[make_running]);

	      //for later reporting
	      set_timer = 1;
	    }
	  else
	    {
	      //no timers running
	      timers.running = -1;
	    }

	  if(timers.running == -1)
	    {
	      //kill the hw timer
	      stop_hardware_timer();
	    }

	  //report
	  printf("\ncancel_timer\n");
	  for(int i=0; i < MAXTIMERS; i++)
	    printf("timers.active[%d]=%ld, set_timer=%d,"
		   "timers.running=%ld\n", i, timers.active[i],
		   set_timer, timers.running); 
	  
	  return(0);
	}
    }

    return 0;
}

int 
mytimers::remove_top_event(void)
{	
  //removes the top event from the event list and 
  //returns the timer number or -1 if the event list is empty

  int timer_number = -1;

  //if there are events...
  if(timers.num_events)
    {
      int i = 0;

      //find the first event in the list
      for(;i<MAXTIMERS && timers.events[i] == -1;i++);

      //remove the event
      timer_number = timers.events[i];
      timers.events[i]=-1;
      timers.num_events--;
    }

  //return the timer just removed
  return timer_number;
}

void 
mytimers::wait_for_timer_event(void)
{
  //waits until there is an event on the event list and 
  //then returns without changing the event list
  wait_for_interrupt();
}

	
////////// PRIVATE
void
mytimers::myhandler(int)
{
  /* handles the timer signal. This function is called by the actual
     signal handler to mainain the timers structure when the real hardware
     timer expires.
  */

  //add the running timer to the end of the event list.
  //make the running timer inactive.
  put_on_event_list_and_deactivate(timers.running);
}

void
mytimers::put_on_event_list_and_deactivate(int n)
{
  /* sets a timer to be inactive, removes it from the event list
     if it was there, and puts it at the end of the event list

     NOTE: the signal doesn't have to be blocked here unless this
     function is called outside of the signal handler. when called
     outside the handler block the signal so we don't get interrupted
     in the middle of adjusting the events list
  */

  //n is the number of the timer to be deactivated and takes no action
  // if n is -1 or out of MAXTIMERS range
  
  int i =0;

  //find the first open slot in the event list
  for(; i < MAXTIMERS && timers.events[i] != -1; i++);

  //set the event element to the timer 
  timers.events[i] = n;

  //add to the number of events waiting to be cleared/acknowledged
  timers.num_events++;

  //this timer just fired! set previous value to current
  last_timer_val = timers.active[n];

  //remove timer from active list
  timers.active[n]= -1;
}



////////// PUBLIC

#include "mytimers.h"
#include "hardware_timer.h"

timer_data_t mytimers::timers;

mytimers::mytimers()
{
  this->htimer = new hardware_timer;
}


mytimers::~mytimers()
{
  delete htimer;
}

int 
mytimers::init_timers(void)
{
  int i;

  //timer_data_t timers;

  //set up the timers struct
  timers.running = -1;

  for(i=0; i < MAXTIMERS; i++)
    {	
      timers.active[i] = -1;
    }
	
  for(i=0; i < MAXTIMERS; i++)
    {	
      timers.events[i] = -1;
    }
	
  timers.num_events = 0;

  //set up the signal handler
  return(htimer->catch_timer_interrupt(&myhandler));
}

int 
mytimers::get_number_events(void)
{
  return(timers.num_events);
}

int 
mytimers::get_event(int event_number)
{
  if(timers.num_events)
    return(timers.events[event_number]);
  else
    return(-1);
}

long 
mytimers::get_timer_value(int n)
{
  return(timers.active[n]);
}

int 
mytimers::get_running_timer(void)
{
  return timers.running;
}

void 
mytimers::start_timer(int n, long interval)
{
  //remove timer n from event list
  if(timers.num_events)
    for(int i=0; i < MAXTIMERS; i++)
      {
	if(timers.events[i] == n)
	  timers.events[i] = -1;
      }

  //set running to timer n
  timers.running = n;

  //set active[n]to the appropriate time value
  timers.active[n] = interval;

  //start the interval timer by calling the set_hardware_timer function
  //in the hardware_timer object

  htimer->set_hardware_timer(interval);
}

void 
mytimers::stop_timer(int n)
{
  //stop timer n
	
  //stops a timer if it is running and removes the timer from
  // the event list if it is there
}

//int timer_number;

int 
mytimers::remove_top_event(void)
{	
  //removes the top event from the event list and 
  //returns the timer number or -1 if the event list is empty

  int timer_number = -1;
  //timer_number = -1;

  if(timers.num_events)
    {
      timer_number = timers.events[0];
      timers.events[0]=-1;
      timers.num_events--;
    }

  return timer_number;
}

void 
mytimers::wait_for_timer_event(void)
{
  //waits until there is an event on the event list and 
  //then returns without changing the event list
  sigset_t newmask;
  sigemptyset(&newmask);
  sigsuspend(&newmask);
}

	
////////// PRIVATE
void
mytimers::myhandler(int)
  //myhandler(int)
{
  /* handles the timer signal. This function is called by the actual
     signal handler to mainain the timers structure when the real hardware
     timer expires.
  */

  //add the running timer to the end of the event list.
  timers.events[0] = timers.running;

  //make the running timer inactive.
  timers.running = -1;
	
  //update the timers data structure
  timers.num_events++;

  //reset the interval timer if there is an active timer

}

void
mytimers::put_on_event_list_and_deactivate(int n)
{
  /* sets a timer to be inactive, removes it from the event list
     if it was there, and puts it at the end of the event list
  */

  //n is the number of the timer to be deactivated and takes no action
  // if n is -1 or out of MAXTIMERS range

  timers.active[n] = -1;
  
  if(timers.num_events)
    {
      int i =0;
      for(; i < MAXTIMERS && timers.events[i] != -1; i++);

      timers.events[i-1] = n;
    }
  else
    {
      timers.events[0] = n;
    }
}



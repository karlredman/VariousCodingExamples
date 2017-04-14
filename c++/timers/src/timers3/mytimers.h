/* mytimers.h */
/* a timer manager implimentation.
   class that provides a timer API. This class is based on
   a signal implimentation and is inherrited from a hardware
   timer implimentation. The individual timers times are kept in
   an active "array" for timers that are active and timers that 
   have fired are removed from tha active array and put into the
   events array.

   Note: the array implimentations were kept simple here for 
   demonstration purposes. cirtainly more safisticated lists
   of timers may be implimented if desired.

   static member variables and functions are used here. stating things 
   have been scoped within the class to reduce name polution. The use 
   of static things here is required in order to provide a robust
   signal handler implimentation.

   AUTHOR NOTE: this is a demonstration of a technique that may be
   used as a timer implimentation. This class should be redesigned
   somewhat for production uses (ie. making easier to use, error
   handling, and signal blocking should be used more extensively).
   -Karl N. Redman
   

*/

#ifndef __MYTIMERS_H
#define __MYTIMERS_H

#include "hardware_timer.h"

#ifndef MILLION
#define MILLION 1000000
#endif

#ifndef MAXTIMERS
/* sets the size of the arrays inside
   a timers_data_t structure; which is static.
   other implimentations of this class
   may due away with this limitation.
*/
#define MAXTIMERS 5
#endif


/* tracks timers */
typedef struct _timer_data_t {
  int running;			/* which active timer is running */
  long active[MAXTIMERS];	/* list of active timers */
  int num_events;		/* number of events in event list */
  int events[MAXTIMERS];	/* timers that have fired */
} timer_data_t;

/* 
timer_data_t further explination

running: the number of the timer that is running or -1 if none are active,
	otherwise this represents the timer that will be the next to expire.
	This timer will be the one to cause the next signal to be generated.
active: has an entry for each timer giving the expiration time in usec relative
	to the starting time of the running timer. negative values indicate that 
	the timer is not active.
num_events: number of events in the event array
events: a list of timers that have expired in the order in which they expired
*/



class mytimers : public hardware_timer
{

 public:
  mytimers();
  virtual ~mytimers();

  //initialize timers
  int init_timers(void);

  //event related calls
  int get_number_events(void);
  int get_event(int event_number);
  int remove_top_event(void);	/* remove the first event on the event
				 list (NOTE: this implimentation
				 doesn't report the events in any
				 particular order. returns the timer
				 that was removed (usually then passed
				 to stop_timer()*/

  //get the time value of an active timer
  long get_timer_value(int n);

  //get the number of the timer that is running
  int get_running_timer(void);

  //start a timer
  void start_timer(int n, long interval);

  //stop a timer
  void stop_timer(int n);	/* clears the timer from the timer
				   lists and sets a new timer to
				   active if possible (does NOT cancel
				   a timer)
				*/

  //cancel a timer
  int cancel_timer(int n);

  //wait for the next timer event to happen
  void wait_for_timer_event(void);
	
 private:
  static long last_timer_val;	/* the previous timer value that fired */
  static void myhandler(int);	/* my signal handler (used by base
				   class */
  static timer_data_t timers;	/* timer data */
  
  //put a timer on the event list and remove it from the 
  //active timer list.
  static void put_on_event_list_and_deactivate(int n);
};

#endif

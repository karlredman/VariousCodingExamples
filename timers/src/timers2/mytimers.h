/* mytimers.h */

#ifndef __MYTIMERS_H
#define __MYTIMERS_H

class hardware_timer;

#define MILLION 1000000
#define MAXTIMERS 5

typedef struct _timer_data_t {
  int running;
  long active[MAXTIMERS];
  int num_events;
  int events[MAXTIMERS];
} timer_data_t;

/* 
timer_data_t Info 

running: the number of the timer that is running or -1 if none are active,
	otherwise this represents the timer that will be the next to expire.
	This timer will be the one to cause the next signal to be generated.
active: has an entry for each timer giving the expiration time in usec relative
	to the starting time of the running timer. negative values indicate that 
	the timer is not active.
num_events: number of events in the event array
events: a list of timers that have expired in the order in which they expired
*/



class mytimers
{

 public:
  mytimers();
  ~mytimers();

  int init_timers(void);
  int get_number_events(void);
  int get_event(int event_number);
  long get_timer_value(int n);
  int get_running_timer(void);
  void start_timer(int n, long interval);
  void stop_timer(int n);
  int remove_top_event(void);
  void wait_for_timer_event(void);
	
 private:

  hardware_timer *htimer;
  static void myhandler(int);
  static timer_data_t timers;
  
  static void put_on_event_list_and_deactivate(int n);
	
};

#endif

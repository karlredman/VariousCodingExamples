//hardware_timer.h
/*
  class that provides the functionality of a hardware timer.
  This class is meant to be replace depending on the desired/
  required timer.
*/
  

#ifndef __HARDWARE_TIMER_H__
#define __HARDWARE_TIMER_H__

#include <signal.h>

class hardware_timer
{
 public:
  hardware_timer();

  //interrupt handler: the original sigmask is not recorded
  virtual int catch_timer_interrupt(void(*handler)(int));

  //set the hw timer to an interval
  virtual void set_hardware_timer(long interval);

  //get the time remaining from the timer
  virtual long get_hardware_timer(void);

  //stop the timer (usually sets it to 0)
  virtual void stop_hardware_timer(void);

  //check if the interrupt is blocked for operations
  //that set/stop the timer
  virtual int is_timer_interrupt_blocked(void);

  //block and unblock the timer interrupt
  virtual void block_timer_interrupt(void);
  virtual void unblock_timer_interrupt(void);

  //mechanism to wait for the next timer to fire
  virtual void wait_for_interrupt(void);

 private:
  
  int sig_blocked;		/* timer interrupt blocked flag */
  sigset_t old_sigmask;		/* a placeholder sigmask (for signal
				 blocking */
};  

#endif

//hardware_timer.h

#ifndef __HARDWARE_TIMER_H__
#define __HARDWARE_TIMER_H__

#include <signal.h>

class hardware_timer
{
 public:
  hardware_timer();

  int catch_timer_interrupt(void(*handler)(int));
  void set_hardware_timer(long interval);
  long get_hardware_timer(void);
  void stop_hardware_timer(void);
  int is_timer_interrupt_blocked(void);
  void block_timer_interrupt(void);
  void unblock_timer_interrupt(void);
  void wait_for_interrupt(void);

 public:
  int sig_blocked;
  sigset_t old_sigmask;
};  

#endif

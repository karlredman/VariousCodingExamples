//Timer.h

/* Class derived form mThread class for use as a timer
 */

#ifndef __TIMER_H__
#define __TIMER_H__

#include <mThread.h>

class Timer : public mThread
{
 public:
  /* set the timer in miliseconds and call a callback from the static
     function below
  */
  Timer(long time, void *callback);
  ~Timer();

  /* A static function that executest after the timer fires */
  static void func(void *args);
};
  
#endif

//Timer.h

#include <mThread.h>

class Timer : public mThread
{
 public:
  Timer(long time, void *callback);

  static void func(void *args);
};
  

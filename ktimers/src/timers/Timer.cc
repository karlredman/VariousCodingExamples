//Timer.cc

#include <Timer.h>

#include <sys/time.h>

#include <stdio.h>
#include <unistd.h>

Timer::Timer(long time, void *callback)
{
  thread_func = (void *)&func;
  attr = NULL;
  args = &time;
}

void 
Timer::func(void *args)
{
  int ret;

  struct itimerval value;
  value.it_interval.tv_sec=0;
  value.it_interval.tv_usec=1;

  value.it_value = value.it_interval;
  //value.it_value.tv_sec=2;
  //value.it_value.tv_usec=0;

  ret = setitimer(ITIMER_REAL, &value, NULL);
  printf("timer set: %d\n", ret);

}

//timertest.cc

#include <stdio.h>
#include <stdlib.h>

#include "mytimers.h"

int main(int argc, char **argv, char **env)
{

  int ret = 0;

  if(argc !=2)
    {
      printf("usage: prog microseconds\n");
      exit(1);
    }

  //initialize everyting
  mytimers t;
  t.init_timers();

  //start the timer with command line args
  t.start_timer(0, atoi(argv[1]));

  //detect timer expiration in a busy wait loop
  //while(t.remove_top_event() == -1);
  t.wait_for_timer_event();

  //output timer expired
  printf("timer expired\n");

  return 0;
}

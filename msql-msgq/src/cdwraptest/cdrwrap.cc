#include <stdio.h>
#include "CDRWrapper.h"

#ifdef __linux__
	#include <time.h>
	#include <sys/time.h>
#endif

int main() {
   CDRWrapper w("Cdr");

   timeval  tv;
   gettimeofday(&tv, NULL);
   w.insert(5, CDRWrapper::INVITE, 6000, "sol-dev-06.verascape.com", "mg1", 60001, "sol-dev-07.verascape.com", "ss1", tv.tv_sec, "hohoho", "1800flowers");
   w.select(); 

  return 0;
}

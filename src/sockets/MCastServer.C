/* project-template my-project main.c file
 */


#include <time.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>

#include <iostream>

#include "class_MCastServer.h"

int main()
{
  char buff[256];
  time_t ticks;

  MCastServer s("linux", "9734");

    if( (s.init(256)) < 0)
      cout << "ERROR: init failed." << endl;

    for(;;)
      {
	//format the time for sending
	ticks = time(NULL);
	snprintf(buff, sizeof(buff), "From Server: %.24s\r\n", ctime(&ticks));

	if(s.sendTo(buff) == -1)
	  {
	    cout << "errno = " << errno << endl;
	    exit(1);
	  }
	else
	  cout << "SUCCESS: write()" << endl;

	sleep(2);
      }
    
    s.closeAll();
    cout << "done." << endl;
    return(0);
}

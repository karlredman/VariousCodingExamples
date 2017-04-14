/* project-template my-project main.c file
 */


#include <errno.h>
#include <unistd.h>

#include <iostream>

#include "class_MCastClient.h"

int main()
{
  int len;
  MCastClient c("linux", "9734");

    if( (len = c.init(256)) < 0)
      {
	cout << "ERROR: init failed." 
	     << "errno = " << errno << endl;
	exit(1);
      }

    for(;;)
      {
	if(c.recvFrom() == -1)
	  {
	    cout << "errno = " << errno << endl;
	    exit(1);
	  }
	else
	  cout << "SUCCESS: read()" << c.getBuffer() << endl;

	sleep(2);
      }
    
    c.closeAll();
    cout << "done." << endl;
    return(0);
}

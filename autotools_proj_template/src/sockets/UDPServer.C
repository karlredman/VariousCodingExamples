/* project-template my-project main.c file
 */


#include <errno.h>
#include <unistd.h>

#include <iostream>

#include "class_UDPServer.h"

int main()
{
  int len;
  UDPServer s("linux", "9734");

    if( (len = s.init(256)) < 0)
      cout << "ERROR: init failed." << endl;

    
    if(s.recvFrom() == -1)
      exit(1);
    else
      cout << "SUCCESS: read() /";
    
    cout << "Received:" << s.getBuffer() << endl;
   

    for(;;)
      {

	if(s.sendTo("From Server...") == -1)
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

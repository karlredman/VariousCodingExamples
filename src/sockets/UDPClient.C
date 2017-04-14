/* project-template my-project main.c file
 */


#include <iostream>
#include <errno.h>

#include "class_UDPClient.h"

int main()
{
  int len;
  UDPClient c("linux", "9734");

    if( (len = c.init(256)) < 0)
      cout << "ERROR: init failed." << endl;

    if(c.sendTo("From Client...") == -1)
      exit(1);
    else
      cout << "SUCCESS: write()" << endl;
    
    for(;;)
      {
	
	if(c.recvFrom() == -1)
	  exit(1);
	else
	  cout << "SUCCESS: read() /";
	  cout << "Received:" << c.getBuffer() << endl;
      }
    
    //c.closeAll();
    cout << "done." << endl;
    return(0);
}

/* project-template my-project main.c file
 */


#include <iostream>
#include <errno.h>

#include "class_TCPServer.h"

int main()
{
  TCPServer s(AF_INET, 9734, 10);

    if(s.init(256) < 0)
      cout << "ERROR: init failed." << endl;
    
    int cd = 0; 
    cd = s.accept();
    if(cd < 0)
      cout << "ERROR: accept() with " << errno << endl;
    else
      cout << "SUCCESS: accept() / cd = " << cd << endl;

    for(;;)
      {
	if(s.blockingRead(s.getClient(cd)) == -1)
	  exit(1);
	else
	  cout << "SUCCESS: read()" << endl;

	  cout << "Received:" << s.getBuffer() << endl;

	if(s.blockingWrite(s.getClient(cd), "B", 1) == -1)
	   exit(1);
	else
	  cout << "SUCCESS: write()" << endl;
      }
    
    s.closeAll();
  cout << "done." << endl;
  return(0);
}

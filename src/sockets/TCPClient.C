/* project-template my-project main.c file
 */

#include <iostream>

#include <errno.h>

#include "class_TCPClient.h"

int main()
{
  TCPClient c(AF_INET, "127.0.0.1", 9734);

    if(c.init(256) < 0)
      cout << "ERROR: init failed." << endl;
    
    if(c.connect() < 0)
      cout << "ERROR: connect failed." << endl;
    else
      cout << "SUCCESS: connect." <<endl;

    char *command = "A";

    int ret = 0; 
    while(ret != -1)
      {
	if(ret = c.blockingWrite(command, 1) < 0)
	  cout << "ERROR: write failed with:" <<errno << endl;
	else
	  cout << "SUCCESS: write." <<endl;

	ret = c.blockingRead();
	if(ret == -1)
	  {
	    cout << "ERROR: read failed with: " << errno << endl;
	    return(1);
	  }
	else
	  cout << "SUCCESS: read." <<endl;

	cout << "data:" << c.getBuffer() << endl;
      }
    
  cout << "done." << endl;
  return(0);
}

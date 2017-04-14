/*
  File Name: class_UDPServer.C
  Author: Karl N. Redman (Speed)
  Created: 2-2-03

  Description:

  Updated (list):
*/

/* System Includes */

/* C++ Includes */

/* Project Includes */
#include "class_UDPServer.h"

/* Forward Decarations */

/* Namespace */


UDPServer::
UDPServer(const char *hostname, char *service) :
  UDP(hostname, service) { }
  

int 
UDPServer::init(int arg)
{
  //set buffer
  if( UDP::init(arg) < 0 )
    return -1;

  return( initServer() );
}


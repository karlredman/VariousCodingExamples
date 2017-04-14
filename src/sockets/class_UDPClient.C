/*
  File Name: class_UDPClient.C
  Author: Karl N. Redman (Speed)
  Created: 2-2-03

  Description:

  Updated (list):
*/

/* System Includes */

/* C++ Includes */

/* Project Includes */
#include "class_UDPClient.h"

/* Forward Decarations */

/* Namespace */

UDPClient::
UDPClient(const char *hostname, char *service) :
  UDP(hostname, service) { }

int 
UDPClient::init(int arg)
{
  //set buffer
  if( UDP::init(arg) < 0 )
    return -1;

  return( initClient() );
}

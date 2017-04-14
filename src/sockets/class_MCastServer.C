/*
  File Name: class_MCastServer.C
  Author: Karl N. Redman (Speed)
  Created: 2-2-03

  Description:

  Updated (list):
*/

/* System Includes */
#include <sys/types.h>
#include <sys/socket.h>

/* C++ Includes */

/* Project Includes */
#include "class_MCastServer.h"

/* Forward Decarations */

/* Namespace */

MCastServer::
MCastServer(const char *hostname, char *service) :
  MCast(hostname, service) { };

int 
MCastServer::init(int arg)
{
  //set buffer
  if( MCast::init(arg) < 0 )
    return (-1);

  //right, multicast uses the client kind of interface
  //this is confusing -but that's the way it goes...
  if( initClient() < 0)
    return (-1);

  //turn off loopback
  return( setLoopback(0) );
}

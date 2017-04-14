/*
  File Name: classUDPServer.h
  Author: Karl N. Redman (Speed)
  Created: 2-2-03

  Description:

  Updated (list):
*/

/* System Includes */

/* C++ Includes */

/* Project Includes */
#include "class_UDP.h"

/* Forward Decarations */

/* Namespace */

#ifndef __UDPSERVER_H__
#define __UDPSERVER_H__

class UDPServer :
public UDP
{
 public:
  UDPServer(const char *hostname, char *service);
  int init(int arg);
};

#endif /* __UDPSERVER_H__ */

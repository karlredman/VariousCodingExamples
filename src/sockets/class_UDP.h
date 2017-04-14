/*
  File Name: classUDP.h
  Author: Karl N. Redman (Speed)
  Created: 2-2-03

  Description:

  Updated (list):
*/

/* System Includes */
//#include <sys/types.h>
//#include <sys/socket.h>

/* C++ Includes */

/* Project Includes */
#include "class_SocketBase.h"

/* Forward Decarations */

/* Namespace */

#ifndef __UDP_H__
#define __UDP_H__

class UDP :
public SocketBase
{
 public:
  UDP(const char *hostname, char *service);
  ~UDP();
  int init(int arg);

  ssize_t recvFrom();
  ssize_t sendTo(const char *s);

  void closeAll();

 protected:
  int initClient();
  int initServer();

 protected:
  char *hostName;
  char *servicePort;
  socklen_t addrLen;
};

#endif /* __UDP_H__ */

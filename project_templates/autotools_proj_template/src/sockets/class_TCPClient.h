/*
  File Name: class_TCPClient.h
  Author: Karl N. Redman
  Created: 2-1-03

  Description:

  Updated (list):
*/

#include "class_TCPSocket.h"

#ifndef __TCPCLIENT_H__
#define __TCPCLIENT_H__

class TCPClient 
: public TCPSocket
{
 public:
  TCPClient(sa_family_t fam, const char *addr, in_port_t port);

  int init(int bufflen);
  int connect(void);
};

#endif /* __TCPCLIENT_H__ */

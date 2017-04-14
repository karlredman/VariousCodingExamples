/*
  File Name: class_TCPSocket.h
  Author: Karl N. Redman
  Created: 2-1-03

  Description:

  Updated (list):
*/

#ifndef __TCPSOCKET_H__
#define __TCPSOCKET_H__

#include "class_SocketBase.h"

class TCPSocket :
public SocketBase
{
 public:
  //not thread safe!!!
  int blockingRead();
  int blockingRead(int sd);
  int blockingWrite(char *ch, int count);
  int blockingWrite(int sfd, char *ch, int count);
};

#endif /* __SOCKETBASE_H__ */

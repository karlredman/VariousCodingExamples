/*
  File Name: class_TCPServer.h
  Author: Karl N. Redman
  Created: 2-1-03

  Description:

  Updated (list):
*/

#include "class_TCPSocket.h"

#ifndef __TCPSERVER_H__
#define __TCPSERVER_H__

class TCPServer 
: public TCPSocket
{
 public:
  TCPServer(sa_family_t fam, in_port_t port, int numClients);
  ~TCPServer();

  int init(int bufflen);
  int accept(void);
  int accept(struct sockaddr *addr, socklen_t *addrlen);
  void close(int clientNum);
  void closeAll();

  int getClient(int c) 
    {return clientFd[c];}

 private:
  int listen(void);

  int *clientFd;
  int numClientFd;		/* # sockets descripters in array */
  int clients;
};

#endif /* __TCPSERVER_H__ */

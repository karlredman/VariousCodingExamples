/*
  File Name: class_Client.C
  Author: Karl N. Redman
  Created: 2-1-03

  Description:

  Updated (list):
*/

#include <sys/types.h>
#include <sys/socket.h>

#include "class_TCPClient.h"


TCPClient::
TCPClient(sa_family_t fam, const char *addr, in_port_t port)
{
  setSocketAddress(fam, addr, port);
}


int 
TCPClient::init(int arg)
{
  int ret = 0;


  if( (ret = setSocket(AF_INET, SOCK_STREAM, 0) < 0) )
    return -1;


  ret = setBufferLen(arg);
  return ret;

}


int
TCPClient::connect(void)
{
  return(::connect(sockfd, (struct sockaddr *) &socketAddress, sizeof(socketAddress)));
}

/*
  File Name: class_TCPSocket.C
  Author: Karl N. Redman
  Created: 2-1-03

  Description:

  Updated (list):
*/

#include "class_TCPSocket.h"

#include <assert.h>

#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <iostream>

int 
TCPSocket::blockingRead()
{
  //read from internal socket
  return read(sockfd, buffer, bufferLen);
}

int 
TCPSocket::blockingRead(int sd)
{
  //read from a specific socket
  return read(sd, buffer, bufferLen);
}

/*
int TCPSocket
::blockingRead(int sd, int count)
{
  int n = -1;

  if(count <= bufferLen)
    n = read(sd, buffer, count);
  else
    return -1;

    //null terminate buffer
    if(bufferLen < n)
    {
      buffer[n] = 0;
      return n;
    }
  //else
    return -1;
}
*/

int 
TCPSocket::blockingWrite(char *ch, int count)
{
  return write(sockfd, ch, count);
}

int TCPSocket
::blockingWrite(int sd, char *ch, int count)
{
  return write(sd, ch, count);
}

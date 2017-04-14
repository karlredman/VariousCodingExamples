/*
  File Name: classUDP.C
  Author: Karl N. Redman (Speed)
  Created: 2-2-03

  Description:

  Updated (list):
*/

/* System Includes */
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

/* C++ Includes */

/* Project Includes */
#include "class_UDP.h"

/* Forward Decarations */

/* Namespace */

UDP::
UDP(const char *hostname, char *service)
{
  hostName = new char[strlen(hostname)+1];
  strcpy(hostName, hostname);

  servicePort = new char[strlen(service)+1];
  strcpy(servicePort, service);
}

UDP::
~UDP()
{
  //close all active sockets
  closeAll();

  //delete stuff in memeory
  delete [] hostName;
  delete [] servicePort;
  delete [] cliAddr;
}

int 
UDP::init(int arg)
{
  if(setBufferLen(arg) < 0)
    return -1;

  return 0;
}

ssize_t 
UDP::sendTo(const char *s)
{
  //only works for one client right now (no register service)
  return( sendto(sockfd, s, strlen(s), 0, cliAddr, addrLen) );
}

ssize_t 
UDP::recvFrom()
{
  //only works for one client right now (no register service)
  return( recvfrom(sockfd, buffer, getBufferLen(), 0, cliAddr, &addrLen) );
}


void
UDP::closeAll()
{
  //close all sockets
  close(sockfd);
}


int 
UDP::initClient()
{
  int n;
  struct addrinfo hints, *res, *ressave;

  //bzero(&hints, sizeof(struct addrinfo));
  bzero(&hints, sizeof(hints));

  //setup hints
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_DGRAM;

  if( (n = getaddrinfo(hostName, servicePort, &hints, &res)) != 0)
    return(-1);

  //save the resource
  ressave = res;

  //try to get a socket
  do {
      
    if(setSocket(res->ai_family, res->ai_socktype, res->ai_protocol) < 0)
      continue;		//try next one 

    if(sockfd >= 0)
      break;		//success

  }while( (res = res->ai_next) != NULL);

  if(res == NULL)
    return(-1);		//all socket and bind calls failed

  //size of protocol address
  addrLen = res->ai_addrlen;

  //set client address pointer
  //(char *)cliAddr = new char[addrLen];
  cliAddr = (sockaddr *)new char[addrLen];

  //copy the found address into cliAddr
  memcpy(cliAddr, res->ai_addr, res->ai_addrlen);

  //free the addrinfo linked list
  freeaddrinfo(ressave);

  return sockfd;
}

int 
UDP::initServer()
{
  int n;
  struct addrinfo hints, *res, *ressave;

  //bzero(&hints, sizeof(struct addrinfo));
  bzero(&hints, sizeof(hints));

  //setup hints
  hints.ai_flags = AI_PASSIVE;
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_DGRAM;

  if( (n = getaddrinfo(hostName, servicePort, &hints, &res)) != 0)
    return(-1);

  //save the resource
  ressave = res;

  //try to get a socket
  do {
      
    if(setSocket(res->ai_family, res->ai_socktype, res->ai_protocol) < 0)
      continue;		//try next one 

    if(bind(sockfd, res->ai_addr, res->ai_addrlen) == 0)
      break;		//success

    close(sockfd);	//bind failed, try again

  }while( (res = res->ai_next) != NULL);


  //size of protocol address
  addrLen = res->ai_addrlen;

  //set client address pointer
  //(char *)cliAddr = new char[addrLen];
  cliAddr = (sockaddr *)new char[addrLen];

  //free the addrinfo linked list
  freeaddrinfo(ressave);

  return sockfd;
}

/*
  File Name: class_TCPServer.C
  Author: Karl N. Redman
  Created: 2-1-03

  Description:

  Updated (list):
*/

#include "class_TCPServer.h"

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>


TCPServer::
TCPServer(sa_family_t fam, in_port_t port, int numClients) :
  clients(0)
{
  setSocketAddress(fam, port);
  clientFd = new int[numClients];
  numClientFd = numClients;
}

TCPServer::
~TCPServer()
{ 
  //close all sockets
  closeAll();
}

void
TCPServer::closeAll()
{
  //close all sockets and delete the array
  for(int i = 0; i < numClientFd; i++)
    { close(clientFd[i]); }

  //delete the array
  delete [] clientFd;
}

int 
TCPServer::init(int arg)
{
  if( setSocket(AF_INET, SOCK_STREAM, 0) < 0 )
    return -1;

  if( bind(sockfd, (struct sockaddr *) &socketAddress, sizeof(socketAddress)) < 0)
      return -1;

  if(setBufferLen(arg) < 0)
    return -1;

  return(listen());
}


int
TCPServer::listen(void)
{
  //listen for a maximum of the number of clients specified
  return ::listen(sockfd, numClientFd);
}

int 
TCPServer::accept(void)
{
  //accept a connection
  return accept(NULL, NULL);
}

int 
TCPServer::accept(struct sockaddr *addr, socklen_t *addrlen)
{
  //returns the id of the client (in array terms)
  int c = 0;
  if( (c = ::accept(sockfd, addr, addrlen)) != -1)
    {
      //this is already emplied!!!
      if( (clients+1) <= numClientFd)
	{
	  //save the client socked desc. in the array
	  clientFd[clients] = c;
	  return clients;
	}
    }
  
  //fail from too many clients or accept() system call failure
  return -1;
}

void 
TCPServer::close(int clientNum)
{
  //close a sd on a client in our list
  close(clientFd[clientNum]);
}

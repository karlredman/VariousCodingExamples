/*
  File Name: class_MCastClient.C
  Author: Karl N. Redman (Speed)
  Created: 2-2-03

  Description:

  Updated (list):
*/

/* System Includes */
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>

/* C++ Includes */

/* Project Includes */
#include "class_MCastClient.h"

/* Forward Decarations */

/* Namespace */

MCastClient::
MCastClient(const char *hostname, char *service) :
  MCast(hostname, service) { };

int 
MCastClient::init(int arg)
{
  const int on = 1;

  //set buffer
  if( MCast::init(arg) < 0 )
    return (-1);

  //if( setSocket(AF_UNSPEC, SOCK_DGRAM, 0) < 0 )
  if( setSocket(AF_INET, SOCK_DGRAM, 0) < 0 )
    return (-1);

  if( setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
    return (-1);

  if( initClient() < 0)
    return (-1);
  
  if( bind(sockfd, cliAddr, addrLen) < 0)
    return (-1);

  if( mcastJoin(sockfd, cliAddr, addrLen, NULL, 0) < 0)
    { 
      //ignore an EINVAL for portability reasons
      if(errno == EINVAL)
	return 0;
      else
	return (-1);
    }

  return 0;
}

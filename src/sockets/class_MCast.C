/*
  File Name: classMCast.C
  Author: Karl N. Redman (Speed)
  Created: 2-2-03

  Description: !!!Not thread safe if errno isn't.

  Updated (list):
*/

/* System Includes */
#include <sys/types.h>
#include <sys/socket.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <string.h>

/* C++ Includes */

/* Project Includes */
#include "class_MCast.h"

/* Forward Decarations */

/* Namespace */

MCast::
MCast(const char *hostname, char *service) :
  UDP(hostname, service) {}

int 
MCast::init(int arg)
{
  if(UDP::init(arg) == -1)
    return(-1);

  return 0;
}

int
MCast::setLoopback(int onOff)
{
  switch(sockfd_to_family(sockfd))
    {
    case AF_INET: {
      u_char flag;
      flag = onOff;
      return(setsockopt(sockfd, IPPROTO_IP, IP_MULTICAST_LOOP,
			&flag, sizeof(flag)));
    }
    default:
      errno = EPROTONOSUPPORT;
      return (-1);
    }//end switch
}

int
MCast::mcastJoin(int sd, sockaddr *sa, socklen_t salen,
		 const char *ifname, u_int ifindex)
{
  //from stevens book -NOTE: providing ifname and ifindex is not
  //portable any longer (a new solution besides the stevens method
  //must be found). For now the last to parameters must always be NULL 
  // and 0, respectively. -ksr.

  switch(sa->sa_family) {
  case AF_INET: {
    //structures are defined in class_SocketBase.h for 
    // convenience. -ksr.
    struct ip_mreq mreq;
    struct ifreq ifreq;

    memcpy(&mreq.imr_multiaddr, &((struct sockaddr_in *)sa)->sin_addr,
	   sizeof(struct in_addr));

    if(ifindex > 0) {

      //no implimentation for if_indextoname()
      //if(if_indextoname(ifindex, ifreq.ifr_name) == NULL) {
	      //errno = ENXIO // i/f index not found
 	      //  return(-1);
            //}

      //this will always fail if you try to use it. -ksr
      goto doioctl;

    } else if(ifname != NULL) {
      strncpy(ifreq.ifr_name, ifname, IFNAMSIZ);
    
  doioctl:
    
    if(ioctl(sd, SIOCGIFADDR, &ifreq) < 0)
      return(-1);
    
    memcpy(&mreq.imr_interface, &((struct sockaddr_in *) &ifreq.ifr_addr)->sin_addr, 
	   sizeof(struct in_addr));

  } else
    //mreq.imr_multiaddr.s_addr = inet_netof( ((sockaddr_in *)cliAddr)->sin_addr );
    //mreq.imr_multiaddr.s_addr = inet_addr("127.0.0.1");
    mreq.imr_interface.s_addr = htonl(INADDR_ANY);

    return(setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(struct ip_mreq)));

  }//end AF_INET

  default:
    errno = EPROTONOSUPPORT;
    return (-1);
  }//end switch
}

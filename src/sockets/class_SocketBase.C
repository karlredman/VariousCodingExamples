/*
  File Name: class_SocketBase.C
  Author: Karl N. Redman
  Created: 2-1-03

  Description:

  Updated (list):
*/

#include "class_SocketBase.h"

#include <assert.h>

#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <iostream>

SocketBase::
SocketBase() :
  buffer(NULL), bufferLen(0), cliAddr(NULL)
{ 
  bzero(&socketAddress, sizeof(socketAddress));
}

SocketBase::
~SocketBase()
{ 
  delete [] buffer;
  close(sockfd);
}

int SocketBase
::setSocket(int domain, int type, int protocol)
{ 
  sockfd = socket(domain, type, protocol);
  return sockfd;
}

void SocketBase
::setSocketAddress(sa_family_t fam, const char *addr, in_port_t port)
{
  socketAddress.sin_family = fam;
  socketAddress.sin_addr.s_addr = inet_addr(addr); // ipv4
  socketAddress.sin_port = htons(port);
  return;
}

void SocketBase
::setSocketAddress(sa_family_t fam, in_port_t port)
{
  socketAddress.sin_family = fam;
  socketAddress.sin_addr.s_addr = htonl(INADDR_ANY); // ipv4
  socketAddress.sin_port = htons(port);
  return;
}

int SocketBase
::setBufferLen(int len)
{
  int ret=0;

  //null terminate

  len += 1;

  if(bufferLen)
    {
      //copy what what we can
      char *x;
      char *tmp = new char[len];

      assert(tmp != NULL);

      if(len <= bufferLen)
	memcpy(tmp, buffer, len);
      else
	{
	  memset(tmp, 0, sizeof(tmp));
	  memcpy(tmp,buffer, bufferLen);
	}

      //replace the pointer
      x = buffer;
      buffer = tmp;

      //free the old buffer
      delete [] x;
    }
  else
    {
      bufferLen = len;
      buffer = new char[bufferLen];
      memset(buffer, 0, sizeof(buffer));
    }

  return ret;
}

int
SocketBase::sockfd_to_family(int sd)
{
  //from Stevens book

  int MAXSOCKADDR = 128;	// should be a constan!!!

  union {
    struct sockaddr sa;

    char data[MAXSOCKADDR];
  } un;

  socklen_t len;
  
  len = MAXSOCKADDR;

  if(getsockname(sd, (struct sockaddr *)un.data, &len) < 0)
    return (-1);

  return(un.sa.sa_family);
}

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  It is not possible to use the stevens method for getting
  the interface any longer (it's not portable at all for 
  linux and the like) -ksr.
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
/*
if_indextoname(unsigned int index, char * name)
{
  //from stevens book
  char *buf, *next, *lim;
  size_t len;
  struct if_msghdr *ifm;
  struct sockaddr *sa, *rti_info[RTAX_MAX];
  struct sockaddr_dl *sdl;

  if( (buf = net_rt_iflist(0, index, &len)) == NULL)
    retur(NULL);

  lim = buf +len;
  for( next = buf; next < lim; next += ifm->ifm_msglen)
    {
      ifm = (struct if_msghdr *) next;
      if(ifm->ifm_type == RTM_IFINFO)
        {
          sa = (struct sockaddr *)(ifm+1);
          get_rtaddrs(ifm->ifm_addrs, sa, rti_info);
          
          if( (sa = rti_info[RTAX_IFP]) != NULL)
            {              
              if(sa->sa_family = AF_LINK)
                {
                  sdl = (struct sockaddr_dl *) sa;
                  if(sdl->sdl_index == index)
                    {
                      strcpy(name, sdl->sdl_data);
                      name[sdl->sdl_nlen);
                      free(buf);
                      return(name);
                    }
                }
            }
        }
    }
      free(buf);
      return(NULL);
}
*/


/*
 * Round up 'a' to next multiple of 'size'
 */
//#define ROUNDUP(a, size) (((a) & ((size)-1)) ? (1+((a) | ((size)-1))) : (a))

/*
 * Step to next socket address structure;
 * if sa_len is 0, assume it is of sizeof(u_long).
 */
//#define NEXT_SA(ap) ap=(struct sockaddr *) ((caddr_t) ap + (ap->sa_len ? ROUNDUP(ap->sa_len, sizeof(u_long)) : sizeof(u_long)))

/*
void
SocketBase::get_rtaddrs(int addrs, struct sockaddr *sa, struct sockaddr **rti_info)
{
  int i;
  
  for (i = 0; i < RTAX_MAX; i++)
    {
      if(addrs & (1<< i))
	{
	  rti_info[i];
	  NEXT_SA(sa);
	} else
	  rti_info[i] = NULL;
    }
}
*/

/*
char *
SocketBase::net_rt_iflist(int family, int flags, size_t *lenp)
{
  int mib[6];
  char *buf;

  mib[0] = CTL_NET;
  mib[1] = AF_ROUTE;
  mib[2] = 0;
  mib[3] = family;
  mib[4] = NET_RT_IFLIST;
  mib[5] = flags;

  if(sysctl(mib, 6, NULL, lenp, NULL, 0 ) < 0 )
    return(NULL);

  if( (buf = malloc(*lenp)) == NULL)
    return(NULL);

  if(sysctl(mib, 6, buf, lenp, NULL, 0) < 0)
    return(NULL);

  reutrn(buf);
}
*/

/*
  File Name: class_SocketBase.h
  Author: Karl N. Redman
  Created: 2-1-03

  Description:

  Updated (list):
*/

#ifndef __SOCKETBASE_H__
#define __SOCKETBASE_H__

#include <netinet/in.h>

/* stuff that doesn't exist in my /usr/include/net/if.h file 
   but is used by stevens
*/

struct if_msghdr {
  u_short ifm_mshlen;
  u_char ifm_version;
  u_char ifm_type;

  int ifm_addrs;
  int ifm_flags;
  u_short ifm_index;
  //struct if_data ifm_data; ...who knows... -ksr
};

struct ifa_msghdr {
  u_short ifam_msglen;
  u_char ifam_version;
  u_char ifam_type;

  int ifam_addrs;
  int ifam_flags;
  u_short ifam_index;
  int ifam_metric;
};

class SocketBase
{
 public:
  SocketBase();
  virtual ~SocketBase();
  virtual int init(int arg) = 0;

  virtual int setBufferLen(int len);
  inline int getBufferLen() {return bufferLen-1;}
  inline const char *getBuffer() {return buffer;}

 protected:
  int setSocket(int domain, int type, int protocol);
  int getSocket() {return sockfd;}

  void setSocketAddress(sa_family_t fam, const char * addr, in_port_t port);
  void setSocketAddress(sa_family_t fam, in_port_t port);
  sockaddr_in getSocketAddress()
    {return socketAddress;}

  /* support functions */
  int sockfd_to_family(int sd);

 protected:
  int sockfd;
  char *buffer;
  int bufferLen;

  struct sockaddr *cliAddr;

  //should be an array of addresses for 1...* addresses 
  //and changed to a sockaddr (to be cast as needed)
  struct sockaddr_in socketAddress;
};

#endif /* __SOCKETBASE_H__ */

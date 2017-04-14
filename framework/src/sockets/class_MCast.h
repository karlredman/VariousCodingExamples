/*
  File Name: classMCast.h
  Author: Karl N. Redman (Speed)
  Created: 2-2-03

  Description:

  Updated (list):
*/

/* System Includes */

/* C++ Includes */

/* Project Includes */
#include "class_UDP.h"

/* Forward Decarations */

/* Namespace */

#ifndef __MCAST_H__
#define __MCAST_H__

class MCast :
public UDP
{
 public:
  MCast(const char *hostname, char *service);
  int init(int arg);

  /* SUPPORT FUNCTIONS */
  int setLoopback(int onOff);
  int mcastJoin(int sd, sockaddr *sa, socklen_t salen,
		const char *ifname, u_int ifindex);
};

#endif /* __MCAST_H__ */

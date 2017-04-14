/*
  File Name: class_UDPClient.h
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

#ifndef __UDPCLIENT_H__
#define __UDPCLIENT_H__

class UDPClient :
public UDP
{
 public:
  UDPClient(const char *hostname, char *service);
  int init(int arg);
    
};

#endif /* __UDPCLIENT_H__ */

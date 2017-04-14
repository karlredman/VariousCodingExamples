/*
  File Name: class_MCastClient.h
  Author: Karl N. Redman (Speed)
  Created: 2-3-03

  Description:

  Updated (list):
*/

/* System Includes */

/* C++ Includes */

/* Project Includes */
#include "class_MCast.h"

/* Forward Decarations */

/* Namespace */

#ifndef __MCASTCLIENT_H__
#define __MCASTCLIENT_H__

class MCastClient :
public MCast
{
 public:
  MCastClient(const char *hostname, char *service);
  int init(int arg);
};

#endif /* __MCASTCLIENT_H__ */

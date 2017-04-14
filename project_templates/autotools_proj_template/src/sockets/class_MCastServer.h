/*
  File Name: class_MCastServer.h
  Author: Karl N. Redman (Speed)
  Created: 2-2-03

  Description:

  Updated (list):
*/

/* System Includes */

/* C++ Includes */

/* Project Includes */
#include "class_MCast.h"

/* Forward Decarations */

/* Namespace */

#ifndef __MCASTSERVER_H__
#define __MCASTSERVER_H__

class MCastServer :
public MCast
{
 public:
  MCastServer(const char *hostname, char *service);
  int init(int arg);
};

#endif /* __MCASTSERVER_H__ */

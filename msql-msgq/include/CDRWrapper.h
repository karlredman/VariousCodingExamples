#ifndef __CDRWrapper_h__
#define __CDRWrapper_h__

#include "MySQLWrapper.h"


class CDRWrapper : public MySQLWrapper {

   public:

      enum CDREventType {
         INVITE = 0,
         INVITEOK = 1,
         ACK = 2,
         BYE = 3,
         BYEOK = 4,
         REFER = 5,
         REFEROK = 6
      };

      CDRWrapper(char *db);
      ~CDRWrapper();

      bool insert(unsigned long cseq, CDREventType event, 
         unsigned short fromPort, char *fromHost, char *fromUser, 
         unsigned short toPort, char *toHost, char *toUser,
         unsigned long timestamp, char *callId, 
         char *appName, unsigned short status = 0);
      bool select();
};

#endif // __CDRWrapper_h__

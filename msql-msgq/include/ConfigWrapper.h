#ifndef __ConfigWrapper_h__
#define __ConfigWrapper_h__

#include "MySQLWrapper.h"
#include "CallDirectorCache.h"

class ConfigWrapper : public MySQLWrapper {

   private:

      MYSQL_RES *res_set;

   public:

      ConfigWrapper(char *db);
      ~ConfigWrapper();

      bool select(Rack &rack);
      bool query(char *stmt);
      void processCallDirector(MYSQL *conn, MYSQL_RES *res_set, Rack &rack);
      void processSpeechServer(MYSQL *conn, MYSQL_RES *res_set, Rack &rack);
      void processMediaGateway(MYSQL *conn, MYSQL_RES *res_set, Rack &rack);
      void processLineCard(MYSQL *conn, MYSQL_RES *res_set, Rack &rack);
      void processSpan(MYSQL *conn, MYSQL_RES *res_set, Rack &rack);
      void processCarrier(MYSQL *conn, MYSQL_RES *res_set, Rack &rack);
      void processTrunkGroup(MYSQL *conn, MYSQL_RES *res_set, Rack &rack);
      void processTrunkGroupSpanAssignment(MYSQL *conn, MYSQL_RES *res_set, Rack &rack);
      void processTrunkGroupLineCardAssignment(MYSQL *conn, MYSQL_RES *res_set, Rack &rack);
      void processApplication(MYSQL *conn, MYSQL_RES *res_set, Rack &rack);
      void processDNIS(MYSQL *conn, MYSQL_RES *res_set, Rack &rack);
      void processAppTrunkAssignment(MYSQL *conn, MYSQL_RES *res_set, Rack &rack);
};

#endif // __ConfigWrapper_h__

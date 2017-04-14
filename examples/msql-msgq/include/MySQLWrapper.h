#ifndef __MySQLWrapper_h__
#define __MySQLWrapper_h__

#include <mysql.h>

#define DEF_HOST_NAME   "localhost"
#define DEF_PORT_NUM    3306
#define DEF_SOCKET_NAME NULL
#define DEF_FLAGS 0

class MySQLWrapper {

   private:

      void print_dashes (MYSQL_RES *res_set);

   protected:

      char *host;
      char *user;
      char *password;
      unsigned short port;
      char *db;
      MYSQL *conn;
      int errno;

      void connect();
      void disconnect();

      virtual void processResultSet(MYSQL *conn, MYSQL_RES *res_set);

      inline virtual void setError(int err);

   public:

      enum MySQLWrapperError {
         E_NONE,
         E_INIT,
         E_RESULT,
         E_QUERY,
         E_CONN
      };

      MySQLWrapper(char *user, char *password, char *db,
                   char *host = DEF_HOST_NAME,
                   unsigned short port = DEF_PORT_NUM);
      virtual ~MySQLWrapper();

      virtual bool query(char *);
      
      inline virtual int getError() const;
};

#endif // __MySQLWrapper_h__

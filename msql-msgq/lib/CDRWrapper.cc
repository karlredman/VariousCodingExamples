#include "CDRWrapper.h"
#include <stdio.h>

#ifdef __linux__
	#include <time.h>
#endif

#define DEF_USER_NAME "dba"
#define DEF_PASSWORD "sql"

CDRWrapper::CDRWrapper(char *db) : MySQLWrapper(DEF_USER_NAME, DEF_PASSWORD, db) {};
CDRWrapper::~CDRWrapper() {};

bool CDRWrapper::select() {
   return query("SELECT * FROM CallDetailRecord");
}

bool CDRWrapper::insert(unsigned long cseq, CDREventType event, unsigned short fromPort, char *fromHost, char *fromUser, unsigned short toPort, char *toHost, char *toUser, unsigned long timestamp, char *callId, char *appName, unsigned short status) {
   tm * ptm;
   ptm = gmtime ((long *)&timestamp);

   char stmt[512];
   sprintf(stmt, "INSERT INTO CallDetailRecord VALUES(%u, %u, %u, \'%s\', \'%s\', %u, \'%s\', \'%s\', %04u%02u%02u%02u%02u%02u, \'%s\', \'%s\', %u)", cseq, event, fromPort, fromHost, fromUser, toPort, toHost, toUser, ptm->tm_year + 1900, ptm->tm_mon, ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec, callId,  appName,  status);
   printf("%s\n", stmt);
   return query(stmt);
}

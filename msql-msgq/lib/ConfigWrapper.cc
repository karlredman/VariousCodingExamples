#include "ConfigWrapper.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEF_USER_NAME "dba"
#define DEF_PASSWORD "sql"

ConfigWrapper::ConfigWrapper(char *db) : MySQLWrapper(DEF_USER_NAME, DEF_PASSWORD, db) {
   res_set = NULL;
}

ConfigWrapper::~ConfigWrapper() {
   if (res_set) {
      delete res_set;
   }
}

bool ConfigWrapper::select(Rack &rack) {
   bool rv;

   memset(&rack, 0, sizeof(rack));
   rv = query("SELECT SubRackNumber, CallDirectorNumber, CallDirectorName, IPAddress FROM CallDirector, SubRack, Rack WHERE (CallDirector.SubRackID = SubRack.SubRackID AND SubRack.RackID = Rack.RackID)");   
   if (!rv) {
      return rv;
   }

   processCallDirector(conn, res_set, rack);

   rv = query("SELECT SubRackNumber, SpeechServerNumber, SpeechServerName, IPAddress, MaxRtpPorts, MaxASRs FROM SpeechServer, SubRack, Rack WHERE (SpeechServer.SubRackID = SubRack.SubRackID AND SubRack.RackID = Rack.RackID)");
   if (!rv) {
      return rv;
   }

   processSpeechServer(conn, res_set, rack);

   rv = query("SELECT SubRackNumber, MediaGatewayNumber, MediaGatewayName, IPAddress FROM MediaGateway, SubRack, Rack WHERE (MediaGateway.SubRackID = SubRack.SubRackID AND SubRack.RackID = Rack.RackID)");
   if (!rv) {
      return rv;
   }

   processMediaGateway(conn, res_set, rack);

   rv = query("SELECT SubRackNumber, MediaGatewayNumber, LineCardNumber, LineCardName, LineCard.IPAddress FROM LineCard, MediaGateway, SubRack, Rack WHERE (LineCard.MediaGatewayID = MediaGateway.MediaGatewayID AND MediaGateway.SubRackID = SubRack.SubRackID AND SubRack.RackID = Rack.RackID)");
   if (!rv) {
      return rv;
   }

   processLineCard(conn, res_set, rack);

   rv = query("SELECT SubRackNumber, MediaGatewayNumber, LineCardNumber, SpanNumber, DChannelConfig, SpanName FROM Span, LineCard, MediaGateway, SubRack, Rack WHERE (Span.LineCardID = LineCard.LineCardID AND LineCard.MediaGatewayID = MediaGateway.MediaGatewayID AND MediaGateway.SubRackID = SubRack.SubRackID AND SubRack.RackID = Rack.RackID)");
   if (!rv) {
      return rv;
   }

   processSpan(conn, res_set, rack);

   rv = query("SELECT CarrierID, CarrierName FROM Carrier");
   if (!rv) {
      return rv;
   }

   processCarrier(conn, res_set, rack);

   rv = query("SELECT TrunkGroupID, TrunkGroupName, TrunkGroupType, TrunkGroup.CarrierID FROM TrunkGroup, Carrier WHERE (TrunkGroup.CarrierID = Carrier.CarrierID)");
   if (!rv) {
      return rv;
   }

   processTrunkGroup(conn, res_set, rack);

   rv = query("SELECT TrunkGroup.TrunkGroupID, SpanNumber, LineCardNumber, MediaGatewayNumber, SubRackNumber FROM  TrunkGroupSpanAssignment, TrunkGroup, Span, LineCard, MediaGateway, SubRack, Rack WHERE (TrunkGroup.TrunkGroupID = TrunkGroupSpanAssignment.TrunkGroupID AND TrunkGroupSpanAssignment.SpanID = Span.SpanID AND Span.LineCardID = LineCard.LineCardID AND LineCard.MediaGatewayID = MediaGateway.MediaGatewayID AND MediaGateway.SubRackID = SubRack.SubRackID AND SubRack.RackID = Rack.RackID)");
   if (!rv) {
      return rv;
   }

   processTrunkGroupSpanAssignment(conn, res_set, rack);

   rv = query("SELECT DISTINCT TrunkGroup.TrunkGroupID, LineCardNumber, MediaGatewayNumber, SubRackNumber FROM  TrunkGroupSpanAssignment, TrunkGroup, Span, LineCard, MediaGateway, SubRack, Rack WHERE (TrunkGroup.TrunkGroupID = TrunkGroupSpanAssignment.TrunkGroupID AND TrunkGroupSpanAssignment.SpanID = Span.SpanID AND Span.LineCardID = LineCard.LineCardID AND LineCard.MediaGatewayID = MediaGateway.MediaGatewayID AND MediaGateway.SubRackID = SubRack.SubRackID AND SubRack.RackID = Rack.RackID)");
   if (!rv) {
      return rv;
   }

   processTrunkGroupLineCardAssignment(conn, res_set, rack);

   rv = query("SELECT VSSApplicationID, VSSApplicationName, VoiceXMLURL FROM VSSApplication");
   if (!rv) {
      return rv;
   }

   processApplication(conn, res_set, rack);

   rv = query("SELECT DNISID, VSSApplicationID, StartPhoneNumber, EndPhoneNumber FROM DNIS");
   if (!rv) {
      return rv;
   }

   processDNIS(conn, res_set, rack);

   rv = query("SELECT VSSApplicationID, TrunkGroupID FROM AppTrunkAssignment");
   if (!rv) {
      return rv;
   }

   processAppTrunkAssignment(conn, res_set, rack);

   return true;
}

bool ConfigWrapper::query(char *stmt) {
   unsigned int field_count;

   if (mysql_query(conn, stmt) != 0) {
      setError(E_QUERY);
      return false;
   }

   res_set = mysql_store_result(conn);

   return true;
}

void ConfigWrapper::processCallDirector(MYSQL *conn, MYSQL_RES *res_set, Rack &rack) {
   MYSQL_ROW               row;
   int srNumber, cdNumber;
   char *cdName;
   char *cdAddr;
   int idx;

   if (!res_set) {
      return;
   }

   while ((row = mysql_fetch_row(res_set)) != NULL) {
      srNumber = atoi(row[0]) - 1;
      cdNumber = atoi(row[1]) - 1;
      cdName = row[2];
      cdAddr = row[3];
      idx = srNumber * MAX_CALL_DIRECTORS_SUBRACK + cdNumber;
      strcpy(rack.callDirectors[idx].name, cdName);
      strcpy(rack.callDirectors[idx].ip, cdAddr);
      rack.callDirectors[idx].used = true;
   }
}

void ConfigWrapper::processSpeechServer(MYSQL *conn, MYSQL_RES *res_set, Rack &rack) {
   MYSQL_ROW               row;
   int srNumber, ssNumber, availablePorts, availableASRs;
   char *ssName;
   char *ssAddr;
   int idx;

   if (!res_set) {
      return;
   }

   while ((row = mysql_fetch_row(res_set)) != NULL) {
      srNumber = atoi(row[0]) - 1;
      ssNumber = atoi(row[1]) - 1;
      ssName = row[2];
      ssAddr = row[3];
      availablePorts = atoi(row[4]);
      availableASRs = atoi(row[5]);
      idx = srNumber * MAX_SPEECH_SERVERS_SUBRACK + ssNumber;
      strcpy(rack.speechServers[idx].name, ssName);
      strcpy(rack.speechServers[idx].ip, ssAddr);
      rack.speechServers[idx].availableRtpPorts = availablePorts;
      rack.speechServers[idx].availableAsrs = availableASRs;
      rack.speechServers[idx].used = true;
      rack.availableAsrs[idx] = availableASRs;
   }
}

void ConfigWrapper::processMediaGateway(MYSQL *conn, MYSQL_RES *res_set, Rack &rack) {
   MYSQL_ROW               row;
   int srNumber, mgNumber;
   char *mgName;
   char *mgAddr;
   int idx;

   if (!res_set) {
      return;
   }

   while ((row = mysql_fetch_row(res_set)) != NULL) {
      srNumber = atoi(row[0]) - 1;
      mgNumber = atoi(row[1]) - 1;
      mgName = row[2];
      mgAddr = row[3];
      idx = srNumber * MAX_MEDIA_GATEWAYS_SUBRACK + mgNumber;
      strcpy(rack.mediaGateways[idx].name, mgName);
      strcpy(rack.mediaGateways[idx].ip, mgAddr);
      rack.mediaGateways[idx].firstLineCard = srNumber * MAX_LINE_CARDS_SUBRACK + mgNumber * MAX_LINE_CARDS_MEDIA_GATEWAY;
      rack.mediaGateways[idx].used = true;
   }
}

void ConfigWrapper::processLineCard(MYSQL *conn, MYSQL_RES *res_set, Rack &rack) {
   MYSQL_ROW               row;
   int srNumber, mgNumber, lcNumber;
   char *lcName;
   char *lcAddr;
   int idx;

   if (!res_set) {
      return;
   }

   while ((row = mysql_fetch_row(res_set)) != NULL) {
      srNumber = atoi(row[0]) - 1;
      mgNumber = atoi(row[1]) - 1;
      lcNumber = atoi(row[2]) - 1;
      lcName = row[3];
      lcAddr = row[4];
      idx = srNumber * MAX_LINE_CARDS_SUBRACK + mgNumber * MAX_LINE_CARDS_MEDIA_GATEWAY + lcNumber;
      strcpy(rack.lineCards[idx].name, lcName);
      strcpy(rack.lineCards[idx].ip, lcAddr);
      rack.lineCards[idx].used = true;
   }
}

void ConfigWrapper::processSpan(MYSQL *conn, MYSQL_RES *res_set, Rack &rack) {
   MYSQL_ROW               row;
   int srNumber, mgNumber, lcNumber, spanNumber, dch;
   char *spanName;
   int idx;

   if (!res_set) {
      return;
   }

   while ((row = mysql_fetch_row(res_set)) != NULL) {
      srNumber = atoi(row[0]) - 1;
      mgNumber = atoi(row[1]) - 1;
      lcNumber = atoi(row[2]) - 1;
      spanNumber = atoi(row[3]) - 1;
      dch = atoi(row[4]) - 1;
      spanName = row[5];
      idx = srNumber * MAX_SPAN_SUBRACK + mgNumber * MAX_SPAN_MEDIA_GATEWAY + lcNumber * MAX_SPAN_LINE_CARD + spanNumber;
      rack.spans[idx].availableChannels = (dch == DCH_NFAS) ? MAX_CHANNELS_SPAN : MAX_CHANNELS_SPAN - 1;
      strcpy(rack.spans[idx].name, spanName);
      rack.spans[idx].used = true;
   }
}

void ConfigWrapper::processCarrier(MYSQL *conn, MYSQL_RES *res_set, Rack &rack) {
   MYSQL_ROW row;
   char *carrierName;
   int carrierId = 0;

   if (!res_set) {
      return;
   }

   while ((carrierId < MAX_CARRIERS) && ((row = mysql_fetch_row(res_set)) != NULL)) {
      carrierId = atoi(row[0]) - 1;
      carrierName = row[1];
      strcpy(rack.carriers[carrierId].name, carrierName);
      rack.carriers[carrierId].id = carrierId;
      rack.carriers[carrierId].used = true;
   }
}

void ConfigWrapper::processTrunkGroup(MYSQL *conn, MYSQL_RES *res_set, Rack &rack) {
   MYSQL_ROW row;
   char *tgName;
   int tgType, tgId, carrierNumber;

   if (!res_set) {
      return;
   }

   while ((row = mysql_fetch_row(res_set)) != NULL) {
      tgId = atoi(row[0]) - 1;
      tgName = row[1];
      tgType = atoi(row[2]);
      carrierNumber = atoi(row[3]);
      strcpy(rack.trunkGroups[tgId].name, tgName);
      rack.trunkGroups[tgId].flags = tgType;
      rack.trunkGroups[tgId].carrier = carrierNumber;
      rack.trunkGroups[tgId].used = true;
   }
}

void ConfigWrapper::processTrunkGroupSpanAssignment(MYSQL *conn, MYSQL_RES *res_set, Rack &rack) {
   MYSQL_ROW row;
   int tgId, spanNumber, lcNumber, mgNumber, srNumber;

   if (!res_set) {
      return;
   }

   int idx;
   while ((row = mysql_fetch_row(res_set)) != NULL) {
      tgId = atoi(row[0]) - 1;
      spanNumber = atoi(row[1]) - 1;
      lcNumber = atoi(row[2]) - 1;
      mgNumber = atoi(row[3]) - 1;
      srNumber = atoi(row[4]) - 1;
      idx = srNumber * MAX_SPAN_SUBRACK + mgNumber * MAX_SPAN_MEDIA_GATEWAY + lcNumber * MAX_SPAN_LINE_CARD + spanNumber;
      rack.trunkGroups[tgId].spans[rack.trunkGroups[tgId].usedSpans++] = idx;
      rack.spans[idx].trunkGroup = tgId;
   }
}

void ConfigWrapper::processTrunkGroupLineCardAssignment(MYSQL *conn, MYSQL_RES *res_set, Rack &rack) {
   MYSQL_ROW row;
   int tgId, lcNumber, mgNumber, srNumber;

   if (!res_set) {
      return;
   }

   int idx;
   while ((row = mysql_fetch_row(res_set)) != NULL) {
      tgId = atoi(row[0]) - 1;
      lcNumber = atoi(row[1]) - 1;
      mgNumber = atoi(row[2]) - 1;
      srNumber = atoi(row[3]) - 1;
      idx = srNumber * MAX_LINE_CARDS_SUBRACK + mgNumber * MAX_LINE_CARDS_MEDIA_GATEWAY + lcNumber
;
      rack.lineCards[idx].trunkGroups[rack.lineCards[idx].usedTrunkGroups++] = tgId;
   }
}

void ConfigWrapper::processApplication(MYSQL *conn, MYSQL_RES *res_set, Rack &rack) {
   MYSQL_ROW row;
   int appId;
   char *appName, *appUri;

   if (!res_set) {
      return;
   }

   while ((row = mysql_fetch_row(res_set)) != NULL) {
      appId = atoi(row[0]) - 1;
      appName = row[1];
      appUri = row[2];
      strcpy(rack.apps[appId].name, appName);
      strcpy(rack.apps[appId].voiceXmlUri, appUri);
   }
}

void ConfigWrapper::processDNIS(MYSQL *conn, MYSQL_RES *res_set, Rack &rack) {
   MYSQL_ROW row;
   int dnisId, appId;
   char *startN, *endN;

   if (!res_set) {
      return;
   }

   while ((row = mysql_fetch_row(res_set)) != NULL) {
      dnisId = atoi(row[0]) - 1;
      appId = atoi(row[1]) - 1;
      startN = row[2];
      endN = row[3];
      rack.dniss[dnisId].app = appId;
      strcpy(rack.dniss[dnisId].startPhoneNumber, startN);
      strcpy(rack.dniss[dnisId].endPhoneNumber, endN);
      rack.dniss[dnisId].used = true;
   }
}

void ConfigWrapper::processAppTrunkAssignment(MYSQL *conn, MYSQL_RES *res_set, Rack &rack) {
   MYSQL_ROW row;
   int tgId, appId;

   if (!res_set) {
      return;
   }

   while ((row = mysql_fetch_row(res_set)) != NULL) {
      appId = atoi(row[0]) - 1;
      tgId = atoi(row[1]) - 1;
      rack.apps[appId].trunkGroups[rack.apps[appId].usedTrunkGroups++] = tgId;
      rack.apps[appId].used = true;
   }
}


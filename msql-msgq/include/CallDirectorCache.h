#ifndef __CallDirectorCache_h__
#define __CallDirectorCache_h__

#include "CallDirectorCacheDefs.h"
 
struct CallDirector {
   bool used;

   char name[MAX_NAME_SIZE];
   char ip[MAX_NAME_SIZE];
};
 
struct SpeechServer {

   bool used;

   char name[MAX_NAME_SIZE];
   char ip[MAX_NAME_SIZE];

   unsigned short availableAsrs;
   unsigned short availableRtpPorts;
};

struct Application {
   bool used;

   char name[MAX_NAME_SIZE];
   char voiceXmlUri[MAX_URI];

   unsigned short trunkGroups[MAX_TRUNK_GROUPS_APPLICATION];
   unsigned short usedTrunkGroups;
};

struct DNIS {
   bool used;

   char startPhoneNumber[MAX_PHONE_NUMBER];
   char endPhoneNumber[MAX_PHONE_NUMBER];
   unsigned short app;
};

struct Span {

   bool used;

   char name[MAX_NAME_SIZE];

   int availableChannels;
   unsigned short trunkGroup;
};

struct Carrier {
   bool used;

   int id;
   char name[MAX_CARRIER_NAME];
};

struct TrunkGroup {
   bool used;

   char name[MAX_NAME_SIZE];

   unsigned short flags; // TrunkGroupConst

   unsigned short carrier; 
   unsigned short spans[MAX_SPANS_TRUNK_GROUP];
   unsigned short usedSpans;
};

struct LineCard {

   bool used;

   char name[MAX_NAME_SIZE];
   char ip[MAX_NAME_SIZE];

   unsigned short trunkGroups[MAX_TRUNK_GROUPS_LINE_CARD];
   unsigned short usedTrunkGroups;
};

struct MediaGateway {
   bool used;

   char name[MAX_NAME_SIZE];
   char ip[MAX_NAME_SIZE];

   unsigned short firstLineCard;
};

struct Rack {
   bool used;

   MediaGateway mediaGateways[MAX_MEDIA_GATEWAYS_RACK];
   SpeechServer speechServers[MAX_SPEECH_SERVERS_RACK];
   CallDirector callDirectors[MAX_CALL_DIRECTORS_RACK];

   LineCard lineCards[MAX_LINE_CARDS_RACK];
   TrunkGroup trunkGroups[MAX_TRUNK_GROUPS_RACK];
   Span spans[MAX_SPAN_RACK];
   Carrier carriers[MAX_CARRIERS];

   Application apps[MAX_APPLICATIONS];
   DNIS dniss[MAX_DNISS];

   int availableChannels[MAX_SPAN_RACK];
   int availableAsrs[MAX_SPEECH_SERVERS_RACK];
};

#endif // __CallDirectorCache_h__

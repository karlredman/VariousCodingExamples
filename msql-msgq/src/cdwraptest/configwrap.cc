#include <stdio.h>
#include "ConfigWrapper.h"

int main() {
   Rack rack;
   ConfigWrapper w("configuration");

   printf("Hi\n");
   w.select(rack); 

   printf("%s %s\n", rack.callDirectors[0].name, rack.callDirectors[0].ip);
   printf("%s %s\n", rack.callDirectors[1].name, rack.callDirectors[1].ip);

   printf("%s %s %d %d\n", rack.speechServers[0].name, rack.speechServers[0].ip, rack.speechServers[0].availableRtpPorts, rack.speechServers[0].availableAsrs);
   printf("%s %s %d %d\n", rack.speechServers[7].name, rack.speechServers[7].ip, rack.speechServers[7].availableRtpPorts, rack.speechServers[7].availableAsrs);

   printf("%s %s\n", rack.mediaGateways[0].name, rack.mediaGateways[0].ip);
   printf("%s %s\n", rack.mediaGateways[2].name, rack.mediaGateways[2].ip);

   int i;

   for (i = 0; i < MAX_LINE_CARDS_RACK; i++) {
      printf("%d: %s %s %d %d %d %d %d\n", i, rack.lineCards[i].name, rack.lineCards[i].ip, rack.lineCards[i].trunkGroups[0], rack.lineCards[i].trunkGroups[1], rack.lineCards[i].trunkGroups[2], rack.lineCards[i].trunkGroups[3], rack.lineCards[i].usedTrunkGroups);
   }

   for (i = 0; i < MAX_SPAN_RACK; i++) {
      printf("%d: %s %d %d\n", i, rack.spans[i].name, rack.spans[i].availableChannels, rack.spans[i].trunkGroup);
   }

   for (i = 0; i < MAX_CARRIERS; i++) {
      printf("%d: %s\n", i, rack.carriers[i].name);
   }

   for (i = 0; i < MAX_TRUNK_GROUPS_RACK; i++) {
      printf("%d: %s %d %d %d %d %d %d %d\n", i, rack.trunkGroups[i].name, rack.trunkGroups[i].flags, rack.trunkGroups[i].carrier, rack.trunkGroups[i].spans[0], rack.trunkGroups[i].spans[1], rack.trunkGroups[i].spans[2], rack.trunkGroups[i].spans[3], rack.trunkGroups[i].usedSpans);
   }

   for (i = 0; i < MAX_APPLICATIONS; i++) {
      printf("%d: %s %s %d %d %d %d\n", i, rack.apps[i].name, rack.apps[i].voiceXmlUri, rack.apps[i].trunkGroups[0], rack.apps[i].trunkGroups[1], rack.apps[i].trunkGroups[2], rack.apps[i].usedTrunkGroups);
   }

   for (i = 0; i < MAX_DNISS; i++) {
      printf("%d: %s %s %d\n", i, rack.dniss[i].startPhoneNumber, rack.dniss[i].endPhoneNumber, rack.dniss[i].app);
   }
return 0;
}

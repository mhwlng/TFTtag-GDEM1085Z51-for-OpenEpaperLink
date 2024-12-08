#include <Arduino.h>

#include "AsyncUDP_W5500.h"

#ifndef defudpcomm
#define defudpcomm

class UDPcomm {
	public:
		UDPcomm();
		~UDPcomm();
		void init(IPAddress localIP);
		void getAPList();
		void netProcessDataReq(struct espAvailDataReq* eadr);
		void netProcessXferComplete(struct espXferComplete* xfc);
		void netProcessXferTimeout(struct espXferComplete* xfc);
		void netSendDataAvail(struct pendingData* pending);
		void netTaginfo(struct TagInfo* taginfoitem);
    private:
		AsyncUDP udp;
		IPAddress localIP;
		void processPacket(AsyncUDPPacket packet);
};

#endif

void init_udp(IPAddress localIP);
void sendAvail(uint8_t wakeupReason);
void prepareExternalDataAvail(struct pendingData *pending, IPAddress remoteIP);
void mac2hex(uint8_t *mac, char *hexBuffer);

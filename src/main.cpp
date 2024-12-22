#include <Arduino.h>
#include <WiFi.h>

#include "AsyncUDP.h"

#include <AsyncWebServer_ESP32_SC_W5500.h>

#include "commstructs.h"
#include "main.h"
#include "udp.h"

#include "Display_EPD_W21_spi.h"
#include "Display_EPD_W21.h"

#define MISO_GPIO                    12//GPIO12
#define MOSI_GPIO                    11//GPIO11
#define SCK_GPIO                     13//GPIO13
#define CS_GPIO                      14//GPIO14
#define INT_GPIO                     10//GPIO10
//#define ETH_RST_PIN                 9//GPIO9

void advertiseTagTask(void *parameter) {
	sendAvail(0xFC);
	while (true) {
		vTaskDelay(60000 / portTICK_PERIOD_MS);
	  sendAvail(0);
	}
}

void drawImage(uint8_t *buffer, uint8_t dataType) {

	EPD_Init(); //Full screen refresh initialization.
	EPD_WhiteScreen_ALL(&buffer[0],&buffer[81600]); //To Display one image using full screen refresh.
	EPD_DeepSleep(); //Enter the sleep mode and please do not delete it, otherwise it will reduce the lifespan of the screen.

}

void Ethernet_event(WiFiEvent_t event)
{
  switch (event)
  {
    case ARDUINO_EVENT_ETH_START:
      AWS_LOG(F("\nETH Started"));

      uint8_t  address[6];
      WiFi.macAddress(address);
    	char hexmac1[40];
    	sprintf(hexmac1, "GDEM108Z51-%02X%02X%02X", address[3],address[4], address[5]);
      ETH.setHostname(hexmac1);
      break;

    case ARDUINO_EVENT_ETH_CONNECTED:
      AWS_LOG(F("ETH Connected"));
      break;

    case ARDUINO_EVENT_ETH_GOT_IP:
      if (!ESP32_W5500_eth_connected)
      {
        AWS_LOG3(F("ETH MAC: "), ETH.macAddress(), F(", IPv4: "), ETH.localIP());

        if (ETH.fullDuplex())
        {
          AWS_LOG0(F("FULL_DUPLEX, "));
        }
        else
        {
          AWS_LOG0(F("HALF_DUPLEX, "));
        }

        AWS_LOG1(ETH.linkSpeed(), F("Mbps"));

        ESP32_W5500_eth_connected = true;
      }

      break;

    case ARDUINO_EVENT_ETH_DISCONNECTED:
      AWS_LOG("ETH Disconnected");
      ESP32_W5500_eth_connected = false;
      break;

    case ARDUINO_EVENT_ETH_STOP:
      AWS_LOG("ETH Stopped");
      ESP32_W5500_eth_connected = false;
      break;

    default:
      break;
  }
}


void setup() {
	Serial.begin(115200);
  
  /*
  SPIRAM pins:
33 SPICLK
32 SPICS0
28 SPICS1  
35 SPID
34 SPIQ
31 SPIWP
30 SPIHD
38 IO33
39 IO34
40 IO35
41 IO36
42 IO37


IO21                         !!!!
IO17                         !!!!
IO16 XTAL                    !!!!
IO18              CAMERA     !!!!
IO15 XTAL         CAMERA     !!!!
IO3               CAMERA
IO2               CAMERA
IO1               CAMERA
IO0                          !!!!
IO44 UARTRX
IO43 UARTTX
IO20 USBP                           
IO19 USBN                           
IO48 SPICLK_N     CAMERA
IO47 SPICLK_P     CAMERA
IO46              CAMERA
IO45              CAMERA
IO42 MTMS         CAMERA
IO41 MTDI         CAMERA
IO40 MTDO         CAMERA
IO39 MTCLK        CAMERA
IO38              CAMERA

IO37 SPIRAM
IO36 SPIRAM
IO35 SPIRAM
IO34 SPIRAM
IO33 SPIRAM

  */

  pinMode(EPD_W21_BUSY, INPUT);  //BUSY
  pinMode(EPD_W21_RST, OUTPUT); //RES    
  pinMode(EPD_W21_CS2, OUTPUT); //CS2     
  pinMode(EPD_W21_CS, OUTPUT); //CS     
   
  pinMode(EPD_W21_CLK, OUTPUT); //SCLK      
  pinMode(EPD_W21_MOSI, OUTPUT); //SDI         

  while (!Serial && (millis() < 5000));

  delay(500);

  Serial.setDebugOutput(true);

  uint8_t  address[6];
	WiFi.macAddress(address);

  WiFi.onEvent(Ethernet_event);

  ETH.begin( MISO_GPIO, MOSI_GPIO, SCK_GPIO, CS_GPIO, INT_GPIO, SPI_CLOCK_MHZ, ETH_SPI_HOST, address );

  ESP32_W5500_waitForConnect();

	vTaskDelay(1000 / portTICK_PERIOD_MS);

	init_udp(ETH.localIP());

	xTaskCreate(advertiseTagTask, "Tag alive", 6000, NULL, 2, NULL);
}

void loop() {
	vTaskDelay(10000 / portTICK_PERIOD_MS);
  /*
    delay(5000);
    Serial.println("\n\n##################################");
    Serial.printf("Internal Total heap %d, internal Free Heap %d\n", ESP.getHeapSize(), ESP.getFreeHeap());
    Serial.printf("SPIRam Total heap %d, SPIRam Free Heap %d\n", ESP.getPsramSize(), ESP.getFreePsram());
    Serial.printf("ChipRevision %d, Cpu Freq %d, SDK Version %s\n", ESP.getChipRevision(), ESP.getCpuFreqMHz(), ESP.getSdkVersion());
    Serial.printf("Flash Size %d, Flash Speed %d\n", ESP.getFlashChipSize(), ESP.getFlashChipSpeed());
    Serial.println("##################################\n\n");

    Serial.printf("Total heap: %d\n", ESP.getHeapSize());
    Serial.printf("Free heap: %d\n", ESP.getFreeHeap());
    Serial.printf("Total PSRAM: %d\n", ESP.getPsramSize());
    Serial.printf("Free PSRAM: %d\n\n", ESP.getFreePsram());

    //Serial.printf("ESP32 Partition table:\n");
    //Serial.printf("| Type | Sub |  Offset  |   Size   |       Label      |\n");
    //Serial.printf("| ---- | --- | -------- | -------- | ---------------- |\n");
    //esp_partition_iterator_t pi = esp_partition_find(ESP_PARTITION_TYPE_ANY, ESP_PARTITION_SUBTYPE_ANY, NULL);
    //if (pi != NULL) {
    //    do {
    //        const esp_partition_t* p = esp_partition_get(pi);
    //        Serial.printf("|  %02x  | %02x  | 0x%06X | 0x%06X | %-16s |\r\n",
    //                      p->type, p->subtype, p->address, p->size, p->label);
    //    } while (pi = (esp_partition_next(pi)));
    //}
*/

}

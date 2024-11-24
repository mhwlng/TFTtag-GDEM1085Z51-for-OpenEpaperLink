#include <FS.h>

#include <Wire.h>
#include <Arduino.h>

#include <SPI.h>
#include <WiFi.h>

#include "commstructs.h"
#include "main.h"
#include "udp.h"

#include "Display_EPD_W21_spi.h"
#include "Display_EPD_W21.h"
#include "Ap_29demo.h"  


const char *ssid = "xxx";
const char *password = "yyy";

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

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  IPAddress IP = WiFi.localIP();


	vTaskDelay(1000 / portTICK_PERIOD_MS);

	init_udp();

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

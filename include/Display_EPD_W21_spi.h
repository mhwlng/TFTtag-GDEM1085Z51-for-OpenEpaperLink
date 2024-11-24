#ifndef _DISPLAY_EPD_W21_SPI_
#define _DISPLAY_EPD_W21_SPI_
#include "Arduino.h"

//IO settings
#define EPD_W21_BUSY 0  //BUSY
#define EPD_W21_RST 16  //RES
#define EPD_W21_CS2 17 //CS2
#define EPD_W21_CS 21 //CS

#define EPD_W21_CLK 18   // CLK pin used by CAMERA !!
#define EPD_W21_MOSI  15 // MOSI pin used by CAMERA !!

//IO settings
#define isEPD_W21_BUSY digitalRead(EPD_W21_BUSY)  //BUSY
#define EPD_W21_RST_0 digitalWrite(EPD_W21_RST,LOW)  //RES
#define EPD_W21_RST_1 digitalWrite(EPD_W21_RST,HIGH)
#define EPD_W21_CS2_0 digitalWrite(EPD_W21_CS2,LOW) //CS2
#define EPD_W21_CS2_1 digitalWrite(EPD_W21_CS2,HIGH)
#define EPD_W21_CS_0 digitalWrite(EPD_W21_CS,LOW) //CS
#define EPD_W21_CS_1 digitalWrite(EPD_W21_CS,HIGH)

#define EPD_W21_CLK_0 digitalWrite(EPD_W21_CLK,LOW)   // CLK pin used by CAMERA !!
#define EPD_W21_CLK_1 digitalWrite(EPD_W21_CLK,HIGH)
#define EPD_W21_MOSI_0  digitalWrite(EPD_W21_MOSI,LOW) // MOSI pin used by CAMERA !!
#define EPD_W21_MOSI_1  digitalWrite(EPD_W21_MOSI,HIGH) 



void SPI_Write(uint8_t value);
void EPD_W21_WriteDATA(uint8_t datas);
void EPD_W21_WriteCMD(uint8_t command);
void EPD_W21_WriteDATA1(uint8_t datas);
void EPD_W21_WriteCMD1(uint8_t command);
void EPD_W21_WriteDATA2(uint8_t datas);
void EPD_W21_WriteCMD2(uint8_t command);
#endif 

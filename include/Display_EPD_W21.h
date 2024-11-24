#ifndef _DISPLAY_EPD_W21_H_
#define _DISPLAY_EPD_W21_H_


#define EPD_WIDTH   1360/2
#define EPD_HEIGHT  480
#define EPD_ARRAY  EPD_WIDTH*EPD_HEIGHT/8  


//Full screen refresh display
void EPD_Init(void); 
void EPD_WhiteScreen_ALL(const uint8_t* datasBW,const uint8_t* datasRW);

void EPD_Init_180(void);	
void EPD_WhiteScreen_ALL180(const uint8_t* datasBW,const uint8_t* datasRW);
void EPD_WhiteScreen_White(void);
void EPD_DeepSleep(void); 


#endif



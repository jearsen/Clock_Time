#ifndef __Parse_command_H__
#define __Parse_command_H__


#include "stm32f10x.h" 
#include "UART.h"
#include "wifi.h"
#include "Work_LED.h"
#include "UART2.h"
#include "GeneralTim.h"
#include "UART3.h"

#define MAX_RCV_ESP8266_LEN  256   

extern u16 Tance;
extern u16 CO_Temp;
u8 ESP8266_Check_Num(u8 *Buf, u8 Len);
void Esp8266_Analyze_Saddr(unsigned int Saddr, unsigned char zcmd,u16 CO_Value);
void Analyze_instruction(u8 *RecBuf, u16 Reclen);











#endif






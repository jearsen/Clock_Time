#ifndef __UART_Screen_H__
#define __UART_Screen_H__



#include "stm32f10x.h"
#include "UART2.h"
#include "DS3231.h"
#include "AT24CXX.h"
#include "DHT11.h"
#include "GeneralTim.h"
#include "wifi.h"
#include "Parse_command.h"
#include "zigbee.h"


extern u8 Alarm_hour;
extern u8 Alarm_Minutes;
extern u8 Alarm_Month;
extern u8 Alarm_Date;
extern u8 Alarm_flag;

extern u16 Set_Safe_CO;
extern u16 Set_Keep_CO;
extern u16 Set_Danger_CO;

extern u16 Set_Safe_Tance;
extern u16 Set_Keep_Tance;
extern u16 Set_Danger_Tance;

void Dis_Time(void);
void Dis_Data(void);
void Dis_temer(void);
void Buffercls(unsigned char *pBuffer, unsigned char vlaue, unsigned int BufferLength);
void Seting_Time(void);
void Alarm_Clock(void);
void Dis_CO(void);
void Dis_Tance(void);
void Screen_Get_FData(unsigned char rec_tem);
void Screen_Get_NData(unsigned char rec_tem);
void Dis_All_information(void);



























#endif



















#ifndef __DS3231_H__
#define __DS3231_H__



#include "stm32f10x.h"
#include "IIC.h"


#define DS3231_ADDR 0xD0


//∂‘”¶µÿ÷∑0x01-0x18
typedef enum
{
	DS3231_Seconds,
	DS3231_Minutes,
	DS3231_Hours,
	DS3231_Day,
	DS3231_Date,
	DS3231_Month,
	DS3231_Year,
	DS3231_Alarm_1_Seconds,
	DS3231_Alarm_1_Minutes,
	DS3231_Alarm_1_Hours,
	DS3231_Alarm_1_Day_Date,
	DS3231_Alarm_2_Minutes,
	DS3231_Alarm_2_Hours,
	DS3231_Alarm_2_Day_Date,
	DS3231_Control,
	DS3231_Control_Status,
	DS3231_Aging_Offset,
	DS3231_MSB_Temp,
	DS3231_LSB_Temp
}DS3231_ADDRESS;

struct RTC_DataType
{
	u8 Seconds;
	u8 Minutes;
	u8 Hours;
	u8 Day;
	u8 Date;
	u8 Month;
	u8 Year;
};

extern struct RTC_DataType RTC_Data;  
extern u8 RTC_RAW_Data[7];  
void DS3231_Init(void);
void DS3231_GetRTCData(void);
unsigned char B_BCD(unsigned char val);	//B????BCD? 
u8 BCD2HEX(u8 val);
void DS3231_SetRTCData(u8 Year,u8 Month,u8 Date,u8 Day,u8 Hours,u8 Minutes,u8 Seconds);












































#endif

























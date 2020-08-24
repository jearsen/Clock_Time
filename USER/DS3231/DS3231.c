#include "DS3231.h"



u8 RTC_RAW_Data[7];   //存放读时钟
struct RTC_DataType RTC_Data;  


void DS3231_Init(void)
{
	IICwriteByte(DS3231_ADDR,DS3231_Control,0x00);
	IICwriteByte(DS3231_ADDR,DS3231_Control_Status,0x00);
	DS3231_GetRTCData();
}

void DS3231_GetRTCData(void)
{
	IICreadBytes(DS3231_ADDR,DS3231_Seconds,7,RTC_RAW_Data);
	RTC_Data.Seconds = (RTC_RAW_Data[0]&0x0f) + (RTC_RAW_Data[0]>>4)*10;
	RTC_Data.Minutes = (RTC_RAW_Data[1]&0x0f) + (RTC_RAW_Data[1]>>4)*10;
	RTC_Data.Hours = (RTC_RAW_Data[2]&0x0f) + (RTC_RAW_Data[2]>>4)*10;
	RTC_Data.Day = RTC_RAW_Data[3]&0x0f;
	RTC_Data.Date = (RTC_RAW_Data[4]&0x0f) + (RTC_RAW_Data[4]>>4)*10;
	RTC_Data.Month = (RTC_RAW_Data[5]&0x0f) + (RTC_RAW_Data[5]>>4)*10;
	RTC_Data.Year = (RTC_RAW_Data[6]&0x0f) + (RTC_RAW_Data[6]>>4)*10;
}
unsigned char B_BCD(unsigned char val)		//B????BCD?  
{  
	unsigned char k;  

	k = (val/10)<<4 | (val%10);	

	return k;  
} 
u8 BCD2HEX(u8 val)
{
    u8 i;
    i= val&0x0f;
    val >>= 4;
    val &= 0x0f;
    val *= 10;
    i += val;
    
    return i;
}
void DS3231_SetRTCData(u8 Year,u8 Month,u8 Date,u8 Day,u8 Hours,u8 Minutes,u8 Seconds)   //17,2,25,6,14,14,0
{
	u8 data_to_send[7];
	data_to_send[6] = ((Year/10)<<4) | (Year%10);
	data_to_send[5] = ((Month/10)<<4) | (Month%10);
	data_to_send[4] = ((Date/10)<<4) | (Date%10);
	data_to_send[3] = Day;
	data_to_send[2] = ((Hours/10)<<4) | (Hours%10);
	data_to_send[1] = ((Minutes/10)<<4) | (Minutes%10);
	data_to_send[0] = ((Seconds/10)<<4) | (Seconds%10);
	IICwriteBytes(DS3231_ADDR,DS3231_Seconds,7,data_to_send);
}


//void Dis()
//{
//	 
////		if(count_1s != last_count_1s)
////		{
////			Beep_On_Off;
////	 
////		printf("年月日：");
////		printf("%d,%d,%d\r\n",RTC_Data.Year+2000,RTC_Data.Month,RTC_Data.Date);
////		printf("时分秒：");
////		printf("%d,%d,%d\r\n",RTC_Data.Hours,RTC_Data.Minutes,RTC_Data.Seconds);
////			last_count_1s = count_1s;
////		}
////		
//}
























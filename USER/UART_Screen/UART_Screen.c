#include "UART_Screen.h"

u8 Alarm_hour ;
u8 Alarm_Minutes ;
u8 Alarm_Month ;
u8 Alarm_Date ;
u8 Alarm_flag = 1 ;

u16 Set_Safe_CO;
u16 Set_Keep_CO;
u16 Set_Danger_CO;

u16 Set_Safe_Tance;
u16 Set_Keep_Tance;
u16 Set_Danger_Tance;

void Dis_Time(void)
{
	
	u8  Hour_Temp[7] = "n0.val=";
	u8 Dis_Hour[2] = {0};
	u8  Minutes_Temp[7] = "n1.val=";
	u8 Dis_Minutes[2] = {0};
	u8 stop_str[3] = {0xff,0xff,0xff};    //结束符
	
	USART2_Send_Len_Str(Hour_Temp,7);
	Dis_Hour[0] = RTC_Data.Hours/10+'0';
	Dis_Hour[1] = RTC_Data.Hours%10+'0';
	USART2_Send_Len_Str(Dis_Hour,2);
	USART2_Send_Len_Str(stop_str,3);
	
	USART2_Send_Len_Str(Minutes_Temp,7);
	Dis_Minutes[0] = RTC_Data.Minutes/10+'0';
	Dis_Minutes[1] = RTC_Data.Minutes%10+'0';
	USART2_Send_Len_Str(Dis_Minutes,2);
	USART2_Send_Len_Str(stop_str,3);
	
}


void Dis_Data(void)
{
	u8 Month_Temp[7] = "n2.val=";
	u8 Dis_Month[2] = {0};
	u8 Date_Temp[7] = "n3.val=";
	u8 Dis_Date[2] = {0};
	u8 Day_Temp[7] = "n4.val=";
	u8 Dis_Day[2] = {0};
	u8 stop_str[3] = {0xff,0xff,0xff};    //结束符
	
	USART2_Send_Len_Str(Month_Temp,7);
	Dis_Month[0] = RTC_Data.Month/10+'0';
	Dis_Month[1] = RTC_Data.Month%10+'0';
	USART2_Send_Len_Str(Dis_Month,2);
	USART2_Send_Len_Str(stop_str,3);
	
	USART2_Send_Len_Str(Date_Temp,7);
	Dis_Date[0] = RTC_Data.Date/10+'0';
	Dis_Date[1] = RTC_Data.Date%10+'0';
	USART2_Send_Len_Str(Dis_Date,2);
	USART2_Send_Len_Str(stop_str,3);
	
	USART2_Send_Len_Str(Day_Temp,7);
	Dis_Day[0] = RTC_Data.Day/10+'0';
	Dis_Day[1] = RTC_Data.Day%10+'0';
	USART2_Send_Len_Str(Dis_Day,2);
	USART2_Send_Len_Str(stop_str,3);
}

void Dis_temer(void)
{
	u8 temperature_Temp[8] = "n14.val=";
	u8 Dis_temperature[2] = {0};
	u8 stop_str[3] = {0xff,0xff,0xff}; 
	
	if (DHT11_Read_TempAndHumidity() == SUCCESS)
	{
	USART2_Send_Len_Str(temperature_Temp,8);
	Dis_temperature[0] = temperature_int/10+'0';
	Dis_temperature[1] = temperature_int%10+'0';
	USART2_Send_Len_Str(Dis_temperature,2);
	USART2_Send_Len_Str(stop_str,3);
	}
}

void Dis_CO(void)
{
	u8 Co_Temp[8] = "n18.val=";
	u8 Dis_Co[3] = {0};
	u8 stop_str[3] = {0xff,0xff,0xff}; 
	USART2_Send_Len_Str(Co_Temp,8);
	Dis_Co[0] = CO_Temp/100+'0';
	Dis_Co[1] = CO_Temp%100/10+'0';
	Dis_Co[2] = CO_Temp%10+'0';
	USART2_Send_Len_Str(Dis_Co,3);
	USART2_Send_Len_Str(stop_str,3);
}

void Dis_Tance(void)
{
	u8 Tance_Temp[8] = "n19.val=";
	u8 Dis_Tance[3] = {0};
	u8 stop_str[3] = {0xff,0xff,0xff}; 
	USART2_Send_Len_Str(Tance_Temp,8);
	Dis_Tance[0] = Tance/100+'0';
	Dis_Tance[1] = Tance%100/10+'0';
	Dis_Tance[2] = Tance%10+'0';
	USART2_Send_Len_Str(Dis_Tance,3);
	USART2_Send_Len_Str(stop_str,3);
}
  void Seting_Time(void)
	{
		static u8 Set_Hours;
		static u8 Set_Minutes;
		static u8 Set_Month;
		static u8 Set_Date;
		static u8 Set_Day;
		if(rec_flag2 == 1)
		{		
			if(RxBuffer2[0] == '#'&& RxBuffer2[14] == '&')
			{	 
				switch(RxBuffer2[1])
				{  
					case 0xae:        //设置时间
					Set_Hours = RxBuffer2[2]|RxBuffer2[3]<<8;
          Set_Minutes = RxBuffer2[6]|RxBuffer2[7]<<8;
					break;
					case 0xaf:        //设置日期
					Set_Month= RxBuffer2[2]|RxBuffer2[3]<<8;
					Set_Date = RxBuffer2[6]|RxBuffer2[7]<<8;
					Set_Day = RxBuffer2[10]|RxBuffer2[11]<<8;
					break;
					case 0xad:        //设置CO
					Set_Safe_CO= RxBuffer2[2]|RxBuffer2[3]<<8;
					Set_Keep_CO = RxBuffer2[6]|RxBuffer2[7]<<8;
					Set_Danger_CO = RxBuffer2[10]|RxBuffer2[11]<<8;
					TCP_SEVER_SendString(12,Multiple_ID_0);
					break;
					case 0xab:        //设置距离
           Led1_On;
					Set_Danger_Tance = RxBuffer2[2]|RxBuffer2[3]<<8;
					Set_Keep_Tance = RxBuffer2[6]|RxBuffer2[7]<<8;
		      Set_Safe_Tance  = RxBuffer2[10]|RxBuffer2[11]<<8;
					Zigbee_Send_instruction(open_cpu,curtain_addr);
					break;
				}
					DS3231_SetRTCData(18,Set_Month,Set_Date,Set_Day,Set_Hours,Set_Minutes,00);
				
			}
			
		 else if(RxBuffer2[0] == '!'&& RxBuffer2[18] == '&')
			{
				switch(RxBuffer2[1])
				{  
					case 0xae:    //打开闹钟
					Alarm_hour = RxBuffer2[2]|RxBuffer2[3]<<8;
					Alarm_Minutes = RxBuffer2[6]|RxBuffer2[7]<<8;
					Alarm_Month = RxBuffer2[10]|RxBuffer2[11]<<8;
				  Alarm_Date = RxBuffer2[10]|RxBuffer2[11]<<8;
					AT24CXX_Write_Alarm_Value();
					Alarm_flag = 1;
					break;
					case 0xaf:     //关闭闹钟
					Alarm_flag = 0;
					break;
					case 0xad:     
					break;
				}
//				DS3231_SetRTCData(18,Set_Month,Set_Date,Set_Day,Set_Hours,Set_Minutes,00);
			}
     Buffercls(RxBuffer2,0,19);
		 rec_flag2 = 0;
		}
	
	}

//	void Buffercls(unsigned char *pBuffer, unsigned char vlaue, unsigned int BufferLength)  //以某个数清数组数组 清的值 数组长度
//{
//	while(BufferLength--)
//	{
//		*pBuffer = vlaue;

//		pBuffer++;
//	}
//} 


  void Alarm_Clock(void)
	{
		
		if(Alarm_flag)
		{
			AT24CXX_Read_Alarm_Value();
			if(Alarm_hour==RTC_Data.Hours && Alarm_Minutes==RTC_Data.Minutes && Alarm_Month==RTC_Data.Month &&  Alarm_Date==RTC_Data.Date)
			{
				Beep_On;
			}
		}
		else if (Alarm_flag == 0)
		{  
				Beep_Off;
		}
	}


 void Screen_Get_FData(unsigned char rec_tem)
{	 
		 static unsigned char static_rec = 0;   //开始传输
			if(rec_tem == '#')
				{	
					static_rec = 1;
					RxCounter2 = 0;
					}
					if(static_rec )
					{	
						RxBuffer2[RxCounter2++] = rec_tem;
						if(RxCounter2 == 15)
						{
							Led1_On;
//							USART1_Send_Len_Str(RxBuffer2,15);
							static_rec = 0;
							rec_flag2 = 1;
						}
					} 
				}

 void Screen_Get_NData(unsigned char rec_tem)
 {
		static unsigned char static_rec2 = 0;   //开始传输
		if(rec_tem == '!')
		{   
		  static_rec2 = 1;
		  RxCounter2 = 0;
		  }
		if(static_rec2 )
		{ 
		  RxBuffer2[RxCounter2++] = rec_tem;
		if(RxCounter2 == 19)
		{   
	
		  static_rec2 = 0;
		  rec_flag2 = 1;
		}
		}
	 
 }


void Dis_All_information(void)
{   
	  Dis_Time();  //显示时间
		Dis_Data();  //显示日期
		Dis_temer(); //显示温湿度
	  Dis_CO();    //显示一氧化碳
		Dis_Tance();  //显示距离
		
		
}










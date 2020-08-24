#include "stm32f10x.h"
#include "Work_LED.h"
#include "UART.h"
#include "UART2.h"
#include "SYSTICK.h"
#include "IIC.h"
#include "AT24CXX.h"
#include "DS3231.h"
#include "GeneralTim.h"
#include "UART_Screen.h"
#include "DHT11.h"
#include "wifi.h"
#include "UART3.h"
#include "Parse_command.h"
#include "zigbee.h"


int main(void)
{

	delay_Init(72);
	LED_Confing();
	USART1_Configuration();
	USART2_Configuration();
	USART3_Configuration();
	General_TIM2_Init();
	General_TIM3_Init();
	IIC_Init();
  DS3231_Init();
	DHT11_Init();
	Esp8266_Server_Init();
//	DS3231_SetRTCData(18,12,06,4,21,9,00); 	


	while(1)
	{ 	
    Analyze_instruction(RxBuffer1,10);
	  Dis_All_information();
	  Seting_Time();
		DS3231_GetRTCData();
    Alarm_Clock();
	}
}
















































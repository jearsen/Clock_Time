#ifndef __DHT11_H__
#define __DHT11_H__


#include "stm32f10x.h"
#include "SYSTICK.h"
#include "Work_LED.h"




extern unsigned char humidity_int;     //ʪ�ȵ���������
extern unsigned char humidity_deci;    //ʪ�ȵ�С������
extern unsigned char temperature_int;	//�¶ȵ���������
extern unsigned char temperature_deci; //�¶ȵ�С������



#define DHT11_GPIO_APBxClkCmd      RCC_APB2PeriphClockCmd
#define DHT11_GPIO_CLK             RCC_APB2Periph_GPIOD
#define DHT11_GPIO_PROT            GPIOD
#define DHT11_GPIO_PIN             GPIO_Pin_15

#define DHT11_L                    GPIO_ResetBits(DHT11_GPIO_PROT,DHT11_GPIO_PIN)
#define DHT11_H                    GPIO_SetBits(DHT11_GPIO_PROT,DHT11_GPIO_PIN)
#define DHT11_IN                 GPIO_ReadInputDataBit(DHT11_GPIO_PROT,DHT11_GPIO_PIN)//��ȡ�����˿ڵ���ֵ


void DHT11_State(void);
void DHT11_GPIO_Confing(void);  
unsigned char Read_Byte(void);
void DHT11_Init(void);
unsigned char DHT11_Read_TempAndHumidity(void);
	

#endif 






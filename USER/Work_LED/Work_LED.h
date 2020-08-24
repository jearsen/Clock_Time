#ifndef __Work_LED_H__
#define __Work_LED_H__

#include "stm32f10x.h" 


#define   Led_RCC            RCC_APB2Periph_GPIOD


#define   Led_port           GPIOD


#define   Led1               GPIO_Pin_3


//寄存器版本
//#define		LED1_OFF         	    GPIOB->BSRR = GPIO_Pin_5
//#define		LED1_ON         	    GPIOB->BRR  = GPIO_Pin_5
//#define   LED1_On_Off      	{GPIOB->ODR ^= GPIO_Pin_5;}  
//#define		LED2_OFF         	    GPIOD->BSRR = GPIO_Pin_6
//#define		LED2_ON         	    GPIOD->BRR  = GPIO_Pin_6
//#define   LED2_On_Off      	{GPIOD->ODR ^= GPIO_Pin_6;}  
//#define		LED3_OFF         	    GPIOD->BSRR = GPIO_Pin_3
//#define		LED3_ON         	    GPIOD->BRR  = GPIO_Pin_3
//#define   LED3_On_Off      	{GPIOD->ODR ^= GPIO_Pin_3;}    //^	异或，与1异或状态改变，与0异或不变


//固件库版本
#define Led1_On      GPIO_ResetBits(Led_port, Led1)  //低
#define Led1_Off     GPIO_SetBits(Led_port, Led1)    //高
#define Led1_On_Off  GPIO_PinReverse(Led_port, Led1)
#define Led2_On      GPIO_ResetBits(Led_port, Led3)
#define Led2_Off     GPIO_SetBits(Led_port, Led3)
#define Led2_On_Off  GPIO_PinReverse(Led_port, Led3)
#define Led3_On      GPIO_ResetBits(Led_port, Led1)
#define Led3_Off     GPIO_SetBits(Led_port, Led1)
#define Led3_On_Off  GPIO_PinReverse(Led_port, Led1)


#define Beep_RCC           RCC_APB2Periph_GPIOC
#define Beep_port           GPIOC
#define Beep1               GPIO_Pin_7
#define Beep_On      GPIO_ResetBits(Beep_port, Beep1)
#define Beep_Off     GPIO_SetBits(Beep_port, Beep1)
#define Beep_On_Off  GPIO_PinReverse(Beep_port, Beep1)





 void Led_goio_init(void);
 void LED_Confing(void);
 void GPIO_PinReverse(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
// void BEEP_Confing(void);

#endif 






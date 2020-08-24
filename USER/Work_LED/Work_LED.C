#include "Work_LED.h"

 void LED_Confing(void)
 {    //声明一个结构体
	   GPIO_InitTypeDef GPIO_InitStructure;
	 // IO对应IO口的时钟
		 RCC_APB2PeriphClockCmd(Led_RCC,ENABLE);
	   RCC_APB2PeriphClockCmd(Beep_RCC,ENABLE);
	 	 //初始化引脚
		GPIO_InitStructure.GPIO_Pin = Led1|Beep1;
	 //设置速率
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	 //设置模式
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //  判断是推挽输出还是开漏输出（推挽输出）
	//使能  将上面的配置存到寄存器中
		GPIO_Init(Led_port,&GPIO_InitStructure);
	  GPIO_Init(Beep_port,&GPIO_InitStructure);
		Led1_Off;	 Beep_Off;
 }
 
 void BEEP_Confing()
 {
	 GPIO_InitTypeDef GPIO_InitStructure;
	 RCC_APB2PeriphClockCmd(Beep_RCC,ENABLE);
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	 GPIO_InitStructure.GPIO_Pin = Beep1;
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_Init(Beep_port,&GPIO_InitStructure);
	 Beep_Off;
 }

 
 
 
 // 单个IO端口取反
void GPIO_PinReverse(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin));
  
  GPIOx->ODR ^=  GPIO_Pin;
}


// void Led_goio_init(void)
//{
//  GPIO_InitTypeDef GPIO_InitStructure = {0};

//  RCC_APB2PeriphClockCmd(Led_crc, ENABLE);

//  GPIO_InitStructure.GPIO_Pin = Led;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_Init(Led_port, &GPIO_InitStructure);

//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  Led_Off;
//}

//void GPIO_PinReverse(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
//{
//  /* Check the parameters */
//  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
//  assert_param(IS_GPIO_PIN(GPIO_Pin));
//  
//  GPIOx->ODR ^=  GPIO_Pin;
//}


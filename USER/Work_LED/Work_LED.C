#include "Work_LED.h"

 void LED_Confing(void)
 {    //����һ���ṹ��
	   GPIO_InitTypeDef GPIO_InitStructure;
	 // IO��ӦIO�ڵ�ʱ��
		 RCC_APB2PeriphClockCmd(Led_RCC,ENABLE);
	   RCC_APB2PeriphClockCmd(Beep_RCC,ENABLE);
	 	 //��ʼ������
		GPIO_InitStructure.GPIO_Pin = Led1|Beep1;
	 //��������
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	 //����ģʽ
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //  �ж�������������ǿ�©��������������
	//ʹ��  ����������ô浽�Ĵ�����
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

 
 
 
 // ����IO�˿�ȡ��
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

#include "SYSTICK.h"
  
	static u8 fac_us=0;//us��ʱ������
	static u16 fac_ms=0;//ms��ʱ������
	//CTRL ���Ƽ�״̬�Ĵ���
	//LOAD ��װ����ֵ�Ĵ���
	//VAL  ��ǰ��ֵ�Ĵ���
	void delay_Init(u8 SYSCLK)
	{
		//��յڶ�λ,����λ������
		SysTick->CTRL&=0xfffffffb;
		//��systick�ļ�ʱƵ���趨Ϊ��Ƶ��HCLK/8
		fac_us=SYSCLK/8;
		fac_ms=(u16)fac_us*1000;
	}

    void delay_ms(u16 nms)
		{
			u32 temp;
			SysTick->LOAD=(u32)nms*fac_ms;//ʱ�����(SysTick->LOADΪ24bit)
			SysTick->VAL =0x00;         //��ռ�����
			SysTick->CTRL=0X01;         //��ʼ����  
			do
			{
				temp=SysTick->CTRL;
			}
			while(temp&0x01&&!(temp&(1<<16)));  //�ȴ�ʱ�䵽��  
			SysTick->CTRL=0x00;                 //�رռ�����
			SysTick->VAL =0x00;                 //��ռ�����	  
		}
		

  void delay_us(u16 nus)
	{
		u32 temp;
		SysTick->LOAD=nus*fac_us;	//ʱ�����	  
		SysTick->VAL =0x00;       //��ռ�����
		SysTick->CTRL=0x01;       //��ʼ���� 	 
		do
{
		temp=SysTick->CTRL;
}
//ͨ��(temp&0x01)��� SysTick ��ʹ��λ������ Systick ��ʱ�����رն���������ѭ��
		while(temp&0x01&&!(temp&(1<<16)));  //�ȴ�ʱ�䵽��  
		SysTick->CTRL=0x00;                 //�رռ�����
		SysTick->VAL =0x00;                 //��ռ�����	 	
	}		


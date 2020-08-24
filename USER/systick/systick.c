#include "SYSTICK.h"
  
	static u8 fac_us=0;//us延时倍乘数
	static u16 fac_ms=0;//ms延时倍乘数
	//CTRL 控制及状态寄存器
	//LOAD 重装载数值寄存器
	//VAL  当前数值寄存器
	void delay_Init(u8 SYSCLK)
	{
		//清空第二位,其他位数不变
		SysTick->CTRL&=0xfffffffb;
		//把systick的计时频率设定为主频的HCLK/8
		fac_us=SYSCLK/8;
		fac_ms=(u16)fac_us*1000;
	}

    void delay_ms(u16 nms)
		{
			u32 temp;
			SysTick->LOAD=(u32)nms*fac_ms;//时间加载(SysTick->LOAD为24bit)
			SysTick->VAL =0x00;         //清空计数器
			SysTick->CTRL=0X01;         //开始倒数  
			do
			{
				temp=SysTick->CTRL;
			}
			while(temp&0x01&&!(temp&(1<<16)));  //等待时间到达  
			SysTick->CTRL=0x00;                 //关闭计数器
			SysTick->VAL =0x00;                 //清空计数器	  
		}
		

  void delay_us(u16 nus)
	{
		u32 temp;
		SysTick->LOAD=nus*fac_us;	//时间加载	  
		SysTick->VAL =0x00;       //清空计数器
		SysTick->CTRL=0x01;       //开始倒数 	 
		do
{
		temp=SysTick->CTRL;
}
//通过(temp&0x01)检查 SysTick 的使能位，避免 Systick 定时器被关闭而导致无限循环
		while(temp&0x01&&!(temp&(1<<16)));  //等待时间到达  
		SysTick->CTRL=0x00;                 //关闭计数器
		SysTick->VAL =0x00;                 //清空计数器	 	
	}		


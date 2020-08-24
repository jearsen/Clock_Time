#include "GeneralTim.h"
 
//定时器3
u32 count_1ms = 0;
u32 last_count_1ms = 0;

u32 time_1ms_count = 0;
u32 last__1ms_count = 0;

u32 count_10ms = 0;
u32 last_count_10ms = 0;

u32 count_100ms = 0;
u32 last_count_100ms = 0;

u32 count_200ms = 0;
u32 last_count_200ms = 0;

u32 count_500ms = 0;
u32 last_count_500ms = 0;

u32 count_1s = 0;
u32 last_count_1s = 0;

u32 count_3s = 0;
u32 last_count_3s = 0;

u32 count_3min = 0;
u32 last_count_3min = 0;

//定时器2
//当前秒数
u32 Ms200 = 0;
u32 Ms500 = 0;
u32 Sec = 0;
u32 Minute = 0;
//上一次秒数
u32 Last_Ms200 = 0;
u32 Last_Ms500 = 0;
u32 Last_Sec = 0;
u32 Last_Minute = 0;


// 中断优先级配置
void General_TIM2_NVIC_Confing(void)
{
	NVIC_InitTypeDef NVIC_InitStructure ;
	//设置中断组为0
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	//设置中断来源
	NVIC_InitStructure.NVIC_IRQChannel = GENERAL_TIM_IRQ;
	//设置主优先级为0
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	//设置抢占优先级为3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
void General_TIM3_NVIC_Confing(void)
{
	NVIC_InitTypeDef NVIC_InitStructure ;
	//设置中断组为0
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	//设置中断来源
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	//设置主优先级为0
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	//设置抢占优先级为3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void   General_TIM2_Mode_Config(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	//开启定时器时钟，即内部时钟钟CK_INT=72
	GENERAL_TIM_APBxClock_FUN(GENERAL_TIM_CLK,ENABLE);
	// 自动重装载寄存器的值，累计TIM_Period+1个频率后产生一个更新或者中断
//  TIM_DeInit(GENERAL_TIM);
//	//配置定时器基础结构体
//  TIM_InternalClockConfig(TIM2);
  //采用内部时钟给TIM2提供时钟源 
	TIM_TimeBaseStructure.TIM_Period = GENERAL_TIM_Period;
	// 时钟预分频数为
	TIM_TimeBaseStructure.TIM_Prescaler = GENERAL_TIM_Prescaler;
	//向上计数
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	//不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	// 初始化定时器
	TIM_TimeBaseInit(GENERAL_TIM,&TIM_TimeBaseStructure);
	//清除中断标志位
	TIM_ClearFlag(GENERAL_TIM,TIM_FLAG_Update);
  //  TIM_ARRPreloadConfig(TIM2, DISABLE); 
	//禁止ARR预装载缓冲器
		// 开启计数器中断
	TIM_ITConfig(GENERAL_TIM,TIM_IT_Update,ENABLE);
	// 使能计数器
  TIM_Cmd(GENERAL_TIM,ENABLE);	
	
}

void   General_TIM3_Mode_Config(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	//开启定时器时钟，即内部时钟钟CK_INT=72
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	// 自动重装载寄存器的值，累计TIM_Period+1个频率后产生一个更新或者中断
//  TIM_DeInit(GENERAL_TIM);
//	//配置定时器基础结构体
//  TIM_InternalClockConfig(TIM2);
  //采用内部时钟给TIM2提供时钟源 
	TIM_TimeBaseStructure.TIM_Period = 9999;
	// 时钟预分频数为
	TIM_TimeBaseStructure.TIM_Prescaler = 71;
	//向上计数
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	//不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	// 初始化定时器
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
	//清除中断标志位
	TIM_ClearFlag(TIM3,TIM_FLAG_Update);
  //  TIM_ARRPreloadConfig(TIM2, DISABLE); 
	//禁止ARR预装载缓冲器
	// 开启计数器中断
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	// 使能计数器
  TIM_Cmd(TIM3,ENABLE);	
	
}

    void General_TIM2_Init(void)
		{
			
			General_TIM2_NVIC_Confing();
			General_TIM2_Mode_Config();

		}
		    void General_TIM3_Init(void)
		{
			
			General_TIM3_NVIC_Confing();
			General_TIM3_Mode_Config();

		}
		
void  GENERAL_TIM_IRQHandler (void)
{
	static u8 ms200_count = 0;
	static u8 ms500_count = 0;
	static u8 Sec_count = 0;
	static u8 Min_count = 0;
	
	if(TIM_GetITStatus(GENERAL_TIM, TIM_FLAG_Update) == SET)
	{

		Sec_count ++;
		ms200_count ++;
		ms500_count ++;
		if(ms200_count > 2)
		{
			Ms200 ++;

			ms200_count = 0;
		}

		if(ms500_count > 5)
		{
			Ms500 ++;		

			ms500_count = 0;
		}

		if(Sec_count > 9) // 秒
		{
			Sec ++;
			
			Min_count ++;
			
			if(Min_count > 59) // 分
			{
				Minute ++;
				
				Min_count = 0;
			}

			Sec_count = 0;
		}
		
 TIM_ClearITPendingBit(TIM2, TIM_FLAG_Update); 		 //清除中断标志位
		
	}		 	
}
void  TIM3_IRQHandler (void)
{
	if ( TIM_GetITStatus( TIM3, TIM_IT_Update) != RESET ) 
	{	
		count_1ms++;

		if(count_1ms % 10 == 0)
		count_10ms ++;

		if(count_1ms % 100 == 0)
		count_100ms ++;

		if(count_1ms % 200 == 0)
		count_200ms ++;

		if(count_1ms % 1000 == 0)
		count_1s ++;

		if(count_1ms % 1800 == 0)
		count_3min ++;

			
    TIM_ClearITPendingBit(TIM3 , TIM_IT_Update);  		 //清除中断标志位
		
	}		 	
}


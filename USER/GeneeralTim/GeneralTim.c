#include "GeneralTim.h"
 
//��ʱ��3
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

//��ʱ��2
//��ǰ����
u32 Ms200 = 0;
u32 Ms500 = 0;
u32 Sec = 0;
u32 Minute = 0;
//��һ������
u32 Last_Ms200 = 0;
u32 Last_Ms500 = 0;
u32 Last_Sec = 0;
u32 Last_Minute = 0;


// �ж����ȼ�����
void General_TIM2_NVIC_Confing(void)
{
	NVIC_InitTypeDef NVIC_InitStructure ;
	//�����ж���Ϊ0
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	//�����ж���Դ
	NVIC_InitStructure.NVIC_IRQChannel = GENERAL_TIM_IRQ;
	//���������ȼ�Ϊ0
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	//������ռ���ȼ�Ϊ3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
void General_TIM3_NVIC_Confing(void)
{
	NVIC_InitTypeDef NVIC_InitStructure ;
	//�����ж���Ϊ0
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	//�����ж���Դ
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	//���������ȼ�Ϊ0
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	//������ռ���ȼ�Ϊ3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void   General_TIM2_Mode_Config(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	//������ʱ��ʱ�ӣ����ڲ�ʱ����CK_INT=72
	GENERAL_TIM_APBxClock_FUN(GENERAL_TIM_CLK,ENABLE);
	// �Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
//  TIM_DeInit(GENERAL_TIM);
//	//���ö�ʱ�������ṹ��
//  TIM_InternalClockConfig(TIM2);
  //�����ڲ�ʱ�Ӹ�TIM2�ṩʱ��Դ 
	TIM_TimeBaseStructure.TIM_Period = GENERAL_TIM_Period;
	// ʱ��Ԥ��Ƶ��Ϊ
	TIM_TimeBaseStructure.TIM_Prescaler = GENERAL_TIM_Prescaler;
	//���ϼ���
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	//����Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	// ��ʼ����ʱ��
	TIM_TimeBaseInit(GENERAL_TIM,&TIM_TimeBaseStructure);
	//����жϱ�־λ
	TIM_ClearFlag(GENERAL_TIM,TIM_FLAG_Update);
  //  TIM_ARRPreloadConfig(TIM2, DISABLE); 
	//��ֹARRԤװ�ػ�����
		// �����������ж�
	TIM_ITConfig(GENERAL_TIM,TIM_IT_Update,ENABLE);
	// ʹ�ܼ�����
  TIM_Cmd(GENERAL_TIM,ENABLE);	
	
}

void   General_TIM3_Mode_Config(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	//������ʱ��ʱ�ӣ����ڲ�ʱ����CK_INT=72
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	// �Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
//  TIM_DeInit(GENERAL_TIM);
//	//���ö�ʱ�������ṹ��
//  TIM_InternalClockConfig(TIM2);
  //�����ڲ�ʱ�Ӹ�TIM2�ṩʱ��Դ 
	TIM_TimeBaseStructure.TIM_Period = 9999;
	// ʱ��Ԥ��Ƶ��Ϊ
	TIM_TimeBaseStructure.TIM_Prescaler = 71;
	//���ϼ���
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	//����Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	// ��ʼ����ʱ��
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
	//����жϱ�־λ
	TIM_ClearFlag(TIM3,TIM_FLAG_Update);
  //  TIM_ARRPreloadConfig(TIM2, DISABLE); 
	//��ֹARRԤװ�ػ�����
	// �����������ж�
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	// ʹ�ܼ�����
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

		if(Sec_count > 9) // ��
		{
			Sec ++;
			
			Min_count ++;
			
			if(Min_count > 59) // ��
			{
				Minute ++;
				
				Min_count = 0;
			}

			Sec_count = 0;
		}
		
 TIM_ClearITPendingBit(TIM2, TIM_FLAG_Update); 		 //����жϱ�־λ
		
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

			
    TIM_ClearITPendingBit(TIM3 , TIM_IT_Update);  		 //����жϱ�־λ
		
	}		 	
}


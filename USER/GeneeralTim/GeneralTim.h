#ifndef __GeneralTim_H__
#define __GeneralTim_H__

#include "stm32f10x.h"
#include "Work_LED.h"

extern u32 count_1ms ;
extern u32 last_count_1ms ;

extern u32 time_1ms_count ;
extern u32 last__1ms_count ;

extern u32 count_10ms;
extern u32 last_count_10ms;

extern u32 count_100ms;
extern u32 last_count_100ms;

extern u32 count_200ms;
extern u32 last_count_200ms;

extern u32 count_500ms;
extern u32 last_count_500ms;

extern u32 count_1s ;
extern u32 last_count_1s;

extern u32 count_3s;
extern u32 last_count_3s;

extern u32 count_3min;
extern u32 last_count_3min;

extern u32 Ms200;
extern u32 Ms500;
extern u32 Sec;
extern u32 Minute;
//上一次秒数
extern u32 Last_Ms200;
extern u32 Last_Ms500;
extern u32 Last_Sec;
extern u32 Last_Minute;
/**************通用定时器TIM参数定义，只限TIM2、3、4、5************/
// 当需要哪个定时器的时候，只需要把下面的宏定义改成1即可
#define GENERAL_TIM2    1
#define GENERAL_TIM3    0
#define GENERAL_TIM4    0
#define GENERAL_TIM5    0

#if  GENERAL_TIM2
#define            GENERAL_TIM                   TIM2
#define            GENERAL_TIM_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            GENERAL_TIM_CLK               RCC_APB1Periph_TIM2
#define            GENERAL_TIM_Period            10000-1
#define            GENERAL_TIM_Prescaler         720-1
#define            GENERAL_TIM_IRQ               TIM2_IRQn
#define            GENERAL_TIM_IRQHandler        TIM2_IRQHandler

//#elif  GENERAL_TIM3
//#define            GENERAL_TIM                   TIM3
//#define            GENERAL_TIM_APBxClock_FUN     RCC_APB1PeriphClockCmd
//#define            GENERAL_TIM_CLK               RCC_APB1Periph_TIM3
//#define            GENERAL_TIM_Period            (1000-1)
//#define            GENERAL_TIM_Prescaler         71
//#define            GENERAL_TIM_IRQ               TIM3_IRQn
//#define            GENERAL_TIM_IRQHandler        TIM3_IRQHandler

#elif   GENERAL_TIM4
#define            GENERAL_TIM                   TIM4
#define            GENERAL_TIM_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            GENERAL_TIM_CLK               RCC_APB1Periph_TIM4
#define            GENERAL_TIM_Period            (1000-1)
#define            GENERAL_TIM_Prescaler         71
#define            GENERAL_TIM_IRQ               TIM4_IRQn
#define            GENERAL_TIM_IRQHandler        TIM4_IRQHandler

#elif   GENERAL_TIM5
#define            GENERAL_TIM                   TIM5
#define            GENERAL_TIM_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            GENERAL_TIM_CLK               RCC_APB1Periph_TIM5
#define            GENERAL_TIM_Period            (1000-1)
#define            GENERAL_TIM_Prescaler         71
#define            GENERAL_TIM_IRQ               TIM5_IRQn
#define            GENERAL_TIM_IRQHandler        TIM5_IRQHandler

#endif


 void General_TIM2_Init(void);
 void General_TIM3_Init(void);




#endif







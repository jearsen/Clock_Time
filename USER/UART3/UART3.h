#ifndef __UART3_H__
#define __UART3_H__


#include "stm32f10x.h"
#include <stdio.h>
#include <stdarg.h>
#include "zigbee.h"



//// 串口1-USART1
//#define  DEBUG_USARTx                   USART1
//#define  DEBUG_USART_CLK                RCC_APB2Periph_USART1
//#define  DEBUG_USART_APBxClkCmd         RCC_APB2PeriphClockCmd
//#define  DEBUG_USART_BAUDRATE           115200

//// USART GPIO 引脚宏定义
//#define  DEBUG_USART_GPIO_CLK           (RCC_APB2Periph_GPIOA)
//#define  DEBUG_USART_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
//    
//#define  DEBUG_USART_TX_GPIO_PORT         GPIOA   
//#define  DEBUG_USART_TX_GPIO_PIN          GPIO_Pin_9
//#define  DEBUG_USART_RX_GPIO_PORT         GPIOA
//#define  DEBUG_USART_RX_GPIO_PIN          GPIO_Pin_10

//#define  DEBUG_USART_IRQ                USART1_IRQn
//#define  DEBUG_USART_IRQHandler         USART1_IRQHandler


// //串口2-USART2
//#define  DEBUG_USART2                   USART2
//#define  DEBUG_USART2_CLK                RCC_APB1Periph_USART2
//#define  DEBUG_USART2_APBxClkCmd         RCC_APB1PeriphClockCmd
//#define  DEBUG_USART2_BAUDRATE           115200

//// USART GPIO 引脚宏定义
//#define  DEBUG_USART2_GPIO_CLK           (RCC_APB2Periph_GPIOA)
//#define  DEBUG_USART2_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
//    
//#define  DEBUG_USART2_TX_GPIO_PORT         GPIOA   
//#define  DEBUG_USART2_TX_GPIO_PIN          GPIO_Pin_2
//#define  DEBUG_USART2_RX_GPIO_PORT       GPIOA
//#define  DEBUG_USART2_RX_GPIO_PIN        GPIO_Pin_3

//#define  DEBUG_USART2_IRQ                USART2_IRQn
//#define  DEBUG_USART2_IRQHandler         USART2_IRQHandler

 //串口3-USART3
#define  DEBUG_USART3                    USART3
#define  DEBUG_USART3_CLK                RCC_APB1Periph_USART3
#define  DEBUG_USART3_APBxClkCmd         RCC_APB1PeriphClockCmd
#define  DEBUG_USART3_BAUDRATE           115200

// USART GPIO 引脚宏定义
#define  DEBUG_USART3_GPIO_CLK           (RCC_APB2Periph_GPIOB)
#define  DEBUG_USART3_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
    
#define  DEBUG_USART3_TX_GPIO_PORT         GPIOB   
#define  DEBUG_USART3_TX_GPIO_PIN          GPIO_Pin_10
#define  DEBUG_USART3_RX_GPIO_PORT       GPIOB
#define  DEBUG_USART3_RX_GPIO_PIN        GPIO_Pin_11

#define  DEBUG_USART3_IRQ                USART3_IRQn
#define  DEBUG_USART3_IRQHandler         USART3_IRQHandler

// 串口4-UART4
//#define  DEBUG_USARTx                   UART4
//#define  DEBUG_USART_CLK                RCC_APB1Periph_UART4
//#define  DEBUG_USART_APBxClkCmd         RCC_APB1PeriphClockCmd
//#define  DEBUG_USART_BAUDRATE           115200

//// USART GPIO 引脚宏定义
//#define  DEBUG_USART_GPIO_CLK           (RCC_APB2Periph_GPIOC)
//#define  DEBUG_USART_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
//    
//#define  DEBUG_USART_TX_GPIO_PORT         GPIOC   
//#define  DEBUG_USART_TX_GPIO_PIN          GPIO_Pin_10
//#define  DEBUG_USART_RX_GPIO_PORT       GPIOC
//#define  DEBUG_USART_RX_GPIO_PIN        GPIO_Pin_11

//#define  DEBUG_USART_IRQ                UART4_IRQn
//#define  DEBUG_USART_IRQHandler         UART4_IRQHandler


// 串口5-UART5
//#define  DEBUG_USARTx                   UART5
//#define  DEBUG_USART_CLK                RCC_APB1Periph_UART5
//#define  DEBUG_USART_APBxClkCmd         RCC_APB1PeriphClockCmd
//#define  DEBUG_USART_BAUDRATE           115200

//// USART GPIO 引脚宏定义
//#define  DEBUG_USART_GPIO_CLK           (RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD)
//#define  DEBUG_USART_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
//    
//#define  DEBUG_USART_TX_GPIO_PORT         GPIOC   
//#define  DEBUG_USART_TX_GPIO_PIN          GPIO_Pin_12
//#define  DEBUG_USART_RX_GPIO_PORT       GPIOD
//#define  DEBUG_USART_RX_GPIO_PIN        GPIO_Pin_2

//#define  DEBUG_USART_IRQ                UART5_IRQn
//#define  DEBUG_USART_IRQHandler         UART5_IRQHandler



extern  unsigned char    TxBuffer3[13];
extern u8 RxBuffer3[11];
extern uint8_t rec_flag3;
extern uint8_t tx_fla3;

void USART3_Configuration(void);
void DEBUG_USART3_IRQHandler(void);
void Usart3_SendByte( USART_TypeDef * pUSARTx, uint8_t ch);
void Usart3_SendString( USART_TypeDef * pUSARTx, char *str);
void Usart3_Show_Message(void);
void Usart3_SendArray( USART_TypeDef * pUSARTx, uint8_t *array, uint16_t num);
void USART3_Send_Len_Str(u8 *str, u8 len);
void USART3_printf ( USART_TypeDef * USARTx, char * Data, ... );

























#endif













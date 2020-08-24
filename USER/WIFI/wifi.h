#ifndef __WIFI_H__
#define __WIFI_H__


#include "stm32f10x.h"
#include "stdbool.h"
#include "UART.h"
#include "SYSTICK.h"
#include "string.h"
#include "Work_LED.h"
#include "UART_Screen.h"



//--ָ��ͷ
#define open_cpu  						 0xAF
#define cpu_openstatse				 0xAE




//--ָ���
#define command_length				  10

#define Send_command_length			14

//--ָ��ͷ��ʼλ��
#define cmdhead_startposit	  	0
//--ָ��ͷ����
#define cmdheader_length			  2

//--�����ַ����
#define mainbox_addresslength		2	
//--�����ַ��ʼλ��
#define mainbox_startposit			2	

//--����ָ���
#define WR_command_length				 10

#define MAX_RCV_LEN 50

//���ӱ��
#define master_addr     0x0000     //����
#define curtain_addr    0x0001     //����
#define AC_addr         0x0002     //�յ�
#define prj_addr        0x0003     //ͶӰ
#define mb_addr         0x0004     //Ļ��


//�ӻ�����ָ��
#define slavecmd_open		0x01 
#define slavecmd_close		0x00 


typedef enum{
	Multiple_ID_0 = 0,
	Multiple_ID_1 = 1,
	Multiple_ID_2 = 2,
	Multiple_ID_3 = 3,
	Multiple_ID_4 = 4,
	Single_ID_0 = 5,
} ENUM_ID_NO_TypeDef;
	


extern u32 UART1_read_count;
extern u8 UART1_rcv_buf[MAX_RCV_LEN] ;
extern unsigned char sencmd_temp[8];

void ESP8266_UnvarnishSend(void);
void TCP_SEVER_SendString(u32 ulStrLength,ENUM_ID_NO_TypeDef ucId);
void Buffercls(unsigned char *pBuffer, unsigned char vlaue, unsigned int BufferLength);
bool USRT_Send_ATCmd(unsigned char *cmd,unsigned char *result);
void USART1_Clear_Buf(void);
bool USRT_Send_ATCmd2(unsigned char *result);
void Esp8266_Server_Init(void);
void ESP8266_Client_Init(void);
void ESP8266_IntGenData(unsigned char rec_tem);
unsigned char Convert_Verification(unsigned char *pBuffer2, unsigned int BufferLength);
void  parse_command(void);
bool USRT_Send_ATCmd3(unsigned char *cmd,unsigned char *result);
void TCP_SEVER_Instruction(unsigned char addr,unsigned char zcmd);
void Buffercpy(unsigned char *dBuffer, unsigned char *sBuffer, unsigned int BufferLength);
#endif



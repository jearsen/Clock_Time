#ifndef __ZIGBEE_H__
#define __ZIGBEE_H__



#include "stm32f10x.h"
#include "UART3.h"
#include "UART_Screen.h"
#include "wifi.h"



////--ָ��ͷ
//#define open_cpu  						 0xAF
//#define cpu_openstatse				 0xAE

//--ָ��ͷ����
#define cmdheader_length			  2

////--�����ַ��ʼλ��
//#define mainbox_startposit			2	

//--����ָ���
#define ZS_command_length				11

//--����ָ���
#define ZR_command_length				 7


//���ӱ��
#define master_addr     0x0000     //����
#define curtain_addr    0x0001     //����
#define AC_addr         0x0002     //�յ�
#define prj_addr        0x0003     //ͶӰ
#define mb_addr         0x0004     //Ļ��

//�ӻ�����ָ��
#define slavecmd_open		0x01 
#define slavecmd_close		0x00 


void Buffercpy(unsigned char *dBuffer, unsigned char *sBuffer, unsigned int BufferLength);
void Zigbee_Send_instruction(unsigned char zcmdh,unsigned char addr);
unsigned char Convert_Verification(unsigned char *pBuffer2, unsigned int BufferLength);
void Zigbee_IntGenData(unsigned char rec_tem);































#endif





















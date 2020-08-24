#ifndef __ZIGBEE_H__
#define __ZIGBEE_H__



#include "stm32f10x.h"
#include "UART3.h"
#include "UART_Screen.h"
#include "wifi.h"



////--指令头
//#define open_cpu  						 0xAF
//#define cpu_openstatse				 0xAE

//--指令头长度
#define cmdheader_length			  2

////--主箱地址起始位置
//#define mainbox_startposit			2	

//--发送指令长度
#define ZS_command_length				11

//--接收指令长度
#define ZR_command_length				 7


//机子编号
#define master_addr     0x0000     //主机
#define curtain_addr    0x0001     //窗帘
#define AC_addr         0x0002     //空调
#define prj_addr        0x0003     //投影
#define mb_addr         0x0004     //幕布

//从机控制指令
#define slavecmd_open		0x01 
#define slavecmd_close		0x00 


void Buffercpy(unsigned char *dBuffer, unsigned char *sBuffer, unsigned int BufferLength);
void Zigbee_Send_instruction(unsigned char zcmdh,unsigned char addr);
unsigned char Convert_Verification(unsigned char *pBuffer2, unsigned int BufferLength);
void Zigbee_IntGenData(unsigned char rec_tem);































#endif





















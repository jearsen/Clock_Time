#include "zigbee.h"

//--指令
unsigned char cmd_open_cpu[2] 		     = {0xAF,0x5F};  
unsigned char cmd_cpu_openstatse[2]    = {0xAE,0x5E};

 //  发送指令给从机 并封装指令  指令头  地址  状态
  void Zigbee_Send_instruction(unsigned char zcmdh,unsigned char addr)
	{
		if(zcmdh == open_cpu) //判断是查询指令还是命令指令
		{
			Buffercpy(TxBuffer3,cmd_open_cpu,cmdheader_length);
		}
		else if(zcmdh == cpu_openstatse)
		{
			Buffercpy(TxBuffer3,cmd_cpu_openstatse,cmdheader_length);
		}
		TxBuffer3[mainbox_startposit] = addr>>8;
		TxBuffer3[mainbox_startposit+1] = addr;
		TxBuffer3[4] = Set_Danger_Tance>>8;
		TxBuffer3[5] = Set_Danger_Tance;
		TxBuffer3[6] = Set_Keep_Tance>>8;
		TxBuffer3[7] = Set_Keep_Tance;
		TxBuffer3[8] = Set_Safe_Tance>>8;
		TxBuffer3[9] = Set_Safe_Tance;
		TxBuffer3[ZS_command_length-1] = Convert_Verification(TxBuffer3,ZS_command_length-1);
		USART3_Send_Len_Str(TxBuffer3,ZS_command_length);
	}		

	
	   

//--把一个数组的内容复制到另一个数组
void Buffercpy(unsigned char *dBuffer, unsigned char *sBuffer, unsigned int BufferLength)
{
  while(BufferLength--)
  {
   *dBuffer = *sBuffer;
		
    dBuffer++;
		sBuffer++;
  }
}

   //--计算校验值
unsigned char Convert_Verification(unsigned char *pBuffer2, unsigned int BufferLength)
{
//	unsigned int sum = 0;
	unsigned char i ,temp = 0;
	for(i=0; i<BufferLength; i++)
		{
			temp += pBuffer2[i];
		}
	return temp;
}

void Zigbee_IntGenData(unsigned char rec_tem)
{
	
	static unsigned char rec_count = 0;//--接收计数
		static unsigned char start_rec = 0;//--贞开始
	
		if(rec_tem == open_cpu||rec_tem == cpu_openstatse)
		{	
			rec_count = 0;
			start_rec = 1;
		}
		if(start_rec == 1)
		{ 
			RxBuffer3[rec_count++] = rec_tem;
	    
			if(rec_count == 7)
			{
				start_rec = 0;
				rec_flag3 = 1;
				
			}
		}
}



































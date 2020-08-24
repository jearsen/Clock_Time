#include "Parse_command.h"

u16 Tance = 0;
u16 CO_Temp = 0;
	
   /*解析主句指令数据包*/
  void Analyze_instruction(u8 *RecBuf, u16 Reclen)
			{

				u8 RecT[MAX_RCV_ESP8266_LEN] = {0};          
				u16 RecL = 0;                         // 长度变量
				if(rec_flag == 1)
				{	
						if(*RecBuf == open_cpu || *RecBuf == cpu_openstatse)    //解析控制指令头
						{
							RecL = *(RecBuf+1);
							Buffercpy(RecT,RecBuf,RecL);
//							USART2_Send_Len_Str(RecT,RecL);
							if(RecT[RecL -1] == ESP8266_Check_Num(RecT,RecL))
							{	
								switch(RecT[0])
								{  
									case open_cpu:Esp8266_Analyze_Saddr(((RecT[2]<<8) | RecT[3]),RecT[6],((RecT[4]<<8) | RecT[5]));
										break;
									case cpu_openstatse:
										break;
								  default:
										break;
								}
							}	
		Buffercls(RxBuffer1, 0, WR_command_length);
		rec_flag = 0;
	
				}
			}
    else if(rec_flag3 == 1)
		{ 
			if(Convert_Verification(RxBuffer3,ZR_command_length-1) == RxBuffer3[ZR_command_length-1])
			{
				switch(RxBuffer3[cmdhead_startposit])
				{
					case open_cpu:
						switch(RxBuffer3[2]<<8 | RxBuffer3[3])
						{
							case master_addr:
								break;
							case curtain_addr:
//							Beep_On_Off;
						  Tance = RxBuffer3[4]<<8 | RxBuffer3[5];
//							printf("%d\r\n",Tance);
								break;
						}
						break;
					case cpu_openstatse:
						break;
					default:
						break;
					
				}
				
			}
	  Buffercls(RxBuffer3, 0, ZR_command_length);
		rec_flag3 = 0;
		  }
			}
			 /*计算校验值*/
			 u8 ESP8266_Check_Num(u8 *Buf, u8 Len)
			{
				u8 i = 0;
				u8 Check_SumT = 0;
				for(i=0;i<Len-1;i++)
				Check_SumT += *(Buf+i);
				return Check_SumT;
			}

      /*解析地址和控制指令*/
 void Esp8266_Analyze_Saddr(unsigned int Saddr, unsigned char zcmd,u16 CO_Value)
		{
			
			switch(Saddr)
			{
				case master_addr:
					if(zcmd==slavecmd_open)
				 {
					
				 }
				 else if(zcmd==slavecmd_close)
				 {
					
				 }
					break;
				case curtain_addr:
		     CO_Temp = CO_Value;
					if(zcmd==slavecmd_open)
				 {
					 Led1_On_Off;
				
				 }
				 else if(zcmd==slavecmd_close)
				 {
					
				 }
					break;
				
				case AC_addr:
					break;
				case prj_addr:
					break;
				 default:
					break;
			}

		}

   
			
			


		













#include "wifi.h"

u32 UART1_read_count = 0;//�������ݵĸ���
u8 UART1_rcv_buf[MAX_RCV_LEN] = {0};





// ���õ�����
// ����+ok
uc8 *SetCIPMUX = "AT+CIPMUX=0\r\n";

// ����͸��ģʽ
// ����+ok
uc8	*SetCIPMODE = "AT+CIPMODE=1\r\n";
// ����STATIONģʽ
// ����+ok
uc8 *SetCWMODE = "AT+CWMODE=1\r\n";

//���������ȵ�
//����+ok
uc8 *AddCWJAP = "AT+CWJAP=\"ESP8266\",\"0123456789\"\r\n";

// ����TCP���Ӳ���
// ����+ok
uc8 *SetNETP = "AT+CIPSTART=\"0\",\"TCP\",\"192.168.4.1\",8888\r\n";



  /*���ó�TCP�ͻ���ģʽ*/
  void ESP8266_Client_Init()
	{
		
		USRT_Send_ATCmd2("Ready");                //��ѯ
		USRT_Send_ATCmd("AT\r\n","OK");           //����
		USRT_Send_ATCmd("AT+CIPMUX=0\r\n","OK") ;  //���õ�����
    USRT_Send_ATCmd("AT+CWMODE=1\r\n","OK")  ; //����STATIONģʽ  �״��趨����Ͳ���������
		USRT_Send_ATCmd3((char*)AddCWJAP,"OK");   ////���������ȵ�
		USRT_Send_ATCmd3((char*)SetNETP,"OK");   //����TCP���Ӳ���
	}		
  
	/*���ó�TCP����ģʽ*/ 
  void Esp8266_Server_Init()  //��ʼ��  ���ó�TCP����ģʽ
	{
		 //�ȴ������ɹ� ��������  �յ�����
	   USRT_Send_ATCmd2("Ready");           //��ѯ
	   USRT_Send_ATCmd("AT\r\n","OK");      //����
		 USRT_Send_ATCmd("AT+CIPMUX=1\r\n","OK");    //���ö�����ģʽ
		 USRT_Send_ATCmd("AT+CWMODE=3\r\n","OK")  ; //����STATIONģʽ (AP+STATION)ģʽ �״��趨����Ͳ���������
		 USRT_Send_ATCmd("AT+CIPSERVER=1,8888\r\n","OK");//����TCP����ģʽ	
				
	}
	   /*͸������ģʽ(ֻ�޴ӻ�������������)*/
		void ESP8266_UnvarnishSend()
		{
			
//		unsigned char *str;
			unsigned char *sendtemp = "AT+CIPSEND\r\n";
      USRT_Send_ATCmd((char*)SetCIPMODE,"OK");   //����͸��ģʽ
			USRT_Send_ATCmd3(sendtemp,">");
		  TCP_SEVER_Instruction(curtain_addr,slavecmd_open);

			
		}
		
		/*�������ӻ���ָ��*/
    void TCP_SEVER_SendString(u32 ulStrLength,ENUM_ID_NO_TypeDef ucId)
		{
			   unsigned char Send_Data[9] = {0};
				 unsigned char cStr[100]; 
			if(ucId < 5)
		sprintf ( cStr, "AT+CIPSEND=%d,%d\r\n", ucId, ulStrLength + 2 );  //������ģʽ
		else
		sprintf ( cStr, "AT+CIPSEND=%d\r\n",ulStrLength + 2 ); 		        //������ģʽ
		USRT_Send_ATCmd3(cStr,">");
		TCP_SEVER_Instruction(curtain_addr,slavecmd_open);
//		sprintf ( cStr, "Read DHT11 ERROR!\r\n" );
//		
//		 printf ( "%s", cStr );  
	USRT_Send_ATCmd2("SEND OK"); 
	
	}

	    /*����ָ���*/
	 void TCP_SEVER_Instruction(unsigned char addr,unsigned char zcmd)
	 {
	  u8 i =0;
	  u8 sencmd_temp[Send_command_length] = {0};
		u8 sencmd_Sum = 0;
		sencmd_temp[0] = open_cpu; //����ͷ
		
		sencmd_temp[1] = Send_command_length;       // ���ݳ���
		
		sencmd_temp[2] = addr>>8;
		sencmd_temp[3] = addr;
		
		sencmd_temp[4] = Set_Safe_CO>>8;
		sencmd_temp[5] = Set_Safe_CO;
		sencmd_temp[6] = Set_Keep_CO>>8;
		sencmd_temp[7] = Set_Keep_CO;
		sencmd_temp[8] = Set_Danger_CO>>8;
		sencmd_temp[9] = Set_Danger_CO;
		
		sencmd_temp[10] = zcmd;     //����ָ�� 
		
		sencmd_temp[11] = 1;        //ȷ����
		sencmd_temp[12] = 1;        //У����
    
		for(i=0;i<Send_command_length;i++)
		sencmd_Sum += sencmd_temp[i];
		sencmd_temp[13] = sencmd_Sum;
		
		USART1_Send_Len_Str(sencmd_temp,Send_command_length);

	 }
	
	 
	 
	 
	   
bool USRT_Send_ATCmd(unsigned char *cmd,unsigned char *result)
{
	unsigned char i = 0;
	unsigned char ret = 0;
	while(1)
	{	
  USART1_Clear_Buf();
	USART1_Send_Len_Str(cmd,strlen(cmd));
	delay_ms(100);
	if(NULL != strstr(UART1_rcv_buf,result))
	{
		ret = SUCCESS;
		break;
	}
	else if(i++ >=10)
	{
		ret = ERROR;
		break;
	}
}
	return ret;
}

  bool USRT_Send_ATCmd2(unsigned char *result)
	{
		unsigned char i = 0;
		unsigned char ret = 0;
		while(1)
		{
		USART1_Clear_Buf();
		delay_ms(100);
		if(NULL != strstr(UART1_rcv_buf,result))
		{

			ret = SUCCESS;
		  break; 
		}
		else if(i++ >=10)
		{
			Beep_Off;
			ret = ERROR;
		  break;
		}
	}
		return ret;
	}

bool USRT_Send_ATCmd3(unsigned char *cmd,unsigned char *result)
{
	unsigned char i = 0;
	unsigned char ret = 0;
	while(1)
	{	
  USART1_Clear_Buf();
//	ESP8266_Usart("%s",cmd);
  USART1_Send_Len_Str(cmd,strlen(cmd));
	delay_ms(2000);
	if(NULL != strstr(UART1_rcv_buf,result))
	{
	
		ret = SUCCESS;

		break;
	}
	else if(i++ >=10)
	{
		ret = ERROR;
		break;
	}
}
	return ret;
}


void USART1_Clear_Buf(void)
{
	memset(UART1_rcv_buf, 0, strlen(UART1_rcv_buf));
  UART1_read_count = 0;
}

//--��ĳ����������
void Buffercls(unsigned char *pBuffer, unsigned char vlaue, unsigned int BufferLength)
{
  while(BufferLength--)
  {
   *pBuffer = vlaue;
		
    pBuffer++;
  }
}


 
  void ESP8266_IntGenData(unsigned char rec_tem)
	{
		static unsigned char rec_count = 0;//--���ռ���
		static unsigned char start_rec = 0;//--�꿪ʼ
	
		if(rec_tem == open_cpu||rec_tem == cpu_openstatse)
		{	
			rec_count = 0;
			start_rec = 1;
		}
		if(start_rec == 1)
		{ 
			RxBuffer1[rec_count++] = rec_tem;
	    
			if(rec_count == command_length)
			{
				start_rec = 0;
				rec_flag = 1;
				
			}
		}
	}
	
	 
	
	

  









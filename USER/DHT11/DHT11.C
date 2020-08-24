#include "DHT11.h"
/*

  DHT11���л���  
	������18ms�͵�ƽ
	�ڷ����źŽ�������ʱ�ȴ�20-40us
	��DHT11����80us�͵�ƽ��Ӧ�ź�
	��DHT11�ڰ���������80us
	�ݽ�������
	��������������
	
*/

/*
   ����DHT11�õ���IO��
	 ���ģʽΪ�������
*/


unsigned char humidity_int;     //ʪ�ȵ���������
unsigned char humidity_deci;    //ʪ�ȵ�С������
unsigned char temperature_int;	//�¶ȵ���������
unsigned char temperature_deci; //�¶ȵ�С������
	 
 
void DHT11_Init()
{
	DHT11_GPIO_Confing();
	DHT11_H;
	
}
 void DHT11_GPIO_Confing(void)       
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	DHT11_GPIO_APBxClkCmd(DHT11_GPIO_CLK,ENABLE);
	GPIO_InitStructure.GPIO_Pin = DHT11_GPIO_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(DHT11_GPIO_PROT,&GPIO_InitStructure);
}

/*ʹDHT11�����ű�Ϊ��������*/
 static void DHT11_GPIO_Mode_IPU(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = DHT11_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(DHT11_GPIO_PROT,&GPIO_InitStructure);
}


  static void DHT11_GPIO_Mode_Out_PP(void)
	{
  GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = DHT11_GPIO_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(DHT11_GPIO_PROT,&GPIO_InitStructure);
	}
	
	void DHT11_State(void)
	{
		DHT11_GPIO_Mode_Out_PP();  //����Ϊ���ģʽ
		DHT11_L;
		delay_ms(18);
		DHT11_H;
		delay_us(30);
		DHT11_GPIO_Mode_IPU();
	}
	
//��DHT11��ȡһ���ֽڣ�MSB����(�����Чλ  �������д������ֵ��bit)
    unsigned char Read_Byte(void)
		{
			unsigned char i,temp=0;
			for(i=0;i<8;i++)
			{
				while( DHT11_IN==Bit_RESET);
				delay_us(40);
				if( DHT11_IN==Bit_SET)
				{
					while( DHT11_IN==Bit_SET);
					temp|=(uint8_t)(0x01<<(7-i)); //λ��ֵ �Ѱѵ�7-iλ��1
				}
				else 
				{
					temp&=(uint8_t)~(0x01<<(7-i)); //�ѵ�7-iλ��0
				}
			}
			return temp;
		}
     
		
		unsigned char DHT11_Read_TempAndHumidity()
		{
			unsigned char rec_temp[5];
			unsigned char i;
			
			DHT11_State();               //��ʼ�ź�
			if(DHT11_IN==Bit_RESET)      //�ж�DHT11��Ӧ�ź�
			{
				while(DHT11_IN==Bit_RESET);//��ѯ80us�͵�ƽ�źŽ���
				
				while(DHT11_IN==Bit_SET);  //��ѯ80us�ߵ�ƽ�źŽ���
				for(i=0;i<5;i++)
				{
					rec_temp[i]= Read_Byte();
				}
			DHT11_GPIO_Mode_Out_PP();    //��ȡ���� ���Ÿ�Ϊ���ģʽ
      DHT11_H;                     //��������
				if((rec_temp[0]+rec_temp[1]+rec_temp[2]+rec_temp[3])==rec_temp[4])//У��
				{
					  humidity_int = rec_temp[0];
						humidity_deci = rec_temp[1];
						temperature_int = rec_temp[2];
						temperature_deci = rec_temp[3];
//					Led1_On;
					return SUCCESS;
				}
			else 
			{
					return ERROR;
			}
			}
			else 
			{
					return ERROR;
			}
			
		}
		
		
		
		


























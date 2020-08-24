#include "DHT11.h"
/*

  DHT11运行机制  
	①拉低18ms低电平
	②发送信号结束后延时等待20-40us
	③DHT11发送80us低电平响应信号
	④DHT11在把总线拉高80us
	⑤接收数据
	⑥主机总线拉高
	
*/

/*
   配置DHT11用到的IO口
	 输出模式为推挽输出
*/


unsigned char humidity_int;     //湿度的整数部分
unsigned char humidity_deci;    //湿度的小数部分
unsigned char temperature_int;	//温度的整数部分
unsigned char temperature_deci; //温度的小数部分
	 
 
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

/*使DHT11的引脚变为上拉输入*/
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
		DHT11_GPIO_Mode_Out_PP();  //设置为输出模式
		DHT11_L;
		delay_ms(18);
		DHT11_H;
		delay_us(30);
		DHT11_GPIO_Mode_IPU();
	}
	
//从DHT11读取一个字节，MSB先行(最高有效位  二进制中代表最高值的bit)
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
					temp|=(uint8_t)(0x01<<(7-i)); //位或赋值 把把第7-i位置1
				}
				else 
				{
					temp&=(uint8_t)~(0x01<<(7-i)); //把第7-i位置0
				}
			}
			return temp;
		}
     
		
		unsigned char DHT11_Read_TempAndHumidity()
		{
			unsigned char rec_temp[5];
			unsigned char i;
			
			DHT11_State();               //开始信号
			if(DHT11_IN==Bit_RESET)      //判断DHT11响应信号
			{
				while(DHT11_IN==Bit_RESET);//轮询80us低电平信号结束
				
				while(DHT11_IN==Bit_SET);  //轮询80us高电平信号结束
				for(i=0;i<5;i++)
				{
					rec_temp[i]= Read_Byte();
				}
			DHT11_GPIO_Mode_Out_PP();    //读取结束 引脚改为输出模式
      DHT11_H;                     //主机拉高
				if((rec_temp[0]+rec_temp[1]+rec_temp[2]+rec_temp[3])==rec_temp[4])//校验
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
		
		
		
		



























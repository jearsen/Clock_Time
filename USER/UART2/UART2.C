#include "UART2.h"


////加入以下代码,支持printf函数,而不需要选择use MicroLIB	      
//#if 1
//#pragma   import(__use_no_semihosting)  
////标准库需要的支持函数  
//struct __FILE 
//{ 
//	int handle; 

//}; 

//FILE __stdout;       
////定义_sys_exit()以避免使用半主机模式    
//_sys_exit(int x) 
//{ 
//	x = x; 
//} 
////重定义fputc函数 
//int fputc(int ch, FILE *f)
//{      
//	while((DEBUG_USART2->SR&0X40)==0);//循环发送,直到发送完毕   
//    DEBUG_USART2->DR = (u8) ch;      
//	return ch;
//}
//#endif
///*使用microLib的方法*/
// /* 
//int fputc(int ch, FILE *f)
//{
//	USART_SendData(USART1, (uint8_t) ch);

//	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {}	
//   
//    return ch;
//}
//int GetKey (void)  { 

//    while (!(USART1->SR & USART_FLAG_RXNE));

//    return ((int)(USART1->DR & 0x1FF));
//}
//*/


unsigned char  TxBuffer2[11];    //发送数据缓存区
uint8_t RxBuffer2[19] = {0};    //接收数据缓存区
uint8_t rec_flag2 = 0;
uint8_t tx_flag2 = 0;
uint8_t TxCounter2 = 0;
uint8_t RxCounter2 = 0; 
   void USART2_NVIC_Configuration()
	 {
		 NVIC_InitTypeDef NVIC_InitStructure;
		 	/*配置NVIC中断优先级组*/
		 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
		 /* 配置USART为中断源 */
		 NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART2_IRQ;
		  /* 抢断优先级*/
		 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		 /* 子优先级 */
		 NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;
		  /* 使能中断 */
		 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		  /* 初始化配置NVIC */
     NVIC_Init(&NVIC_InitStructure);
	 }
   void USART2_RCC_Init()
	 {
		 DEBUG_USART2_APBxClkCmd(DEBUG_USART2_CLK,ENABLE);
		 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE);
	 }
   void USART2_GPIO_Configuration()
	 {
		 
				GPIO_InitTypeDef GPIO_InitStructure;
				// 将USART Tx的GPIO配置为推挽复用模式
				GPIO_InitStructure.GPIO_Pin = DEBUG_USART2_TX_GPIO_PIN;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
				GPIO_Init(DEBUG_USART2_TX_GPIO_PORT, &GPIO_InitStructure); 
				// 将USART Rx的GPIO配置为复用开漏模式
				GPIO_InitStructure.GPIO_Pin = DEBUG_USART2_RX_GPIO_PIN;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
				GPIO_Init(DEBUG_USART2_RX_GPIO_PORT, &GPIO_InitStructure);	 
	 }
	 
	   void USART2_Configuration(void)
		 {
			 USART_InitTypeDef USART_InitStructure;
			 USART2_RCC_Init();
			 USART2_GPIO_Configuration();
			 USART2_NVIC_Configuration();
			    //初始化参数设置 
			 USART_InitStructure.USART_BaudRate = 115200;  //波特率9600
			 USART_InitStructure.USART_WordLength = USART_WordLength_8b;  //字长8位
			 USART_InitStructure.USART_StopBits = USART_StopBits_1;     //1位停止字节、
			 USART_InitStructure.USART_Parity = USART_Parity_No;   //无奇偶校验
			 USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无流控制
			 USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//打开RX接收和TX	发送功能  收发一起
			 USART_Init(DEBUG_USART2, &USART_InitStructure);  
			 // 使能串口接收中断	
       //USART_ClearFlag(USART2,USART_FLAG_TC);  
			 USART_ITConfig(DEBUG_USART2,USART_IT_RXNE,ENABLE);//开启接收中断
//			 USART_ITConfig(DEBUG_USARTx,USART_IT_TXE,ENABLE);//开启发中断
			 // 使能串口
			 USART_Cmd(DEBUG_USART2,ENABLE);
		 }
		 
		 
		 
		 //中断函数用于接收数据并判断数据的头尾
//		 void DEBUG_USART_IRQHandler(void)      //串口2 中断服务程序  //接收中断
//{
//  unsigned int i;
//		if(USART_GetFlagStatus(DEBUG_USARTx,USART_FLAG_ORE)==SET)//溢出
//		{
//			USART_ReceiveData(DEBUG_USARTx);                      //读DR
//			USART_ClearFlag(DEBUG_USARTx,USART_FLAG_ORE);        //读SR
//		}
//  if(USART_GetITStatus(DEBUG_USARTx, USART_IT_RXNE) != RESET)	   //判断读寄存器是否非空  接收中断
//  {	
//    
//    RxBuffer1[RxCounter1++] = USART_ReceiveData(DEBUG_USARTx);             //将读寄存器的数据缓存到接收缓冲区里  读取接收到的数据
//	  for(i=0; i< RxCounter1; i++) TxBuffer1[i]	= RxBuffer1[i]; 	     //将接收缓冲器的数据转到发送缓冲区，准备转发
//	  rec_f=1;															                           //接收成功标志
//	  TxBuffer1[RxCounter1]=0;		                                     //发送缓冲区结束符    
//	  RxCounter1=0;
//	
//  }
//  
//  if(USART_GetITStatus(DEBUG_USARTx, USART_IT_TXE) != RESET)                   //这段是为了避免STM32 USART 第一个字节发不出去的BUG 
//  { 
//     USART_ITConfig(DEBUG_USARTx, USART_IT_TXE, DISABLE);					            //禁止发缓冲器空中断， 
//  }	
//}

   void DEBUG_USART2_IRQHandler(void) 
	 {
		   unsigned char rec_tem = 0;   //--接收缓存

		  if(USART_GetITStatus(DEBUG_USART2, USART_IT_RXNE) != RESET)	 //判断读寄存器是否非空   接受中断
			{	
				rec_tem = USART_ReceiveData(DEBUG_USART2);    //将读寄存器的数据缓存到接收缓冲区里  
        Screen_Get_FData(rec_tem);
				Screen_Get_NData(rec_tem);
/
				
		USART_ClearITPendingBit(DEBUG_USART2,USART_IT_RXNE);
	 }
 }

void Usart2_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
{
	/* 发送一个字节数据到USART */
	USART_SendData(pUSARTx,ch);
		
	/* 等待发送数据寄存器为空 */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}
		
	void Usart2_SendString( USART_TypeDef * pUSARTx, char *str)
{
	unsigned int k=0;
  do 
  {
      Usart2_SendByte( pUSARTx, *(str + k) );
      k++;
  } while(*(str + k)!='\0');
  
	
	
	
  /* 等待发送完成 */
  while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET)
  {}
}	
/****************** 发送8位的数组 ************************/
void Usart2_SendArray( USART_TypeDef * pUSARTx, uint8_t *array, uint16_t num)
{
  uint8_t i;
	
	for(i=0; i<num; i++)
  {
	    /* 发送一个字节数据到USART */
	    Usart2_SendByte(pUSARTx,array[i]);	
  
  }
	/* 等待发送完成 */
	while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET);
}


void USART2_Send_Len_Str(u8 *str, u8 len)
{
	u8 i;

	for(i=0; i<len; i++)
		Usart2_SendByte(USART2,*str ++);
}

  /* 指令输入提示信息 */
 void Usart2_Show_Message(void)
{
	Usart2_SendString(DEBUG_USART2,"这是一个通过串口通信指令控制LED灯实验 \n");
	Usart2_SendString(DEBUG_USART2,"使用  USART  参数为：%d 8-N-1 \n");
	Usart2_SendString(DEBUG_USART2,"开发板接到指令后控制LED灯颜色，指令对应如下：\n");
	Usart2_SendString(DEBUG_USART2,"  指令   ------ LED灯号 \n");
	Usart2_SendString(DEBUG_USART2,"    1    ------    LED1 \n");
	Usart2_SendString(DEBUG_USART2,"     2    ------    BEEP \n");
  Usart2_SendString(DEBUG_USART2,"     3    ------    灭 \n");
//  printf("\r\n   这是一个通过串口通信指令控制LED灯实验 \n");
//  printf("使用  USART  参数为：%d 8-N-1 \n",USART2);
//  printf("开发板接到指令后控制LED灯颜色，指令对应如下：\n");
//  printf("   指令   ------ LED灯号 \n");
//  printf("     1    ------    LED1 \n");
//  printf("     2    ------    LED2 \n");
//  printf("     3    ------    灭 \n");  
}

/*通过串口传递数据到ESP*/


static char *    itoa           ( int value, char * string, int radix );


/*
 * 函数名：USART3_print(PB10 PB11)
 * 描述  ：格式化输出，类似于C库中的printf，但这里没有用到C库
 * 输入  ：-USARTx 串口通道，这里只用到了串口2，即USART2
 *		     -Data   要发送到串口的内容的指针
 *			   -...    其他参数
 * 输出  ：无
 * 返回  ：无 
 * 调用  ：外部调用
 *         典型应用USART2_printf( USART2, "\r\n this is a demo \r\n" );
 *            		 USART2_printf( USART2, "\r\n %d \r\n", i );
 *            		 USART2_printf( USART2, "\r\n %s \r\n", j );
 */
void USART2_printf ( USART_TypeDef * USARTx, char * Data, ... )
{
	const char *s;
	int d;   
	char buf[16];

	
	va_list ap;
	va_start(ap, Data);

	while ( * Data != 0 )     // 判断是否到达字符串结束符
	{				                          
		if ( * Data == 0x5c )  //'\'
		{									  
			switch ( *++Data )
			{
				case 'r':							          //回车符
				USART_SendData(USARTx, 0x0d);
				Data ++;
				break;

				case 'n':							          //换行符
				USART_SendData(USARTx, 0x0a);	
				Data ++;
				break;

				default:
				Data ++;
				break;
			}			 
		}
		
		else if ( * Data == '%')
		{									  //
			switch ( *++Data )
			{				
				case 's':										  //字符串
				s = va_arg(ap, const char *);
				
				for ( ; *s; s++) 
				{
					USART_SendData(USARTx,*s);
					while( USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET );
				}
				
				Data++;
				
				break;

				case 'd':			
					//十进制
				d = va_arg(ap, int);
				
				itoa(d, buf, 10);
				
				for (s = buf; *s; s++) 
				{
					USART_SendData(USARTx,*s);
					while( USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET );
				}
				
				Data++;
				
				break;
				
				default:
				Data++;
				
				break;
				
			}		 
		}
		
		else USART_SendData(USARTx, *Data++);
		
		while ( USART_GetFlagStatus ( USARTx, USART_FLAG_TXE ) == RESET );
		
	}
}


/*
 * 函数名：itoa
 * 描述  ：将整形数据转换成字符串
 * 输入  ：-radix =10 表示10进制，其他结果为0
 *         -value 要转换的整形数
 *         -buf 转换后的字符串
 *         -radix = 10
 * 输出  ：无
 * 返回  ：无
 * 调用  ：被USART2_printf()调用
 */
static char * itoa( int value, char *string, int radix )
{
	int     i, d;
	int     flag = 0;
	char    *ptr = string;

	/*适用十进制数*/
	if (radix != 10)
	{
		*ptr = 0;
		return string;
	}

	if (!value)
	{
		*ptr++ = 0x30;
		*ptr = 0;
		return string;
	}

	/* 负数加上减号 */
	if (value < 0)
	{
		*ptr++ = '-';

		/* 乘法负计算 */
		value *= -1;
		
	}

	for (i = 10000; i > 0; i /= 10)
	{
		d = value / i;

		if (d || flag)
		{
			*ptr++ = (char)(d + 0x30);
			value -= (d * i);
			flag = 1;
		}
	}

	/* 终止空字符串 */
	*ptr = 0;

	return string;

}



 





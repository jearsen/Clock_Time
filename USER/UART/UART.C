#include "UART.h"


//加入以下代码,支持printf函数,而不需要选择use MicroLIB	      
#if 1
#pragma   import(__use_no_semihosting)  
//标准库需要的支持函数  
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
_sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((DEBUG_USARTx->SR&0X40)==0);//循环发送,直到发送完毕   
    DEBUG_USARTx->DR = (u8) ch;      
	return ch;
}
#endif
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



uint8_t TxBuffer1[10] ;   //发送数据缓存区
u8 RxBuffer1[10] = {0};    //接收数据缓存区
uint8_t rec_flag = 0;
uint8_t rec_flag1 = 0;
uint8_t tx_flag = 0;
__IO uint8_t TxCounter1 = 0x00;
__IO uint8_t RxCounter1 = 0x00; 
   void USART1_NVIC_Configuration()
	 {
		 NVIC_InitTypeDef NVIC_InitStructure;
		 	/*配置NVIC中断优先级组*/
		 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
		 /* 配置USART为中断源 */
		 NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART_IRQ;
		  /* 抢断优先级*/
		 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		 /* 子优先级 */
		 NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
		  /* 使能中断 */
		 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		  /* 初始化配置NVIC */
     NVIC_Init(&NVIC_InitStructure);
	 }
   void USART1_RCC_Init()
	 {
		 DEBUG_USART_APBxClkCmd(DEBUG_USART_CLK,ENABLE);
		 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE);
	 }
   void USART1_GPIO_Configuration()
	 {
		 
				GPIO_InitTypeDef GPIO_InitStructure;
				// 将USART Tx的GPIO配置为推挽复用模式
				GPIO_InitStructure.GPIO_Pin = DEBUG_USART_TX_GPIO_PIN;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
				GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStructure); 
				// 将USART Rx的GPIO配置为复用开漏模式
				GPIO_InitStructure.GPIO_Pin = DEBUG_USART_RX_GPIO_PIN;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
				GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStructure);	 
	 }
	 
	   void USART1_Configuration()
		 {
			 USART_InitTypeDef USART_InitStructure;
			 USART1_RCC_Init();
			 USART1_GPIO_Configuration();
			 USART1_NVIC_Configuration();
			    //初始化参数设置 
			 USART_InitStructure.USART_BaudRate = 115200;  //波特率9600
			 USART_InitStructure.USART_WordLength = USART_WordLength_8b;  //字长8位
			 USART_InitStructure.USART_StopBits = USART_StopBits_1;     //1位停止字节、
			 USART_InitStructure.USART_Parity = USART_Parity_No;   //无奇偶校验
			 USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无流控制
			 USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//打开RX接收和TX	发送功能  收发一起
			 USART_Init(DEBUG_USARTx, &USART_InitStructure);  
			 // 使能串口接收中断	
       //USART_ClearFlag(USART2,USART_FLAG_TC);  
			 USART_ITConfig(DEBUG_USARTx,USART_IT_RXNE,ENABLE);//开启接收中断
//			 USART_ITConfig(DEBUG_USARTx,USART_IT_TXE,ENABLE);//开启发中断
			 // 使能串口
			 USART_Cmd(DEBUG_USARTx,ENABLE);
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

   void DEBUG_USART_IRQHandler(void) 
	 {
		   unsigned char rec_tem = 0;   //--接收缓存

		  if(USART_GetITStatus(DEBUG_USARTx, USART_IT_RXNE) != RESET)	 //判断读寄存器是否非空   接受中断
			{	

				rec_tem = USART_ReceiveData(DEBUG_USARTx);    //将读寄存器的数据缓存到接收缓冲区里  
		     ESP8266_IntGenData(rec_tem);
				USART_ClearITPendingBit(DEBUG_USARTx,USART_IT_RXNE);
		   
	 }
 }

void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
{
	/* 发送一个字节数据到USART */
	USART_SendData(pUSARTx,ch);
		
	/* 等待发送数据寄存器为空 */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}
		
	void Usart_SendString( USART_TypeDef * pUSARTx, char *str)
{
	unsigned int k=0;
  do 
  {
      Usart_SendByte( pUSARTx, *(str + k) );
      k++;
  } while(*(str + k)!='\0');
  
	
	
	
  /* 等待发送完成 */
  while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET)
  {}
}	
/****************** 发送8位的数组 ************************/
void Usart_SendArray( USART_TypeDef * pUSARTx, uint8_t *array, uint16_t num)
{
  uint8_t i;
	
	for(i=0; i<num; i++)
  {
	    /* 发送一个字节数据到USART */
	    Usart_SendByte(pUSARTx,array[i]);	
  
  }
	/* 等待发送完成 */
	while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET);
}


void USART1_Send_Len_Str(u8 *str, u8 len)
{
	u8 i;

	for(i=0; i<len; i++)
		Usart_SendByte(USART1,*str ++);
}

  /* 指令输入提示信息 */
 void Show_Message(void)
{
	Usart_SendString(DEBUG_USARTx,"这是一个通过串口通信指令控制LED灯实验 \n");
	Usart_SendString(DEBUG_USARTx,"使用  USART  参数为：%d 8-N-1 \n");
	Usart_SendString(DEBUG_USARTx,"开发板接到指令后控制LED灯颜色，指令对应如下：\n");
	Usart_SendString(DEBUG_USARTx,"  指令   ------ LED灯号 \n");
	Usart_SendString(DEBUG_USARTx,"    1    ------    LED1 \n");
	Usart_SendString(DEBUG_USARTx,"     2    ------    BEEP \n");
  Usart_SendString(DEBUG_USARTx,"     3    ------    灭 \n");
//  printf("\r\n   这是一个通过串口通信指令控制LED灯实验 \n");
//  printf("使用  USART  参数为：%d 8-N-1 \n",USART2);
//  printf("开发板接到指令后控制LED灯颜色，指令对应如下：\n");
//  printf("   指令   ------ LED灯号 \n");
//  printf("     1    ------    LED1 \n");
//  printf("     2    ------    LED2 \n");
//  printf("     3    ------    灭 \n");  
}




 





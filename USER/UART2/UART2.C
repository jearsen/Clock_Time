#include "UART2.h"


////�������´���,֧��printf����,������Ҫѡ��use MicroLIB	      
//#if 1
//#pragma   import(__use_no_semihosting)  
////��׼����Ҫ��֧�ֺ���  
//struct __FILE 
//{ 
//	int handle; 

//}; 

//FILE __stdout;       
////����_sys_exit()�Ա���ʹ�ð�����ģʽ    
//_sys_exit(int x) 
//{ 
//	x = x; 
//} 
////�ض���fputc���� 
//int fputc(int ch, FILE *f)
//{      
//	while((DEBUG_USART2->SR&0X40)==0);//ѭ������,ֱ���������   
//    DEBUG_USART2->DR = (u8) ch;      
//	return ch;
//}
//#endif
///*ʹ��microLib�ķ���*/
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


unsigned char  TxBuffer2[11];    //�������ݻ�����
uint8_t RxBuffer2[19] = {0};    //�������ݻ�����
uint8_t rec_flag2 = 0;
uint8_t tx_flag2 = 0;
uint8_t TxCounter2 = 0;
uint8_t RxCounter2 = 0; 
   void USART2_NVIC_Configuration()
	 {
		 NVIC_InitTypeDef NVIC_InitStructure;
		 	/*����NVIC�ж����ȼ���*/
		 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
		 /* ����USARTΪ�ж�Դ */
		 NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART2_IRQ;
		  /* �������ȼ�*/
		 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		 /* �����ȼ� */
		 NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;
		  /* ʹ���ж� */
		 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		  /* ��ʼ������NVIC */
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
				// ��USART Tx��GPIO����Ϊ���츴��ģʽ
				GPIO_InitStructure.GPIO_Pin = DEBUG_USART2_TX_GPIO_PIN;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
				GPIO_Init(DEBUG_USART2_TX_GPIO_PORT, &GPIO_InitStructure); 
				// ��USART Rx��GPIO����Ϊ���ÿ�©ģʽ
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
			    //��ʼ���������� 
			 USART_InitStructure.USART_BaudRate = 115200;  //������9600
			 USART_InitStructure.USART_WordLength = USART_WordLength_8b;  //�ֳ�8λ
			 USART_InitStructure.USART_StopBits = USART_StopBits_1;     //1λֹͣ�ֽڡ�
			 USART_InitStructure.USART_Parity = USART_Parity_No;   //����żУ��
			 USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��������
			 USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//��RX���պ�TX	���͹���  �շ�һ��
			 USART_Init(DEBUG_USART2, &USART_InitStructure);  
			 // ʹ�ܴ��ڽ����ж�	
       //USART_ClearFlag(USART2,USART_FLAG_TC);  
			 USART_ITConfig(DEBUG_USART2,USART_IT_RXNE,ENABLE);//���������ж�
//			 USART_ITConfig(DEBUG_USARTx,USART_IT_TXE,ENABLE);//�������ж�
			 // ʹ�ܴ���
			 USART_Cmd(DEBUG_USART2,ENABLE);
		 }
		 
		 
		 
		 //�жϺ������ڽ������ݲ��ж����ݵ�ͷβ
//		 void DEBUG_USART_IRQHandler(void)      //����2 �жϷ������  //�����ж�
//{
//  unsigned int i;
//		if(USART_GetFlagStatus(DEBUG_USARTx,USART_FLAG_ORE)==SET)//���
//		{
//			USART_ReceiveData(DEBUG_USARTx);                      //��DR
//			USART_ClearFlag(DEBUG_USARTx,USART_FLAG_ORE);        //��SR
//		}
//  if(USART_GetITStatus(DEBUG_USARTx, USART_IT_RXNE) != RESET)	   //�ж϶��Ĵ����Ƿ�ǿ�  �����ж�
//  {	
//    
//    RxBuffer1[RxCounter1++] = USART_ReceiveData(DEBUG_USARTx);             //�����Ĵ��������ݻ��浽���ջ�������  ��ȡ���յ�������
//	  for(i=0; i< RxCounter1; i++) TxBuffer1[i]	= RxBuffer1[i]; 	     //�����ջ�����������ת�����ͻ�������׼��ת��
//	  rec_f=1;															                           //���ճɹ���־
//	  TxBuffer1[RxCounter1]=0;		                                     //���ͻ�����������    
//	  RxCounter1=0;
//	
//  }
//  
//  if(USART_GetITStatus(DEBUG_USARTx, USART_IT_TXE) != RESET)                   //�����Ϊ�˱���STM32 USART ��һ���ֽڷ�����ȥ��BUG 
//  { 
//     USART_ITConfig(DEBUG_USARTx, USART_IT_TXE, DISABLE);					            //��ֹ�����������жϣ� 
//  }	
//}

   void DEBUG_USART2_IRQHandler(void) 
	 {
		   unsigned char rec_tem = 0;   //--���ջ���

		  if(USART_GetITStatus(DEBUG_USART2, USART_IT_RXNE) != RESET)	 //�ж϶��Ĵ����Ƿ�ǿ�   �����ж�
			{	
				rec_tem = USART_ReceiveData(DEBUG_USART2);    //�����Ĵ��������ݻ��浽���ջ�������  
        Screen_Get_FData(rec_tem);
				Screen_Get_NData(rec_tem);
/
				
		USART_ClearITPendingBit(DEBUG_USART2,USART_IT_RXNE);
	 }
 }

void Usart2_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
{
	/* ����һ���ֽ����ݵ�USART */
	USART_SendData(pUSARTx,ch);
		
	/* �ȴ��������ݼĴ���Ϊ�� */
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
  
	
	
	
  /* �ȴ�������� */
  while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET)
  {}
}	
/****************** ����8λ������ ************************/
void Usart2_SendArray( USART_TypeDef * pUSARTx, uint8_t *array, uint16_t num)
{
  uint8_t i;
	
	for(i=0; i<num; i++)
  {
	    /* ����һ���ֽ����ݵ�USART */
	    Usart2_SendByte(pUSARTx,array[i]);	
  
  }
	/* �ȴ�������� */
	while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET);
}


void USART2_Send_Len_Str(u8 *str, u8 len)
{
	u8 i;

	for(i=0; i<len; i++)
		Usart2_SendByte(USART2,*str ++);
}

  /* ָ��������ʾ��Ϣ */
 void Usart2_Show_Message(void)
{
	Usart2_SendString(DEBUG_USART2,"����һ��ͨ������ͨ��ָ�����LED��ʵ�� \n");
	Usart2_SendString(DEBUG_USART2,"ʹ��  USART  ����Ϊ��%d 8-N-1 \n");
	Usart2_SendString(DEBUG_USART2,"������ӵ�ָ������LED����ɫ��ָ���Ӧ���£�\n");
	Usart2_SendString(DEBUG_USART2,"  ָ��   ------ LED�ƺ� \n");
	Usart2_SendString(DEBUG_USART2,"    1    ------    LED1 \n");
	Usart2_SendString(DEBUG_USART2,"     2    ------    BEEP \n");
  Usart2_SendString(DEBUG_USART2,"     3    ------    �� \n");
//  printf("\r\n   ����һ��ͨ������ͨ��ָ�����LED��ʵ�� \n");
//  printf("ʹ��  USART  ����Ϊ��%d 8-N-1 \n",USART2);
//  printf("������ӵ�ָ������LED����ɫ��ָ���Ӧ���£�\n");
//  printf("   ָ��   ------ LED�ƺ� \n");
//  printf("     1    ------    LED1 \n");
//  printf("     2    ------    LED2 \n");
//  printf("     3    ------    �� \n");  
}

/*ͨ�����ڴ������ݵ�ESP*/


static char *    itoa           ( int value, char * string, int radix );


/*
 * ��������USART3_print(PB10 PB11)
 * ����  ����ʽ�������������C���е�printf��������û���õ�C��
 * ����  ��-USARTx ����ͨ��������ֻ�õ��˴���2����USART2
 *		     -Data   Ҫ���͵����ڵ����ݵ�ָ��
 *			   -...    ��������
 * ���  ����
 * ����  ���� 
 * ����  ���ⲿ����
 *         ����Ӧ��USART2_printf( USART2, "\r\n this is a demo \r\n" );
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

	while ( * Data != 0 )     // �ж��Ƿ񵽴��ַ���������
	{				                          
		if ( * Data == 0x5c )  //'\'
		{									  
			switch ( *++Data )
			{
				case 'r':							          //�س���
				USART_SendData(USARTx, 0x0d);
				Data ++;
				break;

				case 'n':							          //���з�
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
				case 's':										  //�ַ���
				s = va_arg(ap, const char *);
				
				for ( ; *s; s++) 
				{
					USART_SendData(USARTx,*s);
					while( USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET );
				}
				
				Data++;
				
				break;

				case 'd':			
					//ʮ����
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
 * ��������itoa
 * ����  ������������ת�����ַ���
 * ����  ��-radix =10 ��ʾ10���ƣ��������Ϊ0
 *         -value Ҫת����������
 *         -buf ת������ַ���
 *         -radix = 10
 * ���  ����
 * ����  ����
 * ����  ����USART2_printf()����
 */
static char * itoa( int value, char *string, int radix )
{
	int     i, d;
	int     flag = 0;
	char    *ptr = string;

	/*����ʮ������*/
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

	/* �������ϼ��� */
	if (value < 0)
	{
		*ptr++ = '-';

		/* �˷������� */
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

	/* ��ֹ���ַ��� */
	*ptr = 0;

	return string;

}



 




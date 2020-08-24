#include "UART.h"


//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	      
#if 1
#pragma   import(__use_no_semihosting)  
//��׼����Ҫ��֧�ֺ���  
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
_sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while((DEBUG_USARTx->SR&0X40)==0);//ѭ������,ֱ���������   
    DEBUG_USARTx->DR = (u8) ch;      
	return ch;
}
#endif
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



uint8_t TxBuffer1[10] ;   //�������ݻ�����
u8 RxBuffer1[10] = {0};    //�������ݻ�����
uint8_t rec_flag = 0;
uint8_t rec_flag1 = 0;
uint8_t tx_flag = 0;
__IO uint8_t TxCounter1 = 0x00;
__IO uint8_t RxCounter1 = 0x00; 
   void USART1_NVIC_Configuration()
	 {
		 NVIC_InitTypeDef NVIC_InitStructure;
		 	/*����NVIC�ж����ȼ���*/
		 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
		 /* ����USARTΪ�ж�Դ */
		 NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART_IRQ;
		  /* �������ȼ�*/
		 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		 /* �����ȼ� */
		 NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
		  /* ʹ���ж� */
		 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		  /* ��ʼ������NVIC */
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
				// ��USART Tx��GPIO����Ϊ���츴��ģʽ
				GPIO_InitStructure.GPIO_Pin = DEBUG_USART_TX_GPIO_PIN;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
				GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStructure); 
				// ��USART Rx��GPIO����Ϊ���ÿ�©ģʽ
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
			    //��ʼ���������� 
			 USART_InitStructure.USART_BaudRate = 115200;  //������9600
			 USART_InitStructure.USART_WordLength = USART_WordLength_8b;  //�ֳ�8λ
			 USART_InitStructure.USART_StopBits = USART_StopBits_1;     //1λֹͣ�ֽڡ�
			 USART_InitStructure.USART_Parity = USART_Parity_No;   //����żУ��
			 USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��������
			 USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//��RX���պ�TX	���͹���  �շ�һ��
			 USART_Init(DEBUG_USARTx, &USART_InitStructure);  
			 // ʹ�ܴ��ڽ����ж�	
       //USART_ClearFlag(USART2,USART_FLAG_TC);  
			 USART_ITConfig(DEBUG_USARTx,USART_IT_RXNE,ENABLE);//���������ж�
//			 USART_ITConfig(DEBUG_USARTx,USART_IT_TXE,ENABLE);//�������ж�
			 // ʹ�ܴ���
			 USART_Cmd(DEBUG_USARTx,ENABLE);
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

   void DEBUG_USART_IRQHandler(void) 
	 {
		   unsigned char rec_tem = 0;   //--���ջ���

		  if(USART_GetITStatus(DEBUG_USARTx, USART_IT_RXNE) != RESET)	 //�ж϶��Ĵ����Ƿ�ǿ�   �����ж�
			{	

				rec_tem = USART_ReceiveData(DEBUG_USARTx);    //�����Ĵ��������ݻ��浽���ջ�������  
		     ESP8266_IntGenData(rec_tem);
				USART_ClearITPendingBit(DEBUG_USARTx,USART_IT_RXNE);
		   
	 }
 }

void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
{
	/* ����һ���ֽ����ݵ�USART */
	USART_SendData(pUSARTx,ch);
		
	/* �ȴ��������ݼĴ���Ϊ�� */
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
  
	
	
	
  /* �ȴ�������� */
  while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET)
  {}
}	
/****************** ����8λ������ ************************/
void Usart_SendArray( USART_TypeDef * pUSARTx, uint8_t *array, uint16_t num)
{
  uint8_t i;
	
	for(i=0; i<num; i++)
  {
	    /* ����һ���ֽ����ݵ�USART */
	    Usart_SendByte(pUSARTx,array[i]);	
  
  }
	/* �ȴ�������� */
	while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET);
}


void USART1_Send_Len_Str(u8 *str, u8 len)
{
	u8 i;

	for(i=0; i<len; i++)
		Usart_SendByte(USART1,*str ++);
}

  /* ָ��������ʾ��Ϣ */
 void Show_Message(void)
{
	Usart_SendString(DEBUG_USARTx,"����һ��ͨ������ͨ��ָ�����LED��ʵ�� \n");
	Usart_SendString(DEBUG_USARTx,"ʹ��  USART  ����Ϊ��%d 8-N-1 \n");
	Usart_SendString(DEBUG_USARTx,"������ӵ�ָ������LED����ɫ��ָ���Ӧ���£�\n");
	Usart_SendString(DEBUG_USARTx,"  ָ��   ------ LED�ƺ� \n");
	Usart_SendString(DEBUG_USARTx,"    1    ------    LED1 \n");
	Usart_SendString(DEBUG_USARTx,"     2    ------    BEEP \n");
  Usart_SendString(DEBUG_USARTx,"     3    ------    �� \n");
//  printf("\r\n   ����һ��ͨ������ͨ��ָ�����LED��ʵ�� \n");
//  printf("ʹ��  USART  ����Ϊ��%d 8-N-1 \n",USART2);
//  printf("������ӵ�ָ������LED����ɫ��ָ���Ӧ���£�\n");
//  printf("   ָ��   ------ LED�ƺ� \n");
//  printf("     1    ------    LED1 \n");
//  printf("     2    ------    LED2 \n");
//  printf("     3    ------    �� \n");  
}




 




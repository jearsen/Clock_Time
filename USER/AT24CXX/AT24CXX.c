#include "AT24CXX.h"


	u8 TEXT_Buffer[5]={"12344"};
	u8 temp[5];
	u16 Value = 50; 
	u16 Value2;
//��AT24CXXָ����ַ����һ������
//ReadAddr:��ʼ�����ĵ�ַ  
//����ֵ  :����������
u8 AT24CXX_ReadOneByte(u16 ReadAddr)
{				  
	u8 temp=0;		  	    																 
    IIC_Start();  
	if(EE_TYPE>AT24C16)
	{
		IIC_Send_Byte(0XA0);	   //����д����
		IIC_Wait_Ack();
		IIC_Send_Byte(ReadAddr>>8);//���͸ߵ�ַ
		IIC_Wait_Ack();		 
	}else IIC_Send_Byte(0XA0+((ReadAddr/256)<<1));   //����������ַ0XA0,д���� 	 

//	IIC_Wait_Ack(); 
    IIC_Send_Byte(ReadAddr%256);   //���͵͵�ַ
	IIC_Wait_Ack();	    
	IIC_Start();  	 	   
	IIC_Send_Byte(0XA1);           //�������ģʽ			   
	IIC_Wait_Ack();	 
    temp=IIC_Read_Byte(0);		   
    IIC_Stop();//����һ��ֹͣ����	    
	return temp;
}

//��AT24CXXָ����ַд��һ������
//WriteAddr  :д�����ݵ�Ŀ�ĵ�ַ    
//DataToWrite:Ҫд�������
void AT24CXX_WriteOneByte(u16 WriteAddr,u8 DataToWrite)
{				   	  	    																 
    IIC_Start();  
	if(EE_TYPE>AT24C16)
	{	
		IIC_Send_Byte(0XA0);	    //����д����
		IIC_Wait_Ack();
		IIC_Send_Byte(WriteAddr>>8);//���͸ߵ�ַ
 	}else
	{
		
		IIC_Send_Byte(0XA0+((WriteAddr/256)<<1));   //����������ַ0XA0,д���� 
	}	 
	IIC_Wait_Ack();	   
  IIC_Send_Byte(WriteAddr%256);   //���͵͵�ַ
	IIC_Wait_Ack(); 	 										  		   
	IIC_Send_Byte(DataToWrite);     //�����ֽ�							   
	IIC_Wait_Ack();  		    	   
    IIC_Stop();//����һ��ֹͣ���� 
	delay_ms(10);	 
}

//��AT24CXX�����ָ����ַ��ʼд�볤��ΪLen������
//�ú�������д��16bit����32bit������.
//WriteAddr  :��ʼд��ĵ�ַ  
//DataToWrite:���������׵�ַ
//Len        :Ҫд�����ݵĳ���2,4
void AT24CXX_WriteLenByte(u16 WriteAddr,u32 DataToWrite,u8 Len)
{  	
	u8 t;
	for(t=0;t<Len;t++)
	{
		AT24CXX_WriteOneByte(WriteAddr+t,(DataToWrite>>(8*t))&0xff);
	}												    
}

//��AT24CXX�����ָ����ַ��ʼ��������ΪLen������
//�ú������ڶ���16bit����32bit������.
//ReadAddr   :��ʼ�����ĵ�ַ 
//����ֵ     :����
//Len        :Ҫ�������ݵĳ���2,4
u32 AT24CXX_ReadLenByte(u16 ReadAddr,u8 Len)
{  	
	u8 t;
	u32 temp=0;
	for(t=0;t<Len;t++)
	{
		temp<<=8;
		temp+=AT24CXX_ReadOneByte(ReadAddr+Len-t-1); 	 				   
	}
	return temp;												    
}
//���AT24CXX�Ƿ�����
//��������24XX�����һ����ַ(255)���洢��־��.
//���������24Cϵ��,�����ַҪ�޸�
//����1:���ʧ��
//����0:���ɹ�
u8 AT24CXX_Check(void)
{
	u8 temp;
	temp=AT24CXX_ReadOneByte(255);//����ÿ�ο�����дAT24CXX			   
	if(temp==0X55)return 0;		   
	else//�ų���һ�γ�ʼ�������
	{
		 
		AT24CXX_WriteOneByte(255,0X55);
	  temp=AT24CXX_ReadOneByte(255);
//    printf("%x\r\n",temp);	  
		if(temp==0X55)return 0;
	}
	return 1;											  
}

//��AT24CXX�����ָ����ַ��ʼ����ָ������������
//ReadAddr :��ʼ�����ĵ�ַ ��24c02Ϊ0~255
//pBuffer  :���������׵�ַ
//NumToRead:Ҫ�������ݵĸ���
void AT24CXX_Read(u16 ReadAddr,u8 *pBuffer,u16 NumToRead)
{
	while(NumToRead)
	{
		*pBuffer++=AT24CXX_ReadOneByte(ReadAddr++);	
		NumToRead--;
	}
}  
//��AT24CXX�����ָ����ַ��ʼд��ָ������������
//WriteAddr :��ʼд��ĵ�ַ ��24c02Ϊ0~255
//pBuffer   :���������׵�ַ
//NumToWrite:Ҫд�����ݵĸ���
void AT24CXX_Write(u16 WriteAddr,u8 *pBuffer,u16 NumToWrite)
{
	while(NumToWrite--)
	{
		AT24CXX_WriteOneByte(WriteAddr,*pBuffer);
		WriteAddr++;
		pBuffer++;
	}
}

void AT24CXX_Write_Alarm_Value(void)
{
	AT24CXX_WriteOneByte(AT24CXX_Alarm_value_Addr,Alarm_hour >> 8);
	AT24CXX_WriteOneByte(AT24CXX_Alarm_value_Addr+1,Alarm_hour );
	AT24CXX_WriteOneByte(AT24CXX_Alarm_value_Addr+2,Alarm_Minutes >> 8);
	AT24CXX_WriteOneByte(AT24CXX_Alarm_value_Addr+3,Alarm_Minutes );
	AT24CXX_WriteOneByte(AT24CXX_Alarm_value_Addr+4,Alarm_Month >> 8);
	AT24CXX_WriteOneByte(AT24CXX_Alarm_value_Addr+5,Alarm_Month );
	AT24CXX_WriteOneByte(AT24CXX_Alarm_value_Addr+6,Alarm_Date >> 8);
	AT24CXX_WriteOneByte(AT24CXX_Alarm_value_Addr+7,Alarm_Date );
}


void AT24CXX_Read_Alarm_Value(void)
{
	Alarm_hour = (AT24CXX_ReadOneByte(AT24CXX_Alarm_value_Addr)<<8 | AT24CXX_ReadOneByte(AT24CXX_Alarm_value_Addr+1));
	Alarm_Minutes = (AT24CXX_ReadOneByte(AT24CXX_Alarm_value_Addr+2)<<8 | AT24CXX_ReadOneByte(AT24CXX_Alarm_value_Addr+3));
	Alarm_Month = (AT24CXX_ReadOneByte(AT24CXX_Alarm_value_Addr+4)<<8 | AT24CXX_ReadOneByte(AT24CXX_Alarm_value_Addr+5));
	Alarm_Date = (AT24CXX_ReadOneByte(AT24CXX_Alarm_value_Addr+6)<<8 | AT24CXX_ReadOneByte(AT24CXX_Alarm_value_Addr+7));
}

// void TEST(void)
// {
//	if(AT24CXX_Check()==0)
//	{
//		AT24CXX_Write(0,(u8*)TEXT_Buffer,5);
//		delay_ms(100);
//		AT24CXX_Read(0,temp,5);
//		printf("%s\r\n",temp);
//	}
// }






































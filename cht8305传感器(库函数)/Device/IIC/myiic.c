#include "myiic.h"
#include "delay.h"
#include "cht8305.h"

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//IIC驱动 代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/9
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
 #define PrintMsg	printf
//初始化IIC
void IIC_GPIO_Init(void)
{					     
	GPIO_InitTypeDef GPIO_InitStructure;
	//RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );	//使能GPIOB时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE); 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;   //
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_8); 	//PB8,PB9 输出高
  
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;   //
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_9); 	//PB8,PB9 输出高

	GPIO_PinRemapConfig(GPIO_Remap_I2C1, ENABLE); 

}

void IIC_Configuration(void)
{
	I2C_InitTypeDef I2C_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
		
	I2C_DeInit(I2C1);
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;    
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;    
	I2C_InitStructure.I2C_OwnAddress1 = CHT8305_DEV_ADDR;//主机的地址            
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;    
	I2C_InitStructure.I2C_AcknowledgedAddress= I2C_AcknowledgedAddress_7bit;    
	I2C_InitStructure.I2C_ClockSpeed = 25000;//100KHZ    
  	I2C_Init(I2C1, &I2C_InitStructure);    
	I2C_Cmd(I2C1, ENABLE);                                         
}

void IIC_Init(void)
{
	IIC_GPIO_Init();
	IIC_Configuration();
}


u8 IIC_Master_BufferWrite(I2C_TypeDef * I2Cx, u8 pBuffer, u8 NumByteToWrite, u8 SlaveAddress)
{    
	if(NumByteToWrite==0)        
	return 1;    /* 1.开始*/    

	PrintMsg("1\r\n");

	I2C_GenerateSTART(I2C1, ENABLE);   
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));    /* 2.设备地址·/写 */    

	PrintMsg("2\r\n");
	
	I2C_Send7bitAddress(I2C1, SlaveAddress, I2C_Direction_Transmitter);    
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));    /* 3.连续写数据 */    

	PrintMsg("3\r\n");
	
	while(NumByteToWrite--)    
	{      
		I2C_SendData(I2C1, pBuffer);      
		while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));     
		pBuffer++;    
	}    /* 4.停止 */  

	PrintMsg("4\r\n");
	
	I2C_GenerateSTOP(I2C1, ENABLE);    
	while ((I2C1->CR1&0x200) == 0x200);    

	PrintMsg("5\r\n");
	return 0;
}

u8 IIC_Master_BufferRead(I2C_TypeDef * I2Cx, u8 * pBuffer, u8 NumByteToRead, u8 SlaveAddress)
{
	if(NumByteToRead==0)
		return 1;

	 while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));      
	 I2C_AcknowledgeConfig(I2C1, ENABLE);    
	 
	 /* 1.开始*/    
//	 I2C_GenerateSTART(I2Cx, ENABLE);    
//	 while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT));    
	 
	 /* 2.设备地址·/写 */    
//	 I2C_Send7bitAddress(I2Cx, SlaveAddress, I2C_Direction_Transmitter);    
//	 while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));    
	 
	 /* 3.开始*/    
	 I2C_GenerateSTART(I2C1, ENABLE);    
	 while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));    
	 
	 /* 4.设备地址·/读 */    
	 I2C_Send7bitAddress(I2C1, SlaveAddress, I2C_Direction_Receiver);    
	 while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));   
	 
	 /* 5.连续写数据 */    
	 while (NumByteToRead)    
	 {        
	 		if(NumByteToRead==1)        
	 		{           
	 			I2C_AcknowledgeConfig(I2C1, DISABLE);            
				I2C_GenerateSTOP(I2C1, ENABLE);//6.停止，非应答        
			}      
			
			while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED));  /* EV7 */        
			*pBuffer++ = I2C_ReceiveData(I2C1);        
			NumByteToRead--;    
	}   
	 	I2C_AcknowledgeConfig(I2C1, ENABLE);    
	 	return 0;
}

























#ifndef __MYIIC_H
#define __MYIIC_H
#include "stm32f10x.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//IIC���� ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/9
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////


//IIC���в�������
void IIC_GPIO_Init(void);
void IIC_Configuration(void);
u8 IIC_Master_BufferWrite(I2C_TypeDef * I2Cx, u8 pBuffer, u8 NumByteToWrite, u8 SlaveAddress);
u8 IIC_Master_BufferRead(I2C_TypeDef * I2Cx, u8 * pBuffer, u8 NumByteToRead, u8 SlaveAddress);
void IIC_Init(void);                //��ʼ��IIC��IO��				 	  
#endif

















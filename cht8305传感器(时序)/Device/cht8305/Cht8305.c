#include "cht8305.h"
#include "myiic.h"
#include "delay.h"


#define PrintMsg	printf

byte configReg;
byte buf[4];

void CHT8305_init()
{
	IIC_Init();
}

unsigned int CHT8305_is_connected()
{
	uint Did =0;
	uint Mid = 0;
	IIC_Start();
	IIC_Send_Byte(CHT8305_DEV_ADDR);
	Mid = CHT8305_get_manufacturerID();
  Did = CHT8305_get_deviceID();
  //PrintMsg("id=%d",id);
	if(Did ==0X8305 && Mid== 0x5959)
  {
      PrintMsg("  read Version ID=0x%x and Manufacture ID=%x\n",Did,Mid);
    	return 1;
  }
	return 0;
}


unsigned int CHT8305_get_manufacturerID()
{
	CHT8305_read_reg(CHT8305_REG_MID, 2);
	return buf[0] << 8 | buf[1];
}


unsigned int CHT8305_get_deviceID()
{
	CHT8305_read_reg(CHT8305_REG_DID, 2);
	return buf[0] << 8 | buf[1];
}



void CHT8305_write_reg(byte regAddr, u16 DataToWrite)
{
	int data;
	IIC_Start();
	IIC_Send_Byte(CHT8305_DEV_ADDR);
	IIC_Send_Byte(regAddr);
  
  data=(DataToWrite >> 8)	&0xff;						  		   
	IIC_Send_Byte(data);     //发送高字节		
	 
	data=	DataToWrite & 0xff;						  		   
	IIC_Send_Byte(data);     //发送低字节		
  
  IIC_Stop();//产生一个停止条件 
}


void CHT8305_read_reg(byte regAddr, byte numOfBytes)
{
	byte READ_ADDR;
	int i;
	IIC_Start();
	IIC_Send_Byte(CHT8305_DEV_ADDR);
	IIC_Send_Byte(regAddr);
  IIC_Stop();
  
	if(regAddr == CHT8305_REG_TEMP || regAddr ==CHT8305_REG_HUMI)
	{
		delay_ms(10);
	}
	
	READ_ADDR=CHT8305_DEV_ADDR |0X01;
	IIC_Start();
	IIC_Send_Byte(READ_ADDR);
  
	for(i =0; i<numOfBytes-1; i++)
	{
		buf[i] = IIC_Read_Byte(0);
	}

	buf[numOfBytes -1] = IIC_Read_Byte(1);
	
	IIC_Stop();
}

uint CHT8305_get_temp_humi(float * temp,float * humi)
{
	unsigned int th , tl, hh ,hl;
	CHT8305_read_reg(CHT8305_REG_TEMP, 4);

	th =buf[0];
	tl =buf[1];
	hh =buf[2];
	hl =buf[3];

	(*temp) =(th <<8 | tl) * 165.0 /65535.0 -40.0;
	(*humi)=(hh <<8 |hl) * 100.0 /65535.0;
	PrintMsg("temp=%f, humi=%f \r\n",(*temp), (*humi));
}


void CHT8305_Write_Alert(u16 alert)
{
	CHT8305_write_reg(CHT8305_REG_Alert,alert);
}
	
u16 CHT8305_Read_Alert(void)
{
	CHT8305_read_reg(CHT8305_REG_Alert, 2);
	return buf[0] << 8 | buf[1];
}





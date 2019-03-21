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
	byte ret =0;
	uint id = 0;
//	IIC_Start();
//	IIC_Send_Byte(CHT8305_DEV_ADDR);
	id = CHT8305_get_manufacturerID();
  //PrintMsg("id=%d",id);
	if( id== 0x5959)
  {
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


void CHT8305_read_reg(byte regAddr, byte numOfBytes)
{
	byte READ_ADDR;

	IIC_Master_BufferWrite(I2C1,regAddr , 1, CHT8305_DEV_ADDR);
  
	if(regAddr == CHT8305_REG_TEMP || regAddr ==CHT8305_REG_HUMI)
	{
		delay_ms(10);
	}
	
	READ_ADDR=CHT8305_DEV_ADDR |0X01;

  	IIC_Master_BufferRead(I2C1, buf,numOfBytes,READ_ADDR);
}

uint CHT8305_get_temp_humi(float * temp,float * humi)
{
	unsigned int th , tl, hh ,hl;
	CHT8305_read_reg(CHT8305_REG_TEMP, 2);

	th =buf[0];
	tl  =buf[1];
  
 // CHT8305_read_reg(CHT8305_REG_HUMI, 2);
	//hh=buf[0];
//	hl =buf[1];

	(*temp) =(th <<8 | tl) * 165.0 /65535.0 -40.0;
	//(*humi)=(hh <<8 |hl) * 100.0 /65535.0;
 	 PrintMsg("temp=%f\r\n",(*temp));
}

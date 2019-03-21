#ifndef	CHT8305_H
#define	CHT8305_H

#include"STM32F10x.h" 

/*	cht8305
*	http://www.sensylink.com
*	mjp
*/

#define	byte unsigned char
#define	uint unsigned int
#define	CHT8305_DEV_ADDR	0x88
#define	CHT8305_REG_TEMP	0x00
#define	CHT8305_REG_HUMI	0x01
#define CHT8305_REG_CONF 0x02
#define CHT8305_REG_Alert 0x03
#define CHT8305_REG_MID 0xFE //0x5959
#define CHT8305_REG_DID 0xFF //0x8305
static const byte BIT_T_RES = 2;
static const byte BIT_H_RES = 0;
static const byte BIT_BATTERY_OK = 3;
static const byte BIT_ACQ_MODE = 4;
static const byte BIT_HEATER = 5;
static const byte BIT_RST = 7;
static const byte T_RES_14 = 0;
static const byte T_RES_11 = 1;
static const byte H_RES_14 = 0;
static const byte H_RES_11 = 1;
static const byte H_RES_8 = 2;

void CHT8305_init(void);
uint CHT8305_is_connected(void);
uint CHT8305_get_manufacturerID(void);
uint CHT8305_get_deviceID(void);
void CHT8305_write_reg(byte regAddr, u16 DataToWrite);
void CHT8305_read_reg(byte regAddr, byte numOfBytes);
uint CHT8305_get_temp_humi(float * temp,float * humi);

#endif

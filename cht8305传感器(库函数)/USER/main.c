#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "cht8305.h"
#include "myiic.h"

#define PrintMsg	printf
		 	
	
 int main(void)
 {	 
  float temp, humi;
	delay_init();	    	 //延时函数初始化	
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);   
	uart_init(115200);	 	//串口初始化为115200
   	CHT8305_init();
	while(1)
	{
    		CHT8305_get_temp_humi(&temp, &humi);
	}
}

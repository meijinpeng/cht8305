#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "cht8305.h"
#include "myiic.h"

#define PrintMsg	printf
		 	
	
 int main(void)
 {	 
  float temp, humi;
	delay_init();	    	 //��ʱ������ʼ��	
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
  CHT8305_init();
	while(1)
	{
    CHT8305_get_temp_humi(&temp, &humi);
    delay_ms(100);
	}
}


#include "uart_to_pc.h"



void send_to_pc(char* latitude_string,char* longitude_string,int lat_size,int lon_size)
{
	int i;
	for(i = 0 ; i < lat_size ; i++)
	{
		UART0_sendByte(latitude_string[i]);
	}

	UART0_sendByte(',');

	for(i = 0 ; i < lon_size ; i++)
	{
		UART0_sendByte(latitude_string[i]);
	}

	UART0_sendByte('\n');
}
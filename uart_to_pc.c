
#include "uart_to_pc.h"



void send_to_pc(char* latitude_string,char* longitude_string)
{
	int size_lat,size_long;
	size_lat = sizeof(latitude_string)/sizeof(latitude_string[0]);
	size_long = sizeof(longitude_string)/sizeof(longitude_string[0]);

	int i;
	for(i = 0 ; i < size_lat ; i++)
	{
		UART0_sendByte(latitude_string[i]);
	}

	UART0_sendByte(',');

	for(i = 0 ; i < size_long ; i++)
	{
		UART0_sendByte(latitude_string[i]);
	}

	UART0_sendByte('\n');
}
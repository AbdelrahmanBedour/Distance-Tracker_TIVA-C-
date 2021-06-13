#include "uart_to_pc.h"



void send_to_pc(char* latitude_string,char* longitude_string)
{
	int i=0;
	while(latitude_string[i] != '\0')
	{
		UART0_sendByte(latitude_string[i]);
		i++;
	}

	UART0_sendByte(',');

	i=0;
	while(longitude_string[i] != '\0')
	{
		UART0_sendByte(longitude_string[i]);
		i++;
	}

	UART0_sendByte('\n');
}

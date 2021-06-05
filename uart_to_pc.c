
#include "uart_to_pc.h"

int coordinates_index=0;
double latitude_array[ARRAY_SIZE];
double longitude_array[ARRAY_SIZE];

void save_coordinates(double latitude,double longitude)
{
    if (coordinates_index < ARRAY_SIZE)
    {
        latitude_array[coordinates_index] = latitude;
        longitude_array[coordinates_index] = longitude;
        coordinates_index++;
    }
    else //array exceeded
    {
        latitude_array[ARRAY_SIZE - 1] = 0; //as a flag that array limit reached
        longitude_array[ARRAY_SIZE - 1] = 0; //as a flag that array limit reached
    }
}

void send_to_pc(double latitude,double longitude)
{
	char latitude_string[20];
	char longitude_string[20];

	snprintf(latitude_string, 20, "%f", latitude);
	snprintf(longitude_string, 20, "%f", longitude);

    int i=0;
    while(latitude_string[i] != '\0')
    {
        UART0_sendByte(latitude_string[i]);
        i++;
    }

    UART0_sendByte(',');

    i=0;
    while(latitude_string[i] != '\0')
    {
        UART0_sendByte(latitude_string[i]);
        i++;
    }

    UART0_sendByte('\n');
}

void send_all_coordinates_to_pc(double* latitude,double* longitude)
{
    int i=0;
    for(i = 0 ; i < coordinates_index ; i++)
    {
        send_to_pc(latitude[i],longitude[i]);
    }
}


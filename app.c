 /******************************************************************************
 *
 * Module: Application
 *
 * File Name: App.c
 *
 * Description: Source file for Application .
 *
 ******************************************************************************/
#include "app.h"


/* Description: Task executes once to initialize all the Modules */
void Init_Task(void)
{
	
   /* Initialize LED Driver */
	Led_init(1);
	
	/* Initialize LED Driver */
	LCD_init();
	
	/* Initialize UART Driver */
	UART0_init();

	/* Initialize GPS Driver including UART1*/
	gps_init();
}



/* Description: Task executes every 40 Mili-seconds to refresh the LED */
void LED_Task(int distance)
{
	static int flag = 0;
	if((distance>=100) && (flag == 0))
	{
		Led_on(1);
		Delay_MS(3000);
		Led_off(1);
		flag = 1;
	}
}

void LCD_Task(int distance)
{
	LCD_goToRowColumn(0,11);
	LCD_intgerToString(distance);
}

void GPS_Task(double*lat1,double*lng1,double*lat2,double*lng2,int* first_time_flag)
{	
	if(*first_time_flag == 1)
	{
		gps_receive_data(lat2,lng2);
		*first_time_flag=0;
	}
	lat1 = lat2;
	lng1 = lng2;		
	gps_receive_data(lat2,lng2);
}

double haversine(double lat1, double lon1,double lat2, double lon2)
{
	// distance between latitudes
	// and longitudes
	double dLat = (lat2 - lat1) * M_PI / 180.0;
	double dLon = (lon2 - lon1) * M_PI / 180.0;

	// convert to radians
	lat1 = (lat1) * M_PI / 180.0;
	lat2 = (lat2) * M_PI / 180.0;

	// apply formulae
	double a = pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * cos(lat1) * cos(lat2);
	double rad = 6371;
	double c = 2 * asin(sqrt(a));
	return rad * c;
}

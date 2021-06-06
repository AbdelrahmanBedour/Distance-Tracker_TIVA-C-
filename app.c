 /******************************************************************************
 *
 * Module: Application
 *
 * File Name: App.c
 *
 * Description: Source file for Application .
 *
 ******************************************************************************/

#include "App.h"
#include "uart.h"
#include "led.h"
#include "gps_driver.h"
#include "lcd.h"
#include <stdlib.h>
#include <math.h>

/* Description: Task executes once to initialize all the Modules */
void Init_Task(void)
{
	
    /* Initialize LED Driver */
    Led_init(1);
	
	/* Initialize LED Driver */
	LCD_init();
	
	/* Initialize UART Driver */
	UART0_init();
	
	/* Initialize GPS Driver */
	gps_init();
}



/* Description: Task executes every 40 Mili-seconds to refresh the LED */
void Led_Task(int distance)
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

void GPS_Task(double*lat1,double*lng1,double*lat2,double*lng2)
{
	char lat_S[20],lat_S2[20],lng_S[20],lng_S2[20];
	char* endp;
        char* endp2;
        char* endp3;
        char* endp4;
			
	gps_receive_data(lat_S,lng_S);
	*lat1 = strtod(lat_S, &endp);
	*lng1 = strtod(lng_S, &endp2);
		
	
		
	gps_receive_data(lat_S2,lng_S2);
	*lat2 = strtod(lat_S2, &endp3);
	*lng2 = strtod(lng_S2, &endp4);
}

double haversine(double lat1, double lon1,
                        double lat2, double lon2)
    {
        // distance between latitudes
        // and longitudes
        double dLat = (lat2 - lat1) *
                      3.14159265358979323846 / 180.0;
        double dLon = (lon2 - lon1) *
                      3.14159265358979323846 / 180.0;
 
        // convert to radians
        lat1 = (lat1) * 3.14159265358979323846 / 180.0;
        lat2 = (lat2) * 3.14159265358979323846 / 180.0;
 
        // apply formulae
        double a = pow(sin(dLat / 2), 2) +
                   pow(sin(dLon / 2), 2) *
                   cos(lat1) * cos(lat2);
        double rad = 6371;
        double c = 2 * asin(sqrt(a));
        return rad * c;
    }
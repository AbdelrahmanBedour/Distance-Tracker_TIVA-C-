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
#define R 637100
#define TO_RAD (3.1415926536 / 180)

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
        static uint8 flag=0;
	if((distance>=100) && (flag == 0))
	{
		Led_on(1);
                flag = 1;
	}
}

void LCD_Task(int distance)
{
	LCD_goToRowColumn(0,11);
	LCD_intgerToString(distance);
}

double GPS_Task(double*lat1,double*lng1,double*lat2,double*lng2)
{

	volatile double dist1;
        volatile double dist2;
        volatile double dist3;
        volatile double dist4;
        volatile double dist5;
        volatile double avg;
	gps_receive_data(lat1,lng1);

        do{
        gps_receive_data(lat2,lng2);
        dist1 = dist(*lat1,*lng1,*lat2,*lng2);
        gps_receive_data(lat2,lng2);
        dist2 = dist(*lat1,*lng1,*lat2,*lng2);
        gps_receive_data(lat2,lng2);
        dist4 = dist(*lat1,*lng1,*lat2,*lng2);
        gps_receive_data(lat2,lng2);
        dist5 = dist(*lat1,*lng1,*lat2,*lng2);
        gps_receive_data(lat2,lng2);
        dist3 = dist(*lat1,*lng1,*lat2,*lng2);
        avg= (dist1+dist2+dist3+dist4+dist5)*5;
        }while(avg<1.5);
        return avg;

}

/*double haversine(double lat1, double lon1,double lat2, double lon2)
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
}*/

double dist(double th1, double ph1, double th2, double ph2)
{
	double dx, dy, dz;
	ph1 -= ph2;
	ph1 *= TO_RAD, th1 *= TO_RAD, th2 *= TO_RAD;
 
	dz = sin(th1) - sin(th2);
	dx = cos(ph1) * cos(th1) - cos(th2);
	dy = sin(ph1) * cos(th1);
	return asin(sqrt(dx * dx + dy * dy + dz * dz) / 2) * 2 * R;
}

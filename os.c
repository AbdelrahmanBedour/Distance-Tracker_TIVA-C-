 /******************************************************************************
 *
 * Module: Os
 *
 * File Name: Os.c
 *
 * Description: Source file for Os .
 *
 ******************************************************************************/
#include "os.h"



void Os_start(void)
{

	/* Execute the Init Task */
	Init_Task();

	/* Start the Os Scheduler */
	Os_Run();
}

/*********************************************************************************************/

void Os_Run(void)
{
	double distance = 0.0;
	int first_time_flag=1;
	double lat1,lng1,lat2,lng2;
	LCD_displayString("Distance = "); //0,11
	LCD_intgerToString((int)distance);
	
	while(1)
	{

                
                distance += GPS_Task(&lat1 , &lng1 , &lat2 , &lng2);
		
		LCD_Task((int)distance);
		
		LED_Task((int)distance);
	}
}
/*********************************************************************************************/

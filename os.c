 /******************************************************************************
 *
 * Module: Os
 *
 * File Name: Os.c
 *
 * Description: Source file for Os .
 *
 ******************************************************************************/

#include "Os.h"
#include "App.h"
#include "tm4c123gh6pm_registers.h"
#include "gps_driver.h"
#include "led.h"
#include "lcd.h"
#include "uart.h"
#include "delay.h"
#include<stdlib.h>
#include<string.h>



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
	int distance = 0;
	LCD_displayString("Distance = "); //0,11
	LCD_intgerToString(distance);
	
    while(1)
    {
		double lat1,lng1,lat2,lng2;
		
		GPS_Task(&lat1 , &lng1 , &lat2 , &lng2);		
		
		distance += (int)haversine(lat1 , lng1 , lat2 , lng2);
		
		LCD_Task(distance);
		
		Led_Task(distance);
    }

}
/*********************************************************************************************/

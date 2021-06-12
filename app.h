 /******************************************************************************
 *
 * Module: application
 *
 * File Name: App.h
 *
 * Description: Header file for Application Tasks.
 *
 ******************************************************************************/

#ifndef APP_H_
#define APP_H_

/******************************* INCLUDES *********************************/

#include <stdio.h>
#include <stdlib.h>
#include "std_types.h"
#include "uart.h"
#include "led.h"
#include "gps_driver.h"
#include "lcd.h"
#include "uart_to_pc.h"
#include <math.h>

/***************************** DEFINITIONS ***********************************/

#define M_PI (3.14159265)
#define R 637100
#define TO_RAD (3.1415926536 / 180)

/***************************** FUNCTIONS ************************************/


/* Description: Task executes once to initialize all the Modules */
void Init_Task(void);

double GPS_Task(double*lat1,double*lng1,double*lat2,double*lng2);

double haversine(double lat1, double lon1, double lat2, double lon2);

void LED_Task(int distance);

void LCD_Task(int distance);
double dist(double th1, double ph1, double th2, double ph2);
void UART_to_PC_Task(int distance);

#endif /* APP_H_ */

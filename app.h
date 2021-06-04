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

#include "std_types.h"

/* Description: Task executes once to initialize all the Modules */
void Init_Task(void);

void GPS_Task(double*lat1,double*lng1,double*lat2,double*lng2);

double haversine(double lat1, double lon1, double lat2, double lon2);

void Led_Task(int distance);

void LCD_Task(int distance);

#endif /* APP_H_ */

 /******************************************************************************
 *
 * Module: delay 
 *
 * File Name: delay.h
 *
 * Description: delay function for delay
 *
 *******************************************************************************/

#ifndef DELAY_H_
#define DELAY_H_

#define NUMBER_OF_ITERATIONS_PER_ONE_MILI_SECOND 762 /* For 16M freq */

/* FN prototype */
void Delay_MS(unsigned long long n);

#endif /* DELAY_H_ */

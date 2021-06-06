 /******************************************************************************
 *
 * Module: systick timer 
 *
 * File Name: systick.h
 *
 * Description: Header file for systick timer .
 *
 ******************************************************************************/

#ifndef SYSTICK_H_
#define SYSTICK_H_


#include "std_types.h"
#include "common_macros.h"
#include "tm4c123gh6pm_registers.h"

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

void SysTick_Start(uint16 Tick_Time);

void SysTick_Stop(void);

#endif /* SYSTICK_H_ */
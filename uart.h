 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART AVR driver
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "tm4c123gh6pm_registers.h"
#include "std_types.h"
#include "common_macros.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

   
#define  PORTA_PIN0   1
#define  PORTA_PIN1   2
#define  PORTA_PIN0_PIN1 3                 //0b00000011
   
#define  PORTC_PIN0   4
#define  PORTC_PIN1   5
#define  PORTC_PIN0_PIN1 0x30               //0b00110000
#define  RXFE 0x10
#define  TXFF 0x20
   
/* UART Driver Baud Rate */
#define USART_BAUDRATE 9600
#define USART_DIVINT_VALUE 104
#define USART_DIVFRAC_VALUE 11
#define DIVINT_MASK  65535              // MASK OF FIRST 16 BITS IN UARTIBRD REG 2^16-1
#define DIVFRAC_MASK 63                 // MASK OF FIRST 6 BITS IN UARTFBRD REG  2^5-1

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

   
void UART0_init(void);

void UART0_sendByte(const uint8 data);

uint8 UART0_recieveByte(void);


void UART1_init(void);

void UART1_sendByte(const uint8 data);

uint8 UART1_recieveByte(void);


#endif /* UART_H_ */

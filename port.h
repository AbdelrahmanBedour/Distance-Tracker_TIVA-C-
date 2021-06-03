 /******************************************************************************
 *
 * Module: port driver
 *
 * File Name: port.h
 *
 * Description: Header file for Port driver
 *
 *******************************************************************************/

#ifndef PORT_H_
#define PORT_H_

#include "std_types.h"
#include "common_macros.h"
#include "tm4c123gh6pm_registers.h"
#include "delay.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/* Port Numbers  */   
#define PORT_A  (uint8)0
#define PORT_B  (uint8)1
#define PORT_C  (uint8)2
#define PORT_D  (uint8)3
#define PORT_E  (uint8)4
#define PORT_F  (uint8)5
     
/* Pins Numbers  */
#define PIN_0   (uint8)0
#define PIN_1   (uint8)1
#define PIN_2   (uint8)2
#define PIN_3   (uint8)3
#define PIN_4   (uint8)4
#define PIN_5   (uint8)5
#define PIN_6   (uint8)6
#define PIN_7   (uint8)7
   
#define LOCK_KEY  0x4C4F434B  
   
/*******************************************************************************
 *                      Data Types                                   *
 *******************************************************************************/

typedef enum
{
    INPUT,OUTPUT
}PinDirection;

typedef struct
{ 
 uint8 port;
 uint8 pin;
 PinDirection direction ;
} PinConfig;


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

void Pin_init( const PinConfig* ConfigPtr);
void Pin_write( const PinConfig* ConfigPtr, uint8 data);
uint8 Pin_read( const PinConfig* ConfigPtr);


#endif /* PORT_H_ */
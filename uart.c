#include "uart.h"

/*******************************************************************************
 *                           UART0                                             *
 *******************************************************************************/

void UART0_init(void)
{
SYSCTL_RCGCUART_REG |= 1;                                   // ACTIVATE UART0 CLOCK
SYSCTL_REGCGC2_REG |= 1;                                   // ACTIVATE CLOCK FOR PORT A

UART0_CTL_R  =0;                                           // DISBALE UART
/* DECLARING THE BAUD RATE  */
UART0_IBRD_R = (USART_DIVINT_VALUE);                       //UART-_IBRD_R = 104  , MASKING ISN'T NESSECERALLY NEEDED HERE VALUE IS VERY LOW IN COMPARSION
UART0_FBRD_R = (USART_DIVFRAC_VALUE);                      //UART-_FBRD_R = 11
UART0_LCRH_R = 0x0070;                                                                          // WLEN = 11 (DATA BITS = 8) FEN =1 (ENABLE 16 ELEMENTS IN BUFFER)
UART0_CTL_R  = 0x0301;                                                                          // ENABLE UART , ENABLE TRANSMITTER ,ENABLE RECEIVER
                     
GPIO_PORTA_AMSEL_REG &= ~(PORTA_PIN0_PIN1);                  // WE WANT THIS PIN DIGITAL -> GPIO_PORTA_AMSEL_REG &= ~0X03
GPIO_PORTA_AFSEL_REG |= (PORTA_PIN0_PIN1);                   // TO ACTIVATE ALTERNATIVE FUNCTION SELECT FOR PIN0 AND PIN1
GPIO_PORTA_PCTL_REG  |= 0X00000011;                             // CHOOSE PIN0 AND PIN1 TO BE UART0 RECEIVE AND TRANSMIT RESPECTIVELY
GPIO_PORTA_DEN_REG |= (PORTA_PIN0_PIN1);                     // TO ENABLE PIN TO BE DIGITAL
}


void UART0_sendByte(const uint8 data)
{
   while( UART0_FR_R & TXFF);   //POLLING UNTIL TX FULL FLAG =0 (IF DATA BUFFER ISN'T FULL WE CAN SEND DATA) 
   UART0_DR_R=data;
}

uint8 UART0_recieveByte(void)
{
  while( UART0_FR_R & RXFE);    //POLLING UNTIL RX EMPTY FLAG =0 ( DATA BUFFER ISN'T EMPTY SO WE CAN START RECEIVING DATA)
  return (uint8)UART0_DR_R;     // RETURN FIRST 8 BITS IN UART0 DATA REGISTER
}


/*******************************************************************************
 *                           UART1                                             *
 *******************************************************************************/


void UART1_init(void)
{
SYSCTL_RCGCUART_REG |= 0x0020;                                               // ACTIVATE UART5 CLOCK        0b0010 0000
SYSCTL_REGCGC2_REG |=  0x0010;                            //0b00000100      // ACTIVATE CLOCK FOR PORT E

UART5_CTL_R  =0;                                           // DISBALE UART
/* DECLARING THE BAUD RATE  */
UART5_IBRD_R = (USART_DIVINT_VALUE);                       //UART-_IBRD_R = 104  , MASKING ISN'T NESSECERALLY NEEDED HERE VALUE IS VERY LOW IN COMPARSION
UART5_FBRD_R = (USART_DIVFRAC_VALUE);                      //UART-_FBRD_R = 11
UART5_LCRH_R = 0x0070;                                                                          // WLEN = 11 (DATA BITS = 8) FEN =1 (ENABLE 16 ELEMENTS IN BUFFER)
UART5_CTL_R  = 0x0301;                                                                          // ENABLE UART , ENABLE TRANSMITTER ,ENABLE RECEIVER
                     
GPIO_PORTE_AMSEL_REG &= ~(PORTE_PIN4_PIN5);                  // WE WANT THIS PIN DIGITAL -> GPIO_PORTC_AMSEL_REG
GPIO_PORTE_AFSEL_REG |= (PORTE_PIN4_PIN5);                   // TO ACTIVATE ALTERNATIVE FUNCTION SELECT FOR PIN4 AND PIN5
GPIO_PORTE_PCTL_REG  |= 0X00110000;                          // CHOOSE PIN4 AND PIN5 TO BE UART5 RECEIVE AND TRANSMIT RESPECTIVELY
GPIO_PORTE_DEN_REG |= (PORTE_PIN4_PIN5);                     // TO ENABLE PIN TO BE DIGITAL
}


void UART1_sendByte(const uint8 data)
{
   while( UART5_FR_R & TXFF);   //POLLING UNTIL TX FULL FLAG =0 (IF DATA BUFFER ISN'T FULL WE CAN SEND DATA) 
   UART5_DR_R=data;
}

uint8 UART1_recieveByte(void)
{
  while( UART5_FR_R & RXFE);    //POLLING UNTIL RX EMPTY FLAG =0 ( DATA BUFFER ISN'T EMPTY SO WE CAN START RECEIVING DATA)
  return (uint8)UART5_DR_R;     // RETURN FIRST 8 BITS IN UART0 DATA REGISTER
}




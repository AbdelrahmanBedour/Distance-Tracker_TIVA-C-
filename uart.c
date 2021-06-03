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
SYSCTL_RCGCUART_REG |= 0x0002;                                   // ACTIVATE UART1 CLOCK
SYSCTL_REGCGC2_REG |= 0x0002;                                   // ACTIVATE CLOCK FOR PORT B

UART1_CTL_R  =0;                                           // DISBALE UART
/* DECLARING THE BAUD RATE  */
UART1_IBRD_R = (USART_DIVINT_VALUE);                       //UART-_IBRD_R = 104  , MASKING ISN'T NESSECERALLY NEEDED HERE VALUE IS VERY LOW IN COMPARSION
UART1_FBRD_R = (USART_DIVFRAC_VALUE);                      //UART-_FBRD_R = 11
UART1_LCRH_R = 0x0070;                                                                          // WLEN = 11 (DATA BITS = 8) FEN =1 (ENABLE 16 ELEMENTS IN BUFFER)
UART1_CTL_R  = 0x0301;                                                                          // ENABLE UART , ENABLE TRANSMITTER ,ENABLE RECEIVER
                     
GPIO_PORTB_AMSEL_REG &= ~(PORTB_PIN0_PIN1);                  // WE WANT THIS PIN DIGITAL -> GPIO_PORTA_AMSEL_REG &= ~0X03
GPIO_PORTB_AFSEL_REG |= (PORTB_PIN0_PIN1);                   // TO ACTIVATE ALTERNATIVE FUNCTION SELECT FOR PIN0 AND PIN1
GPIO_PORTB_PCTL_REG  |= 0X00000011;                             // CHOOSE PIN0 AND PIN1 TO BE UART0 RECEIVE AND TRANSMIT RESPECTIVELY
GPIO_PORTB_DEN_REG |= (PORTB_PIN0_PIN1);                     // TO ENABLE PIN TO BE DIGITAL
}


void UART1_sendByte(const uint8 data)
{
   while( UART1_FR_R & TXFF);   //POLLING UNTIL TX FULL FLAG =0 (IF DATA BUFFER ISN'T FULL WE CAN SEND DATA) 
   UART1_DR_R=data;
}

uint8 UART1_recieveByte(void)
{
  while( UART1_FR_R & RXFE);    //POLLING UNTIL RX EMPTY FLAG =0 ( DATA BUFFER ISN'T EMPTY SO WE CAN START RECEIVING DATA)
  return (uint8)UART1_DR_R;     // RETURN FIRST 8 BITS IN UART0 DATA REGISTER
}




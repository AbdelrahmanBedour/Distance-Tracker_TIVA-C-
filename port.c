 /******************************************************************************
 *
 * Module: port driver
 *
 * File Name: port.c
 *
 * Description: Source file for Port driver
 *
 *******************************************************************************/

#include "port.h"

void Pin_init( const PinConfig* ConfigPtr)
{
  volatile uint32 * PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */
  volatile uint32 delay = 0; 
  
  if ( ( ConfigPtr->port > PORT_F  )|| ( ConfigPtr->pin > PIN_7  ) ) 
    return;
  
  /* If JTAG PIN skip it */
  if( (ConfigPtr->port  == PORT_C) && (ConfigPtr->pin <= PIN_3) )
     { 
       return;      
     }
  
  /* Get port base address */  
  switch(ConfigPtr->port)
  {
                    
  case  0:      PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
                                  break;                              
                    
  case  1:      PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
                                  break;
                             
  case  2:      PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
                                  break;
                                  
                    
  case  3:      PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
                                  break;                                 
                    
  case  4:      PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
                                  break;                                 
                    
  case  5:      PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
                                  break;             
  }
  /* enable port clock*/
  SYSCTL_REGCGC2_REG |= (1<<ConfigPtr->port);
  /* wait for the clock */
  delay = SYSCTL_REGCGC2_REG;
  
  if ( ( ConfigPtr->port == PORT_D && ConfigPtr->pin == PIN_7 ) ||  ( ConfigPtr->port == PORT_F && ConfigPtr->pin == PIN_0 ))
  {
    /* Unlock commit register for PD7 and PF0 */
    *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = LOCK_KEY;
    *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET) |= (1<<ConfigPtr->pin);
  }
                          
  /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
  CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , ConfigPtr->pin);
  /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
  SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , ConfigPtr->pin);                           
  
  /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
  CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , ConfigPtr->pin); 
  /* Clear the PMCx bits for this pin */
  *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (ConfigPtr->pin * 4));
  
  if(ConfigPtr->direction == OUTPUT)
  {                              
    /* Set the corresponding bit in the GPIODIR register to configure it as output pin */                
    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) ,ConfigPtr->pin);               
  }
  else if(ConfigPtr->direction == INPUT)
  {     
    /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */                
    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , ConfigPtr->pin);                
  }
  
}

void Pin_write( const PinConfig* ConfigPtr, uint8 data)
{
  volatile uint32 * PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */
  
  /* Get port base address */  
  switch(ConfigPtr->port)
  {
                    
  case  0:      PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
                                  break;                              
                    
  case  1:      PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
                                  break;
                             
  case  2:      PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
                                  break;
                                  
                    
  case  3:      PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
                                  break;                                 
                    
  case  4:      PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
                                  break;                                 
                    
  case  5:      PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
                                  break;             
  }
  if (data==HIGH)
  {
    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) ,ConfigPtr->pin);
  }
  else if (data==LOW)
  {
    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) ,ConfigPtr->pin);
  }
}
                          
uint8 Pin_read(const PinConfig* ConfigPtr)
{
  uint8 data;
  volatile uint32 * PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */
  
  /* Get port base address */  
  switch(ConfigPtr->port)
  {
                    
  case  0:      PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
                                  break;                              
                    
  case  1:      PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
                                  break;
                             
  case  2:      PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
                                  break;
                                  
                    
  case  3:      PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
                                  break;                                 
                    
  case  4:      PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
                                  break;                                 
                    
  case  5:      PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
                                  break;             
  }
  
  if (BIT_IS_SET(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) ,ConfigPtr->pin))
  {
    data = HIGH;
  }
  else if (BIT_IS_CLEAR(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) ,ConfigPtr->pin))
  {
    data = LOW;
  }
  return data;
}
                          
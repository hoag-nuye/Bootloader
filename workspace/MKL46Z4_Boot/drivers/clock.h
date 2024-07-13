//================ INCLUDE ================/
#include "MKL46Z4.h"
#include <stdint.h>
//================ DEFINED ================/
#ifndef __CLOCK_H_
#define __CLOCK_H_

#define CLK_TPM0_IR 1000000U
#define CLK_UART0_IR 4000000U
//------------- Enum -----------//
//Define value of fields

typedef enum{
	 CLK_PORTA,
	 CLK_PORTB,
	 CLK_PORTC,
	 CLK_PORTD,
	 CLK_PORTE,
	 CLK_ADC0,
	 CLK_PIT,
	 CLK_TPM0_MCGIRCLK,
	 CLK_UART0_MCGIRCLK,
}Perhipheral_Name_t;
//------------- Struct -----------//

//================ SUPPORT ================/

//================ FOCUSED ================/

// Configuration control port
void Clock_Enable(Perhipheral_Name_t name);
#endif

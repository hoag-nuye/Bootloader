//================ INCLUDE ================/
#include "MKL46Z4.h"
#include <stdint.h>
//================ DEFINED ================/
#ifndef __NVIC_H_
#define __NVIC_H_


//------------- Enum -----------//
//Define value of fields
typedef enum
{
	IR_PORTCD = 31U,
	IR_ADC0 = 15U,
	IR_UART0 = 12U
}IRQn_t;

//------------- Struct -----------//

//================ SUPPORT ================/

//================ FOCUSED ================/

// Configuration control port
void NVIC_EnableIRQn(IRQn_t IRQn);
void NVIC_DisableIRQn(IRQn_t IRQn);
#endif

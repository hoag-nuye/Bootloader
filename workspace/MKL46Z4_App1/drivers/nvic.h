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
	IR_PORTCD = 31,
	IR_ADC0 = 15
}IRQn_t;

//------------- Struct -----------//

//================ SUPPORT ================/

//================ FOCUSED ================/

// Configuration control port
void NVIC_EnableIRQn(IRQn_t IRQn);
void NVIC_DisableIRQn(IRQn_t IRQn);
#endif

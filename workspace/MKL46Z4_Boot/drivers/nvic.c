//================ INCLUDE ================/
#include "nvic.h"
#include "MKL46Z4.h"
#include <stdint.h>
//================ DEFINED ================/

//================ SUPPORT ================/

//================ FOCUSED ================/
void NVIC_EnableIRQn(IRQn_t IRQn){
	NVIC->ISER[0U] |= (uint32_t)1U<<IRQn;
};
void NVIC_DisableIRQn(IRQn_t IRQn){
	NVIC->ISER[0U] &= ~(uint32_t)(1U<<IRQn);
};

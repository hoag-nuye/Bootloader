//================ INCLUDE ================/
#include "MKL46Z4.h"
#include <stdint.h>
//================ DEFINED ================/
#ifndef __UART0_H_
#define __UART0_H_


//------------- Enum -----------//
//Define value of fields
//------------- Struct -----------//
typedef struct{
	uint32_t baudrate;
	uint8_t samplingRatio;
}UART0_Config_t;
//================ SUPPORT ================/

//================ FOCUSED ================/
void UART0_Config(UART0_Config_t* uart0_config);
void UART0_TRANSMIT_Enable();
void UART0_TRANSMIT_Disable();
void UART0_TRANSMIT_Data(char data);
void UART0_RECEIVER_Enable();
void UART0_RECEIVER_Disable();
uint8_t UART0_RECEIVER_Data();
// Configuration control port
#endif

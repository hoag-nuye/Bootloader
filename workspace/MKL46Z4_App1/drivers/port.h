//================ INCLUDE ================/
#include "MKL46Z4.h"
#include <stdint.h>
//================ DEFINED ================/
#ifndef __PORT_H_
#define __PORT_H_


//------------- Enum -----------//
//Define value of fields
typedef enum{
	Pull_DISABLE = 0b00,
	Pull_UP = 0b11,
	Pull_DOWN = 0b10
}PullControl_t;

typedef enum{
	 Analog = 0b000,
	 GPIO   = 0b001,
	 Alt2   = 0b010,
	 Alt3   = 0b011,
	 Alt4   = 0b100,
	 Alt5   = 0b101,
	 Alt6   = 0b110,
	 Al7    = 0b111
}MuxControl_t;


typedef enum{
	 Falling_Edge = 0b1010,
	 Rising_Edge = 0b1001,
}Port_Interrupt_t;

typedef enum{
	 PORT_INTERRUPT_NOTdetected= 0b0,
	 PORT_INTERRUPT_detected = 0b1,
}Port_Interrupt_Flag_t;
//------------- Struct -----------//
typedef struct{
	PORT_Type* port;
	uint8_t pin;
	PullControl_t pull;
	MuxControl_t mux;
	Port_Interrupt_t irqc;
}PORT_Config_Type;

//================ SUPPORT ================/

//================ FOCUSED ================/

// Configuration control port
void PORT_PinConfig(PORT_Config_Type* PORT_Config);
void PORT_EXTI_Config(PORT_Config_Type* PORT_Config);
void PORT_EXTI_ClearFlag (PORT_Type* port, uint8_t pin);
Port_Interrupt_Flag_t PORT_Interrupt (PORT_Type* port, uint8_t pin);
#endif

//================ INCLUDE ================/
#include "MKL46Z4.h"
#include <stdint.h>
//================ DEFINED ================/
#ifndef __PIT_H_
#define __PIT_H_


//------------- Enum -----------//
typedef enum {
	PIT_MODULE_ENABLE,
	PIT_MODULE_DISABLE,
}Pit_Module_Disable_t;

typedef enum {
	PIT_TIMER0,
	PIT_TIMER1
}Pit_Channel_t;

//------------- Struct -----------//
typedef struct {
	Pit_Module_Disable_t module;
}Pit_Config_Type;
//================ SUPPORT ================/

//================ FOCUSED ================/

void Pit_Config(Pit_Config_Type* Pit_Config);
void Pit_Timer_Reload(Pit_Channel_t channel, uint16_t timeMs);
void Pit_Timer_Start(Pit_Channel_t channel);
void Pit_Timer_Finish(Pit_Channel_t channel);
#endif

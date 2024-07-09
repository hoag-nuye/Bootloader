//================ INCLUDE ================/
#include "stdint.h"
#include "MKL46Z4.h"
//================ DEFINED ================/
#ifndef __SYSTICK_H_
#define __SYSTICK_H_


//================ SUPPORT ================/
typedef enum{
	Sys_Flag_UnCounted,
	Sys_Flag_Counted,
}SysTick_Flag_t;

typedef enum{
	SysTick_External_Clk,
	SysTick_Processor_Clk
}SysTick_Clk_Srouce_t;

typedef struct{
	SysTick_Clk_Srouce_t clkSrc;
}SysTick_Config_Type;
//================ FOCUSED ================/
//Define value of fields
typedef void (*Handle_SysInterrput_t)();

//------------- Struct -----------//

//================ SUPPORT ================/

//================ FOCUSED ================/

// Configuration control port
void SysTick_Init(SysTick_Config_Type SysTick_Config);
void SysTick_Handle(Handle_SysInterrput_t handle_interrupt);
void SysTick_Reload(uint16_t timeMs);
void SysTick_Enable_Interrput();
void SysTick_Disable_Interrput();
void SysTick_Enable();
void SysTick_Disable();
SysTick_Flag_t SysTick_CountFlag();
void SysTick_ClearFlag();

#endif

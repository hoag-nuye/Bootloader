//================ INCLUDE ================/
#include "systick.h"
#include "MKL46Z4.h"
//================ DEFINED ================/

//================ SUPPORT ================/
static Handle_SysInterrput_t handle_interrupt;

void SysTick_Handler(){
	handle_interrupt();
}
//================ FOCUSED ================/
void SysTick_Init(SysTick_Config_Type SysTick_Config){
	SysTick->CTRL &= ~SysTick_CTRL_CLKSOURCE_Msk;
	SysTick->CTRL |= 1<<SysTick_CTRL_CLKSOURCE_Pos;
};

void SysTick_Handle(Handle_SysInterrput_t _handle_interrupt){
	handle_interrupt = _handle_interrupt;
};

void SysTick_Reload(uint16_t timeMs){
	SystemCoreClockUpdate();
	//Take cycle clock of processor
	uint32_t coreClock = SystemCoreClock;//(MHZ)Clock in arm calculated HZ
	uint32_t N_times = (uint32_t)timeMs * coreClock/1000;
	SysTick->LOAD &= ~SysTick_LOAD_RELOAD_Msk;
	SysTick->LOAD |= N_times -1;

};


void SysTick_Enable(){
	SysTick->CTRL |= ((uint32_t)1<<SysTick_CTRL_ENABLE_Pos) & SysTick_CTRL_ENABLE_Msk;
};
void SysTick_Disable(){
	SysTick->CTRL &= ~((uint32_t)SysTick_CTRL_ENABLE_Msk);
};

//INTERRUPT SYSTICK
void SysTick_Enable_Interrput(){
	SysTick->CTRL |= ((uint32_t)1<<SysTick_CTRL_TICKINT_Pos) & SysTick_CTRL_TICKINT_Msk;
};
void SysTick_Disable_Interrput(){
	SysTick->CTRL &= ~((uint32_t)SysTick_CTRL_TICKINT_Msk);
};

//FLAG SYSTICK
SysTick_Flag_t SysTick_CountFlag(){
	SysTick_Flag_t flag = Sys_Flag_UnCounted;
	if((SysTick->CTRL & ((uint32_t)SysTick_CTRL_COUNTFLAG_Msk)) != 0){
		flag = Sys_Flag_Counted;
	}
	return flag;

};
void SysTick_ClearFlag(){
	SysTick->VAL |= 1U;// Writing to the SYST_CVR
};

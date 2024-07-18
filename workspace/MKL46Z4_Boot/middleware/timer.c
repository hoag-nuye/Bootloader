/*
 * timer.c
 *
 *  Created on: Jul 18, 2024
 *      Author: admin
 */
//================ INCLUDE ================/
#include "stdint.h"
#include "MKL46Z4.h"
#include "timer.h"
#include "systick.h"
#include "pit.h"
#include "clock.h"
#include "nvic.h"
//================ DEFINED ================/
//typedef interrupt function

//================ SUPPORT ================/

static uint16_t numTimeCountSysTick;
//================ FOCUSED ================/
void TIMER_Init(){
	Clock_Enable(CLK_PIT);

	Pit_Config_Type Pit_Config_v = {
			.module = PIT_MODULE_ENABLE,
	};
	Pit_Config(&Pit_Config_v);
	Pit_Timer_Interrupt_Enable(PIT_TIMER);
	NVIC_EnableIRQn(IR_PIT);

	SysTick_Config_Type sysTickConfig = {
		.clkSrc = SysTick_Processor_Clk,
	};
	SysTick_Init(sysTickConfig);
	SystemCoreClockUpdate();
}

void TIMER_WAIT_Sync(uint16_t timeMs){
	uint32_t coreClock = SystemCoreClock;//(MHZ)Clock in arm calculated HZ
	uint32_t N_times = (uint32_t)timeMs * (coreClock/1000);

	numTimeCountSysTick = N_times / 0xFFFFFF; //0xFFFFFF : MAX SysTick Reload value (24bit)

	timeMs = (uint32_t)(0xFFFFFF+1) / (coreClock/1000);
	SysTick_Reload(timeMs);
}

void TIMER_WAIT_Sync_Enable(){

}

void TIMER_WAIT_(){
	SysTick_Enable();
	uint8_t idx;
	for(idx=0; idx<numTimeCountSysTick; idx++){
		while(SysTick_CountFlag() != Sys_Flag_Counted){}
		SysTick_ClearFlag();
	}
	SysTick_Disable();
}


void TIMER_COUNTDOWN_Async(uint16_t timeMs){
	Pit_Timer_Reload(PIT_TIMER, timeMs);
}

void TIMER_COUNTDOWN_Async_Start(){
	Pit_Timer_Start(PIT_TIMER);
}

void TIMER_COUNTDOWN_Async_Stop(){
	Pit_Timer_Finish(PIT_TIMER);
}

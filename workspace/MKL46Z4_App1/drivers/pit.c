//================ INCLUDE ================/
#include "pit.h"
#include "MKL46Z4.h"
#include "driverLib.h"
//================ DEFINED ================/

//================ SUPPORT ================/

static uint32_t timeToReload(uint16_t timeMs){
	uint32_t reloadValue;
	//In Block diagram of the PIT, so the clock powering of PIT from bus
	uint32_t Pit_clock = GetBusClock();
	reloadValue = (uint32_t)timeMs * (Pit_clock / 1000);
	return reloadValue;
}
//================ FOCUSED ================/
void Pit_Config(Pit_Config_Type* Pit_Config){
	PIT->MCR &= ~PIT_MCR_MDIS_MASK;
	PIT->MCR |= PIT_MCR_MDIS(Pit_Config->module);
};
void Pit_Timer_Reload(Pit_Channel_t channel, uint16_t timeMs){
	uint32_t reloadValue = timeToReload(timeMs);
	PIT->CHANNEL[channel].LDVAL &= ~PIT_LDVAL_TSV_MASK;
	PIT->CHANNEL[channel].LDVAL |= PIT_LDVAL_TSV(reloadValue);
};
void Pit_Timer_Start(Pit_Channel_t channel){
	PIT->CHANNEL[channel].TCTRL &= ~PIT_TCTRL_TEN_MASK;
	PIT->CHANNEL[channel].TCTRL |= PIT_TCTRL_TEN(1U);
};
void Pit_Timer_Finish(Pit_Channel_t channel){
	PIT->CHANNEL[channel].TCTRL &= ~PIT_TCTRL_TEN_MASK;
};

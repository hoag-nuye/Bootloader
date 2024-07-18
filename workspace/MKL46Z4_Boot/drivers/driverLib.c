//================ INCLUDE ================/
#include "MKL46Z4.h"
#include "driverLib.h"
//================ FOCUSED ================/
uint32_t GetBusClock(void) {
    // take clock of processor
	SystemCoreClockUpdate();
    uint32_t coreClock = SystemCoreClock;
    uint32_t busClock;

    // Bus clock = coreClock / OUTDIV4
    busClock = coreClock / ((SIM->CLKDIV1 & SIM_CLKDIV1_OUTDIV4_MASK) >> SIM_CLKDIV1_OUTDIV4_SHIFT);

    return busClock;
}

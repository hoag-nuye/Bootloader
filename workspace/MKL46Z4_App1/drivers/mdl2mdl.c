//================ INCLUDE ================/
#include "mdl2mdl.h"
#include "MKL46Z4.h"
//================ DEFINED ================/

//================ SUPPORT ================/

//================ FOCUSED ================/
M2M_Interconnects(M2M_Peripheral_t joinWhich){
	switch(joinWhich){
		case M2M_PIT2ADC:
		//choose timer 0 of PIT and connect to Pre-trigger A of ADC
			SIM->SOPT7 &= ~SIM_SOPT7_ADC0ALTTRGEN_MASK;
			SIM->SOPT7 &= ~SIM_SOPT7_ADC0PRETRGSEL_MASK;
			SIM->SOPT7 &= ~SIM_SOPT7_ADC0TRGSEL_MASK;

			SIM->SOPT7 |= SIM_SOPT7_ADC0ALTTRGEN(1U);
			SIM->SOPT7 |= SIM_SOPT7_ADC0PRETRGSEL(0U);
			SIM->SOPT7 |= SIM_SOPT7_ADC0TRGSEL(0b0100);
			break;
	}
};

//================ INCLUDE ================/
#include "clock.h"
#include "MKL46Z4.h"
//================ DEFINED ================/
#define SYSTEM_IRC_H_CLOCK  4000000U
//================ SUPPORT ================/

//================ FOCUSED ================/
void Clock_Enable(Perhipheral_Name_t name){
	switch (name){
	case CLK_PORTA:
		SIM->SCGC5 |= SIM_SCGC5_PORTA(1);
		break;
	case CLK_PORTB:
		SIM->SCGC5 |= SIM_SCGC5_PORTB(1);
		break;
	case CLK_PORTC:
		SIM->SCGC5 |= SIM_SCGC5_PORTC(1);
		break;
	case CLK_PORTD:
		SIM->SCGC5 |= SIM_SCGC5_PORTD(1);
		break;
	case CLK_PORTE:
		SIM->SCGC5 |= SIM_SCGC5_PORTE(1);
		break;
	case CLK_ADC0:
		SIM->SCGC6 |= SIM_SCGC6_ADC0(1);
		break;
	case CLK_PIT:
		SIM->SCGC6 |= SIM_SCGC6_PIT(1);
		break;
	case CLK_TPM0_MCGIRCLK:
		//IRCLKEN = Active
		MCG->C1 &= ~MCG_C1_IRCLKEN_MASK;
		MCG->C1 |= MCG_C1_IRCLKEN(1);

		SIM->SCGC6 |= SIM_SCGC6_TPM0(1);
		//TPMSRC = MCGIRCLK
		SIM->SOPT2 &= ~SIM_SOPT2_TPMSRC_MASK;
		SIM->SOPT2 |= SIM_SOPT2_TPMSRC(0b11);
		//FCRDIV = 4
		MCG->SC &= ~MCG_SC_FCRDIV_MASK;
		MCG->SC |= MCG_SC_FCRDIV(0b010);
		//CHOOSE IR High CLOCK
		MCG->C2 &= ~MCG_C2_IRCS_MASK;
		MCG->C2 |= MCG_C2_IRCS(1);
		break;
	case CLK_UART0_MCGIRCLK:
		//IRCLKEN = Active
		MCG->C1 &= ~MCG_C1_IRCLKEN_MASK;
		MCG->C1 |= MCG_C1_IRCLKEN(1);

		SIM->SCGC4 |= SIM_SCGC4_UART0(1);
		//UART0SRC = MCGIRCLK
		SIM->SOPT2 &= ~SIM_SOPT2_UART0SRC_MASK;
		SIM->SOPT2 |= SIM_SOPT2_UART0SRC(0b11);
		//FCRDIV = 4
		MCG->SC &= ~MCG_SC_FCRDIV_MASK;
		MCG->SC |= MCG_SC_FCRDIV(0b010);
		//CHOOSE IR High CLOCK
		MCG->C2 &= ~MCG_C2_IRCS_MASK;
		MCG->C2 |= MCG_C2_IRCS(1);
		break;
	}
};


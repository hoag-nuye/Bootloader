//================ INCLUDE ================/
#include "adc.h"
#include "MKL46Z4.h"
//================ DEFINED ================/
//================ SUPPORT ================/

//================ FOCUSED ================/
//ADC Config
void ADC_Config(ADC_Config_Type *ADC_Config){
	//set trigger
	ADC0->SC2 &= ~ADC_SC2_ADTRG_MASK;
	ADC0->SC2 |= ADC_SC2_ADTRG(ADC_Config->trigger);
	//set interrupt
	ADC0->SC1[ADC_Config->sc1Name] &= ~ADC_SC1_AIEN_MASK;
	ADC0->SC1[ADC_Config->sc1Name] |= ADC_SC1_AIEN(ADC_Config->interrupt);
	//set source clock
	ADC0->CFG1 &= ~ADC_CFG1_ADICLK_MASK;
	ADC0->CFG1 |= ADC_CFG1_ADICLK(ADC_Config->srcClock);
	//set voltage
	ADC0->SC2 &= ~ADC_SC2_REFSEL_MASK;
	ADC0->SC2 |= ADC_SC2_REFSEL(ADC_Config->voltage);
	//set continuous
	ADC0->SC3 &= ~ADC_SC3_ADCO_MASK;
	ADC0->SC3 &= ADC_SC3_ADCO(ADC_Config->continuous);
	//set resolutions
	ADC0->CFG1 &= ~ADC_CFG1_MODE_MASK;
	ADC0->CFG1 |= ADC_CFG1_MODE(ADC_Config->resolution);
	//set mode sigle-end or different conversion
	ADC0->SC1[ADC_Config->sc1Name] &= ~ADC_SC1_DIFF_MASK;
	ADC0->SC1[ADC_Config->sc1Name] |= ADC_SC1_DIFF(ADC_Config->mode);
	//set input
	if(ADC_Config->trigger == HARDWARE){
		ADC0->SC1[ADC_Config->sc1Name] &= ~ADC_SC1_ADCH_MASK;
		ADC0->SC1[ADC_Config->sc1Name] |= ADC_SC1_ADCH(ADC_Config->input);
	}
};

//ADC Start conversion trigger
void ADC_Softwarwe_Start(ADC_Input_t input, ADC_SC1n_t inputTrigger){
	ADC0->SC1[inputTrigger] = (ADC0->SC1[inputTrigger] & ~ADC_SC1_ADCH_MASK) + ADC_SC1_ADCH(input);
};

//


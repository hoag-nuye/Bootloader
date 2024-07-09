//================ INCLUDE ================/
#include "tpm.h"
#include "MKL46Z4.h"
#include "driverLib.h"
#include "clock.h"
//================ DEFINED ================/
static TPM_ClockMode_t ClkMode = TPM_CLOCK_DISABLE;
//Get Clock From IR Clock

//================ SUPPORT ================/
static void Channel_Mode_Config(TPM_Type* tpm, uint8_t channel,TPM_ChannelMode_t channelMode){
	switch (channelMode){
	case TPM_EPWM_High_MODE:
		//CPWMS = 0
		tpm->SC &= ~TPM_SC_CPWMS_MASK;
		tpm->SC |= TPM_SC_CPWMS(0U);
		//MSnB:MSnA = [1:0]

		//ELSnB:ELSnA = [1:0]
		// can't configuration this field at time here
		// because When a channel is disabled,
		// this bit will not change state

		/* When switching mode, disable channel first  */
		tpm->CONTROLS[channel].CnSC &=
		~(TPM_CnSC_MSA_MASK | TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK | TPM_CnSC_ELSB_MASK);

		/* Wait till mode change to disable channel is acknowledged */
		while ((tpm->CONTROLS[channel].CnSC &
				(TPM_CnSC_MSA_MASK | TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK | TPM_CnSC_ELSB_MASK)))
		{
		}

		//SET UP MSnB:MSnA = [1:0] ; ELSnB:ELSnA = [1:0]
		tpm->CONTROLS[channel].CnSC |=  TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK;


		/* Wait till mode change is acknowledged */
		while (!(tpm->CONTROLS[channel].CnSC &
				(TPM_CnSC_MSA_MASK | TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK | TPM_CnSC_ELSB_MASK)))
		{
		}

		break;
	}
}


//================ FOCUSED ================/
void TPM_PWM_Config(TPM_PWM_Config_t* tpmConfig){
	ClkMode = tpmConfig->clockMode;

	Channel_Mode_Config(tpmConfig->tpm,tpmConfig->channel, tpmConfig->channelMode);
	};

//TPM PWM ENABLE
void TPM_PWM_Enable(TPM_Type* tpm){
	switch (ClkMode){
	case TPM_CLOCK_DISABLE:
		break;
	case TPM_CLOCK_MODULE:
		//CMOD = 01 and PS = 0 (divide 1)
		//NOTE : PS can be written only when the counter is disabled
		//=> Configuration PS before CMOD in CONFIG function
		tpm->SC &= ~TPM_SC_CMOD_MASK;
		tpm->SC |= TPM_SC_CMOD(0b01);
		break;
	case TPM_CLOCK_EXTERNAL:
		break;
	}
};

//TPM PWM DISABLE
void TPM_PWM_Disable(TPM_Type* tpm){
	switch (ClkMode){
	case TPM_CLOCK_DISABLE:
		break;
	case TPM_CLOCK_MODULE:
		//CMOD = 01 and PS = 0 (divide 1)
		//NOTE : PS can be written only when the counter is disabled
		//=> Configuration PS before CMOD in CONFIG function
		tpm->SC &= ~TPM_SC_CMOD_MASK;
		break;
	case TPM_CLOCK_EXTERNAL:
		break;
	}
};

void TPM_PWM_SetMODValue(TPM_Type* tpm, uint8_t channel, uint16_t freqOfPeriod){
	//Calculate IR CLOCK
	uint32_t tpm_clock = CLK_TPM0_IR;
	//Reset Count value
	tpm->CNT &= ~TPM_CNT_COUNT_MASK;
	//Calculate modulo value by BUS clock and Period
	tpm->MOD = (tpm->MOD & (~TPM_MOD_MOD_MASK)) | TPM_MOD_MOD((uint16_t)(tpm_clock/(uint32_t)freqOfPeriod)-1);
};
void TPM_PWM_SetCOUNTERValue(TPM_Type* tpm, uint8_t channel, uint16_t ratioOfDuty){

	//Calculate count value by BUS clock and ratio Of Duty Cycle with Period
	uint16_t valCounter = (((uint16_t)tpm->MOD)+1)*ratioOfDuty/100;
	tpm->CONTROLS[channel].CnV = (tpm->CONTROLS[channel].CnV & (~TPM_CnV_VAL_MASK)) | TPM_CnV_VAL(valCounter-1);
};

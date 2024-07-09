//================ INCLUDE ================/
#include "MKL46Z4.h"
#include <stdint.h>
//================ DEFINED ================/
#ifndef __TPM_H_
#define __TPM_H_


//------------- Enum -----------//
//Define value of fields
typedef enum {
	TPM_CLOCK_DISABLE,
	TPM_CLOCK_MODULE,
	TPM_CLOCK_EXTERNAL,
}TPM_ClockMode_t;

typedef enum {
	 TPM_EPWM_High_MODE,
}TPM_ChannelMode_t;
//------------- Struct -----------//
typedef struct{
	TPM_Type* tpm;
	TPM_ClockMode_t clockMode;
	uint8_t channel;
	TPM_ChannelMode_t channelMode;
}TPM_PWM_Config_t;
//================ SUPPORT ================/

//================ FOCUSED ================/

// Configuration control port
void TPM_PWM_Config(TPM_PWM_Config_t* tpmConfig);
void TPM_PWM_Enable(TPM_Type* tpm);
void TPM_PWM_Disable(TPM_Type* tpm);
void TPM_PWM_SetMODValue(TPM_Type* tpm, uint8_t channel, uint16_t freqOfPeriod);
void TPM_PWM_SetCOUNTERValue(TPM_Type* tpm, uint8_t channel, uint16_t freqOfDuty);
#endif

//================ INCLUDE ================/
#include "MKL46Z4.h"
#include <stdint.h>
//================ DEFINED ================/
#ifndef __ADC_H_
#define __ADC_H_
#define ADC_RESOLUTION 65535

//------------- Enum -----------//
//Define value of fields
typedef enum{
	SOFTWARE = 0b0,
	HARDWARE = 0b1
}ADC_Trigger_t;

typedef enum{
	DISABLE_IR = 0b0,
	ENABLE_IR = 0b1
}ADC_Interrupt_t;

typedef enum{
	BUS_CLOCK = 0b00,
	BUS_CLOCK_D2 = 0b01,
	ALT_CLOCK = 0b10,
	ASYN_CLOCK = 0b11
}ADC_SourceCLock_t;

typedef enum{
	REF_VOL = 0b00,
	ALT_VOL = 0b01,
}ADC_Voltage_t;

typedef enum{
	DISABLE_CON = 0x0,
	ENABLE_CON = 0x1
}ADC_Continuous_t;

typedef enum{
	I_DP0 = 0b0000,
	I_DP1 = 0b0001,
	I_DP2 = 0b0010,
	I_DP3 = 0b0011,
}ADC_Input_t;


typedef enum{
	MODE_8BIT = 0b00,
	MODE_12BIT = 0b01,
	MODE_10BIT = 0b10,
	MODE_16BIT = 0b11,
}ADC_Resolution_t;

typedef enum{
	SINGLE_END = 0b0,
	DIFFERNTTIAL = 0b1,
}ADC_DifMode_t;

typedef enum{
	ADC_SC1A = 0b0,
	ADC_SC1B = 0b1,
}ADC_SC1n_t;
//------------- Struct -----------//
typedef struct
{
	ADC_SC1n_t sc1Name;
	ADC_Trigger_t trigger;
	ADC_Interrupt_t interrupt;
	ADC_SourceCLock_t srcClock;
	ADC_Voltage_t voltage;
	ADC_Continuous_t continuous;
	ADC_Resolution_t resolution;
	ADC_DifMode_t mode;
	ADC_Input_t input;
}ADC_Config_Type;
//================ SUPPORT ================/

//================ FOCUSED ================/

// Configuration control port
void ADC_Config(ADC_Config_Type *ADC_Config);
void ADC_Softwarwe_Start(ADC_Input_t input, ADC_SC1n_t inputTrigger);
#endif

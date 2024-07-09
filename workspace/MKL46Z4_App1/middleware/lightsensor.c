//================ INCLUDE ================/
#include "lightsensor.h"
#include "MKL46Z4.h"
#include "port.h"
#include "clock.h"
#include "nvic.h"
#include "mdl2mdl.h"
#include "adc.h"
#include "pit.h"
//================ DEFINED ================/
static ADC_Trigger_t triggerADCMode;
static void nullHandlLightSensor(uint32_t _){}
Handle_LightSensor_t handle_LightSensorValue = nullHandlLightSensor;
//================ SUPPORT ================/
static void Config_PTE22_Pin(){
	//Clock port E
	Clock_Enable(CLK_PORTE);
	//ADC pin
	PORT_Config_Type PORT_Config = {
			.port = PORTE,
			.pin = 22,
			.mux = Analog,
	};
	PORT_PinConfig(&PORT_Config);
	//Clock ADC
	Clock_Enable(CLK_ADC0);
	//ADC initial
	ADC_Config_Type ADC0_Config = {
			.sc1Name = ADC_SC1A,
			.trigger = HARDWARE,
			.interrupt = ENABLE_IR,
			.srcClock = BUS_CLOCK,
			.voltage = REF_VOL,
			.continuous = DISABLE_CON,
			.resolution = MODE_16BIT,
			.mode = SINGLE_END,
			.input = I_DP3,
	};
	ADC_Config(&ADC0_Config);
	triggerADCMode = ADC0_Config.trigger;
	//ADC interrupt NVIC
	NVIC_EnableIRQn(IR_ADC0);
	//Clock PIT
	Clock_Enable(CLK_PIT);
	//PIT initial
	Pit_Config_Type Pit_Config_v = {
			.module = PIT_MODULE_ENABLE,
	};
	if(triggerADCMode == HARDWARE){
		Pit_Config(&Pit_Config_v);
		//Set reload
		Pit_Timer_Reload(PIT_TIMER0, 10);//10ms trigger time 1;
		//Module to Module
		M2M_Interconnects(M2M_PIT2ADC);
	}
}



void ADC0_IRQHandler(){
	//read value
	if (PIT->CHANNEL[0].TFLG & PIT_TFLG_TIF_MASK) {
		PIT->CHANNEL[0].TFLG = PIT_TFLG_TIF_MASK; // Clear interrupt flag PIT
	}
	uint16_t valueADC = ADC0->R[ADC_SC1A];
	//return to call back function
	handle_LightSensorValue(valueADC);
}
//================ FOCUSED ================/
void LIGHTSENSOR_Init(LIGHTSENSOR_Name_t name){
	switch (name){
		case Light_sns:
			Config_PTE22_Pin();
		}
};
void LIGHTSENSOR_TurnOn(){
	switch (triggerADCMode){
	case HARDWARE:
		Pit_Timer_Start(PIT_TIMER0);
		break;
	case SOFTWARE:
		break;
	}

};

void LIGHTSENSOR_TurnOff();
void LIGHTSENSOR_Read(Handle_LightSensor_t _handle_LightSensorValue){
	handle_LightSensorValue = _handle_LightSensorValue;
};

//CONVERT ADC VALUE TO VOTAGE
float LIGHTSENSOR_Read2Voltage(uint16_t adcValue){
	// ADC reference voltage
	const float VREF = 3.3;
	// ADC resolution (16-bit)

	// Calculate voltage value
	float voltage = (adcValue / (float)ADC_RESOLUTION) * VREF;
	return voltage;
};
float LIGHTSENSOR_Read2Lux(uint16_t adcValue){
	// LUX = GAIN * voltage + OFFSET
	// LUX = A*Current(I) + B
	//Link explain
	// https://www.canva.com/design/DAGIwkwx_7o/92yCpYLy3BPyWVVuTZeJFg/edit?utm_content=DAGIwkwx_7o&utm_campaign=designshare&utm_medium=link2&utm_source=sharebutton
	float result;

	result = ((((float)adcValue*3.3)/ADC_RESOLUTION - 3.3)/10000)*(180.0/37.0) + 1000.0/37.0;

	return result;
};

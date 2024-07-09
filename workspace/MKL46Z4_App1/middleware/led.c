//================ INCLUDE ================/
#include "MKL46Z4.h"
#include "led.h"
#include "port.h"
#include "gpio.h"
#include "clock.h"
#include "systick.h"
#include "tpm.h"
#include "adc.h"
#include "lightsensor.h"
//================ DEFINED ================/
static uint16_t dataLightSensor;
//HANDLE LIGHSENSOR
static void GetDataLightSensor(uint16_t data){
	dataLightSensor = data;
}
//================ SUPPORT ================/
//CONFIG LED PIN
static void Config_PTD5_Pin(){
	Clock_Enable(CLK_PORTD);
	PORT_Config_Type portConfigD5 = {
			.port = PORTD,
			.pin = 5,
			.mux = GPIO,
	};
	PORT_PinConfig(&portConfigD5);

	GPIO_PinConfig_Type gpioConfigD5 = {
			.gpio = GPIOD,
			.pin = 5,
			.pdd = Direct_Output,
			.data = GPIO_DATA_highLOGIC,
	};
	GPIO_PinConfig(&gpioConfigD5);
}

static void Config_PTE29_Pin(){
	Clock_Enable(CLK_PORTE);
	PORT_Config_Type portConfigE29 = {
			.port = PORTE,
			.pin = 29,
			.mux = GPIO,
	};
	PORT_PinConfig(&portConfigE29);

	GPIO_PinConfig_Type gpioConfigE29 = {
			.gpio = GPIOE,
			.pin = 29,
			.pdd = Direct_Output,
			.data = GPIO_DATA_highLOGIC,
	};
	GPIO_PinConfig(&gpioConfigE29);
}

//Configuration LED Pin with PWM
static void Config_PTE29_PWM_Pin(){
	//Configuration LED2 Pin
	Clock_Enable(CLK_PORTE);
	PORT_Config_Type portConfigE29 = {
			.port = PORTE,
			.pin = 29,
			.mux = Alt3,
	};
	PORT_PinConfig(&portConfigE29);

	//Configuration TPM
	//TPM0_CH2
	Clock_Enable(CLK_TPM0_MCGIRCLK);
	TPM_PWM_Config_t TPM0_PWM_Config = {
			.tpm = TPM0,
			.clockMode = TPM_CLOCK_MODULE,
			.channel = 2,
			.channelMode = TPM_EPWM_High_MODE,
	};
	TPM_PWM_Config(&TPM0_PWM_Config);
	//frequencies lower than 100 Hz may cause visible flicker.
	TPM_PWM_SetMODValue(TPM0, 2, 1000);//1000HZ

	//GET DATA from LIGH_SENSOR
	LIGHTSENSOR_Read(GetDataLightSensor);
}

//TOGGLE LED
static void Toggle_PTD5_Pin(){
	GPIO_TogglePin(GPIOD, 5);
}
static void Toggle_PTE29_Pin(){
	GPIO_TogglePin(GPIOE, 29);
}

//TURN OFF LED
static void Set_PTD5_Pin(){
	GPIO_SetPin(GPIOD, 5);
}
static void Set_PTE29_Pin(){
	GPIO_SetPin(GPIOE, 29);
}

//TURN ON LED
static void Clear_PTD5_Pin(){
	GPIO_ClearPin(GPIOD, 5);
}
static void Clear_PTE29_Pin(){
	GPIO_ClearPin(GPIOE, 29);
}


//TURN ON LED2 WITH TAKING DATA FROM LIGHSENSOR
static void Enable_PTE29_LighSNS_Pin(){
	//CONVERT DATA LIGHTSENOR TO VOTAGE
	float votageValue = LIGHTSENSOR_Read2Voltage(dataLightSensor);

	uint8_t ratio = (votageValue / 3.3)*100;

	//TRANSMIT DATA from LIGH_SENSOR to PWM
	TPM_PWM_SetCOUNTERValue(TPM0, 2, ratio);//50%
	TPM_PWM_Enable(TPM0);

}

//TURN OFF LED2 WITH TAKING DATA FROM LIGHSENSOR
static void Disable_PTE29_LighSNS_Pin(){

	TPM_PWM_Disable(TPM0);

}

//CONVERT
//================ FOCUSED ================/
//LED Initial
void LED_Init(LED_Name_t name){
	switch (name){
	case LED1:
		Config_PTD5_Pin();
		break;
	case LED2:
		Config_PTE29_Pin();
		break;
	case LED2_LighSNS:
		Config_PTE29_PWM_Pin();
		break;
	}
};

//Toggle led
void Toggle_LED(LED_Name_t name){
	switch (name){
	case LED1:
		Toggle_PTD5_Pin();
		break;
	case LED2:
		Toggle_PTE29_Pin();
		break;
	case LED2_LighSNS:
		break;
	}
};

//Turn_OFF LED
void TurnOff_LED(LED_Name_t name){
	switch (name){
	case LED1:
		Set_PTD5_Pin();
		break;
	case LED2:
		Set_PTE29_Pin();
	case LED2_LighSNS:
		Disable_PTE29_LighSNS_Pin();
		break;
	}
//Turn_ON LED
};
void TurnOn_LED(LED_Name_t name){
	switch (name){
	case LED1:
		Clear_PTD5_Pin();
		break;
	case LED2:
		Clear_PTE29_Pin();
		break;
	case LED2_LighSNS:
		Enable_PTE29_LighSNS_Pin();
		break;
	}
};

void Flash_LED_Timer(LED_Name_t name, uint8_t times,uint16_t timeMs){
	SysTick_Config_Type sysTickConfig = {
			.clkSrc = SysTick_Processor_Clk,
	};
	SysTick_Init(sysTickConfig);
	SysTick_Reload(timeMs);
	uint8_t idx;
	for (idx = 0; idx <times*2; idx++){
		SysTick_Enable();
		while(SysTick_CountFlag() != Sys_Flag_Counted){}
		Toggle_LED(name);
		SysTick_ClearFlag();
		SysTick_Disable();
	}
};

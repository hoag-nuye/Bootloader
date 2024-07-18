//================ INCLUDE ================/
#include "MKL46Z4.h"
#include "led.h"
#include "port.h"
#include "gpio.h"
#include "clock.h"
#include "systick.h"
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
	}
};

void Flash_LED_Timer(LED_Name_t name, uint8_t times,uint16_t timeMs){
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

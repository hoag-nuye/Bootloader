//================ INCLUDE ================/
#include "stdint.h"
#include "MKL46Z4.h"
#include "button.h"
#include "port.h"
#include "gpio.h"
#include "clock.h"
#include "nvic.h"
//================ DEFINED ================/
//typedef interrupt function

Handle_Button_t handleButtonFunc;

//================ SUPPORT ================/
//CONFIG BUTTON PIN
//SW1
static void Config_PTC3_Pin(){
	Clock_Enable(CLK_PORTC);
	PORT_Config_Type portConfig = {
			.port = PORTC,
			.pin = 3,
			.mux = GPIO,
			.pull = Pull_UP,
			.irqc = Falling_Edge,
	};
	PORT_PinConfig(&portConfig);

	//set interrupt
	PORT_EXTI_Config(&portConfig);

	//enable interrupt on NVIC
	NVIC_EnableIRQn(IR_PORTCD);

	GPIO_PinConfig_Type gpioConfig = {
			.gpio = GPIOC,
			.pin = 3,
			.pdd = Direct_Input,
	};
	GPIO_PinConfig(&gpioConfig);
}

//SW2
static void Config_PTC12_Pin(){
	Clock_Enable(CLK_PORTC);
	PORT_Config_Type portConfig = {
			.port = PORTC,
			.pin = 12,
			.mux = GPIO,
			.pull = Pull_UP,
			.irqc = Falling_Edge,
	};
	PORT_PinConfig(&portConfig);

	PORT_EXTI_Config(&portConfig);

	NVIC_EnableIRQn(IR_PORTCD);

	GPIO_PinConfig_Type gpioConfig = {
			.gpio = GPIOC,
			.pin = 12,
			.pdd = Direct_Input,
	};
	GPIO_PinConfig(&gpioConfig);
}



//
void PORTC_PORTD_IRQHandler(){

	//sw1 detected interrupt
	if(PORT_Interrupt(PORTC, 3) == PORT_INTERRUPT_detected){
		handleButtonFunc(SW1);
		PORT_EXTI_ClearFlag(PORTC, 3);
	}
	//sw2 detected interrupt
	if(PORT_Interrupt(PORTC, 12) == PORT_INTERRUPT_detected){
		PORT_EXTI_ClearFlag(PORTC, 12);
		handleButtonFunc(SW2);
	}
}

//================ FOCUSED ================/
void BUTTON_Init(BUTTON_Name_t name){
	switch (name) {
	case SW1:
		Config_PTC3_Pin();
		break;
	case SW2:
		Config_PTC12_Pin();
		break;
	}
};
void Read_BUTTON(Handle_Button_t handle_interrupt){
	handleButtonFunc = handle_interrupt;
};

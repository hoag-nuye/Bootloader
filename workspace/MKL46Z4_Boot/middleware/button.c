//================ INCLUDE ================/
#include "stdint.h"
#include "MKL46Z4.h"
#include "button.h"
#include "port.h"
#include "gpio.h"
#include "clock.h"
#include "nvic.h"
#include "pit.h"
//================ DEFINED ================/
//typedef interrupt function
static uint8_t isSuccessHold;

static Handle_Button_t handleButtonFunc;

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
			.irqc = Either_Edge,
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

/*INTERRUPT PIT*/
void PIT_IRQHandler(){
	isSuccessHold = 1;
	//clear flag
	PIT->CHANNEL[PIT_TIMER0].TFLG |= PIT_TFLG_TIF(0b1);

	//disable interrupt
	Pit_Timer_Interrupt_Disable(PIT_TIMER0);
}


/*INTERRUPT SWITCH*/
void PORTC_PORTD_IRQHandler(){

	//sw1 detected interrupt
	if(PORT_Interrupt(PORTC, 3) == PORT_INTERRUPT_detected){
		handleButtonFunc(SW1);
		PORT_EXTI_ClearFlag(PORTC, 3);
	}
	//sw2 detected interrupt when button is hold the button
	if((PORT_Interrupt(PORTC, 12) == PORT_INTERRUPT_detected) && (GPIO_ReadPin(GPIOC, 12) == GPIO_DATA_lowLOGIC)){
		PORT_EXTI_ClearFlag(PORTC, 12);
		handleButtonFunc(SW2_Hold);
	}
	//sw2 detected interrupt when button is release the button (1->0)
	if((PORT_Interrupt(PORTC, 12) == PORT_INTERRUPT_detected) && (GPIO_ReadPin(GPIOC, 12) == GPIO_DATA_highLOGIC)){
			PORT_EXTI_ClearFlag(PORTC, 12);
			handleButtonFunc(SW2_Release);
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

uint8_t BUTTON_SUCCESS_HOLD(){
	uint8_t status = 0;
	if(isSuccessHold){
		status = 1;
	}
	return status;
}

void BUTTON_RESET(){
	Port_Reset_Pin(PORTC, 12);
}

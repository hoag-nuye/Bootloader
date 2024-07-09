//================ INCLUDE ================/
#include "MKL46Z4.h"
#include "interface.h"
//================ DEFINED ================/
//================ SUPPORT ================/

State_Mode_t stateMode;

typedef enum{
	MACHINE_DO_NOTHING,
	MACHINE_TOGGLE_LED,
	MACHINE_LIGHT_SENSOR_LED,
	MACHINE_LIGHR_SENSOR_UART,
}State_Machine_t;


static State_Machine_t state = MACHINE_DO_NOTHING;
//handle button
static void handleButton(BUTTON_Name_t name){
	switch (name){
	case SW1:
		switch (stateMode){
		case MODE_START_UP:
			break;

		case MODE_BUTTON_LED:
			if(state == MACHINE_DO_NOTHING){
				state = MACHINE_TOGGLE_LED;
			}
			break;

		case MODE_LIGHTSENSOR_LED:
			if(state == MACHINE_DO_NOTHING){
				state = MACHINE_LIGHT_SENSOR_LED;
			}else{
				state = MACHINE_DO_NOTHING;
			}
			break;

		case MODE_LIGHTSENSOR_USB_COMMS:
			if(state == MACHINE_DO_NOTHING){
				state = MACHINE_LIGHR_SENSOR_UART;
			}else{
				state = MACHINE_DO_NOTHING;
			}
			break;
		}
		break;

	case SW2:
		switch(stateMode){
		case MODE_START_UP:
			stateMode = MODE_BUTTON_LED;
			break;
		case MODE_BUTTON_LED:
			stateMode = MODE_LIGHTSENSOR_LED;
			break;
		case MODE_LIGHTSENSOR_LED:
			stateMode = MODE_LIGHTSENSOR_USB_COMMS;
			break;
		case MODE_LIGHTSENSOR_USB_COMMS:
			stateMode = MODE_START_UP;
			break;
		}
		break;
	}
};


//================ FOCUSED ================/
void APP_Init(){
	BUTTON_Init(SW1);
	BUTTON_Init(SW2);
	LED_Init(LED1);
	LED_Init(LED2);
	Read_BUTTON(handleButton);
	stateMode = MODE_START_UP;
}
void App_Sleep(){
	TurnOff_LED(LED1);
}

void BUTTON_LED(){
	//BLINKING LED 1 times
	TurnOff_LED(LED1);
	LED_Init(LED2);
	Flash_LED_Timer(LED2, 1, 200);

	state = MACHINE_DO_NOTHING;
	while(stateMode == MODE_BUTTON_LED){
		switch (state){
		case MACHINE_DO_NOTHING:
			break;
		case MACHINE_TOGGLE_LED:
			Toggle_LED(LED1);
			Flash_LED_Timer(LED2, 3, 200);
			state = MACHINE_DO_NOTHING;
			break;
		}
	}

};

void LIGHTSENSOR_LED(){
	//BLINKING LED 2 times
	TurnOff_LED(LED1);
	LED_Init(LED2);
	Flash_LED_Timer(LED2, 2, 200);


	LED_Init(LED2_LighSNS);
	LIGHTSENSOR_Init(Light_sns);
	LIGHTSENSOR_TurnOn();

	state = MACHINE_DO_NOTHING;
	while(stateMode == MODE_LIGHTSENSOR_LED){
		switch (state){
		case MACHINE_DO_NOTHING:
			TurnOff_LED(LED1);
			TurnOff_LED(LED2_LighSNS);
			break;
		case MACHINE_LIGHT_SENSOR_LED:
			Toggle_LED(LED1);
			TurnOn_LED(LED2_LighSNS);

			if(state == MACHINE_DO_NOTHING){
				break;
			}
			state = MACHINE_LIGHT_SENSOR_LED;
			break;
		}
	}
};

void LIGHTSENSOR_USB_COMMS(){
	char data[] = "Hello World";
	USB_Init(USB_MODE_UART);
	uint8_t timeSendData = 1;

	//BLINKING LED 3 times
	TurnOff_LED(LED1);
	LED_Init(LED2);
	Flash_LED_Timer(LED2, 3, 200);


	state = MACHINE_DO_NOTHING;
	while(stateMode == MODE_LIGHTSENSOR_USB_COMMS){
		switch (state){
			case MACHINE_DO_NOTHING:
				TurnOff_LED(LED1);
				USB_Disconnect();
				timeSendData = 1;
				break;
			case MACHINE_LIGHR_SENSOR_UART:

				Toggle_LED(LED1);
				while(timeSendData <= 1){
					USB_SEND_DATA(data);
					timeSendData++;
				}

				if(state == MACHINE_DO_NOTHING){
					break;
				}
				state = MACHINE_LIGHR_SENSOR_UART;
				break;
		}

	}

};

//================ INCLUDE ================/
#include <stdint.h>
#include "led.h"
#include "button.h"
#include "lightsensor.h"
#include "usb.h"
//================ DEFINED ================/
#ifndef __INTERFACE_H_
#define __INTERFACE_H_


//------------- Enum -----------//
//Define value of fields


typedef enum{
	MODE_START_UP,
	MODE_BUTTON_LED,
	MODE_LIGHTSENSOR_LED,
	MODE_LIGHTSENSOR_USB_COMMS,
}State_Mode_t;

//------------- Struct -----------//
extern State_Mode_t stateMode;
//================ SUPPORT ================/

//================ FOCUSED ================/
void APP_Init();
void BUTTON_LED();
void LIGHTSENSOR_LED();
void LIGHTSENSOR_USB_COMMS();
#endif

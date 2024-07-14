//================ INCLUDE ================/
#include "MKL46Z4.h"
#include <stdint.h>

//================ DEFINED ================/
#ifndef __USB_H_
#define __USB_H_


//------------- Enum -----------//
//Define value of fields
//------------- Struct -----------//
//================ SUPPORT ================/

//================ FOCUSED ================/
void USB_Init();
void USB_SetupComms();
uint8_t USB_GetNumberLineSREC();
//void USB_Receive_Data();
//void USB_Transmit_Data();
// Configuration control port
#endif

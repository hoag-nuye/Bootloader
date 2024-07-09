//================ INCLUDE ================/
#include "MKL46Z4.h"
#include <stdint.h>

//================ DEFINED ================/
#ifndef __USB_H_
#define __USB_H_


//------------- Enum -----------//
//Define value of fields
typedef enum{
	USB_MODE_UART
}USB_Mode_t;
//------------- Struct -----------//

//================ SUPPORT ================/

//================ FOCUSED ================/
void USB_Init(USB_Mode_t usbMode);
void USB_SEND_DATA(char* data);
void USB_Disconnect();
#endif

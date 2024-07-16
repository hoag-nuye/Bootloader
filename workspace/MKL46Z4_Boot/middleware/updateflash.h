//================ INCLUDE ================/
#include "MKL46Z4.h"
#include <stdint.h>

//================ DEFINED ================/
#ifndef __FLASH_H_
#define __FLASH_H_


//------------- Enum -----------//
typedef enum{
	FLASH_LOAD_Blocked,
	FLASH_LOAD_Unlock,
	FLASH_LOAD_Loading,
	FLASH_LOAD_Done,
	FLASH_LOAD_Discontinuous,
	FLASH_LOAD_DataError,
}FLASH_LOAD_Status_t;
//Define value of fields
//------------- Struct -----------//
//================ SUPPORT ================/

//================ FOCUSED ================/
void FLASH_TransmitTEST();
//void USB_Receive_Data();
//void USB_Transmit_Data();
FLASH_LOAD_Status_t FLASH_LOAD_USB2FLASH();
#endif

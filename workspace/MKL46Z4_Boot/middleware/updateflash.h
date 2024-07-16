//================ INCLUDE ================/
#include "MKL46Z4.h"
#include <stdint.h>

//================ DEFINED ================/
#ifndef __FLASH_H_
#define __FLASH_H_


//------------- Enum -----------//
typedef enum{
	FLASH_LOAD_Loading,
	FLASH_LOAD_Done,
	FLASH_LOAD_Error,
}FLASH_LOAD_Status_t;
//Define value of fields
//------------- Struct -----------//
typedef struct{
	FLASH_LOAD_Status_t status;
	uint32_t sizeData;
}FLASH_LOAD_API_t;
//================ SUPPORT ================/

//================ FOCUSED ================/
void FLASH_TransmitTEST();
//void USB_Receive_Data();
//void USB_Transmit_Data();
FLASH_LOAD_API_t *FLASH_LOAD_USB2FLASH();
uint8_t FLASH_CheckEmpty(uint32_t addr);
#endif

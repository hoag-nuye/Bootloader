//================ INCLUDE ================/
#include "usb.h"
#include "updateflash.h"
#include "MKL46Z4.h"
#include "interface.h"
#include "uart0.h"
#include "ftfa.h"
//================ DEFINED ================/
//Get Clock From IR Clock

//================ SUPPORT ================/

//================ FOCUSED ================/
void Bootloader_Init(){
	USB_Init();
	USB_SetupComms();

	FLASH_LOAD_Status_t FL_Status = FLASH_LOAD_USB2FLASH();


//	FTFA_EraseSector(0x10000);
//	FLASH_TransmitALineSrec();
//	FLASH_TransmitTEST();
};

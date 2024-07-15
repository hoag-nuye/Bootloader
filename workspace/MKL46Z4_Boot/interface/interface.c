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
//	FTFA_EraseSector(0x10000);
	FLASH_SrecLineValidate();
//	FLASH_TransmitALineSrec();
//	FLASH_TransmitTEST();
};

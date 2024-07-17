//================ INCLUDE ================/
#include "usb.h"
#include "updateflash.h"
#include "MKL46Z4.h"
#include "interface.h"
#include "uart0.h"
#include "ftfa.h"
#include "config.h"
//================ DEFINED ================/
//Get Clock From IR Clock

//================ SUPPORT ================/

//================ FOCUSED ================/
void Bootloader(){
	USB_Init();
	USB_SetupComms();

//	FTFA_EraseSector(FLASH_ADDRESS_APP1_LSB);

/*DONE LOAD*/
//	FTFA_EraseMultiSector(FLASH_ADDRESS_APP1_LSB, FLASH_ADDRESS_APP1_MSB);
//	FLASH_LOAD_API_t *FLApi = FLASH_LOAD_USB2FLASH();

	USB_Disconnect();
/***********/

/*JUMP APP*/
	FLASH_Jump2Firmware(FLASH_ADDRESS_APP1_LSB);
/***********/

//	FTFA_EraseMultiSector();
//	FLASH_TransmitALineSrec();
//	FLASH_TransmitTEST();
};

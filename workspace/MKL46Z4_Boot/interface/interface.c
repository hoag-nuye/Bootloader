//================ INCLUDE ================/
#include "usb.h"
#include "MKL46Z4.h"
#include "interface.h"
#include "uart0.h"
//================ DEFINED ================/
//Get Clock From IR Clock

//================ SUPPORT ================/

//================ FOCUSED ================/
void Bootloader_Init(){
	USB_Init();
	USB_TransmitTEST();
};

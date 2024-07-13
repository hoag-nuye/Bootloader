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
	// Receive data
	UART0_RECEIVER_Enable();
	UART0_TRANSMIT_Enable();
	uint8_t idx;
//	uint8_t x[45] = {'S','1','1','3','0','0','0','0','0','0','6','0','0','0','2','0','D','5','0','0','0','0','0','0','4','3','0','1','0','0','0','0','4','5','0','1','0','0','0','0','0','D'};
	while(1){
//		if(s == 3)
//		for(idx =0; idx< 45; idx++){
//			UART0_TRANSMIT_Data(x[idx]);
//		}
		if(numberData == 3){
			for(idx =0; idx< 125; idx++){
				UART0_TRANSMIT_Data(data[0].line[idx]);
			}
			numberData++;
		}
	}
};

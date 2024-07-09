//================ INCLUDE ================/
#include "usb.h"
#include "MKL46Z4.h"
#include "uart0.h"
#include "clock.h"
//================ DEFINED ================/

//================ SUPPORT ================/
static void Config_USB_UART0(){
	Clock_Enable(CLK_UART0_MCGIRCLK);
	UART0_Config_t uart0Config = {
			.baudrate = 9600,
			.samplingRatio = 4,
	};
	UART0_Config(&uart0Config);
};
//================ FOCUSED ================/
void USB_Init(USB_Mode_t usbMode){
	switch (usbMode){
	case USB_MODE_UART:
		Config_USB_UART0();
	}
};

//disconnect
void USB_Disconnect(){
	UART0_TRANSMIT_Disable();
}

void USB_SEND_DATA(char* data){
	UART0_TRANSMIT_Enable();
	uint8_t idx = 0;
	while(data[idx] != '\0'){
		UART0_TRANSMIT_Data(data[idx]);
		idx++;
	}
};

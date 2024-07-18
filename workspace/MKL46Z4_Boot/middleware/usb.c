//================ INCLUDE ================/
#include "usb.h"
#include "MKL46Z4.h"
#include "port.h"
#include "nvic.h"
#include "uart0.h"
#include "clock.h"
#include "queue.h"
#include "srecfile.h"
//================ DEFINED ================/
#define NULL ((void *)0)
//================ SUPPORT ================/


//================ SUPPORT ================/

//================ FOCUSED ================/
void USB_Init(){
	//CONFIG USB PIN TO PTA1 - PTA2
	//Enable clock PORTA

	Clock_Enable(CLK_PORTA);
	/*PTA1 */
	PORT_Config_Type portConfig_PTA1 = {
			.port = PORTA,
			.pin = 1,
			.mux = Alt2,
			.pull = Pull_UP,
	};
	PORT_PinConfig(&portConfig_PTA1);

	/*PTA2 */
	PORT_Config_Type portConfig_PTA2 = {
				.port = PORTA,
				.pin = 2,
				.mux = Alt2,
				.pull = Pull_UP,
		};
		PORT_PinConfig(&portConfig_PTA2);

	//Clock UART
	Clock_Enable(CLK_UART0_MCGIRCLK);
	//NVIC interrupt uart0
	NVIC_EnableIRQn(IR_UART0);

	//Configuration UART0
	UART0_Config_t uart0_config = {
		.baudrate = 56000,
		.samplingRatio = 16,
	};
	UART0_Config(&uart0_config);

	/*DISABLE INTERRUPT*/
	//PORTC_D
	NVIC_DisableIRQn(IR_PORTCD);
	//PIT
	NVIC_DisableIRQn(IR_PIT);

};

//void USB_SetupComms(){
//	UART0_RECEIVER_Enable();
//	UART0_TRANSMIT_Enable();
//}


/*===========HEAP ISSUE =============*/
void USB_SetupComms(){
	QUEUE_Init(SREC_LINE_LEN_MAX);
	UART0_RECEIVER_Enable();
	UART0_TRANSMIT_Enable();
}

/*======================================*/

USB_Disconnect(){
	UART0_RECEIVER_Disable();
	UART0_TRANSMIT_Disable();
}
//uint32_t USB_GetNumberLineSREC(){
//	return numberData;
//}



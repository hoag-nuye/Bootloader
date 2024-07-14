//================ INCLUDE ================/
#include "usb.h"
#include "MKL46Z4.h"
#include "port.h"
#include "nvic.h"
#include "uart0.h"
#include "clock.h"
#include "queue.h"
//================ DEFINED ================/
#define NULL ((void *)0)
static uint8_t lineSrecData[125];
static uint8_t numberChar = 0;
static uint8_t numberData = 0;
//================ SUPPORT ================/
void UART0_IRQHandler(){
	lineSrecData[numberChar] = UART0_RECEIVER_Data();

	if((lineSrecData[numberChar] == '\n') && (lineSrecData[numberChar-1] == '\r')){
		numberData++;
		numberChar = 0;
		QUEUE_Push(lineSrecData);
	}else{
		numberChar++;
	}
};
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
		.baudrate = 9600,
		.samplingRatio = 16,
	};
	UART0_Config(&uart0_config);
};

void USB_TransmitTEST(){
		// Receive data
		UART0_RECEIVER_Enable();
		UART0_TRANSMIT_Enable();
		QUEUE_Init(sizeof(lineSrecData));
		uint8_t idx;
	//	uint8_t x[45] = {'S','1','1','3','0','0','0','0','0','0','6','0','0','0','2','0','D','5','0','0','0','0','0','0','4','3','0','1','0','0','0','0','4','5','0','1','0','0','0','0','0','D'};
		while(1){
	//		if(s == 3)
	//		for(idx =0; idx< 45; idx++){
	//			UART0_TRANSMIT_Data(x[idx]);
	//		}
			if(numberData == 3){
				uint8_t *data = (uint8_t *)QUEUE_Pop();
				if (data != NULL) {
					for(idx =0; idx< 125; idx++){
						UART0_TRANSMIT_Data(data[idx]);
					}
					numberData++;
				}
			}
		}
}


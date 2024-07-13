//================ INCLUDE ================/
#include "usb.h"
#include "MKL46Z4.h"
#include "port.h"
#include "nvic.h"
#include "uart0.h"
#include "clock.h"
//================ DEFINED ================/
typedef struct{
	uint8_t line[125];
}Data_t;
Data_t data[3] = {0};
uint8_t numberChar = 0;
uint8_t numberData = 0;
//================ SUPPORT ================/
void UART0_IRQHandler(){
	data[numberData].line[numberChar] = UART0_RECEIVER_Data();

	if((data[numberData].line[numberChar] == '\n') && (data[numberData].line[numberChar-1] == '\r')){
		numberData++;
		numberChar = 0;
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

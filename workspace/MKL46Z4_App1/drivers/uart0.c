//================ INCLUDE ================/
#include "uart0.h"
#include "MKL46Z4.h"
#include "clock.h"
#include "port.h"
//================ DEFINED ================/
//Get Clock From IR Clock

//================ SUPPORT ================/

//================ FOCUSED ================/
void UART0_Config(UART0_Config_t* uart0_config){
	//Disable UART
	 UART0->C2 &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK);
	/*Update over sampling ratio */
	UART0->C4 = (UART0->C4 & (~UART0_C4_OSR_MASK)) | ((uint8_t)uart0_config->samplingRatio-1);
	//SETUP BAUD RATE DIVISOR
	uint16_t brDiv = (uint32_t)CLK_UART0_IR/((uart0_config->samplingRatio)*uart0_config->baudrate);

	uint8_t brDivHigh = brDiv>>8;
	uint8_t brDivLow = (uint8_t)brDiv;

	UART0->BDH &= ~UART0_BDH_SBR_MASK;
	UART0->BDH |= UART0_BDH_SBR(brDivHigh);

	UART0->BDL &= ~UART0_BDL_SBR_MASK;
	UART0->BDL |= UART0_BDL_SBR(brDivLow);

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


};
void UART0_TRANSMIT_Enable(){;
	//UARTx_C2[TE]=1
	UART0->C2 &= ~UART0_C2_TE_MASK;
	UART0->C2 |= UART_C2_TE(1U);
};

void UART0_TRANSMIT_Disable(){
	UART0->C2 &= ~UART0_C2_TE_MASK;
};

void UART0_TRANSMIT_Data(char data){
	//wait data buffer empty : S1[TDRE]
	while(!((UART0->S1 & UART0_S1_TDRE_MASK)>>UART0_S1_TDRE_SHIFT)){}

	UART0->D = data;
};

//================ INCLUDE ================/
#include "uart0.h"
#include "clock.h"
#include "MKL46Z4.h"
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

void UART0_RECEIVER_Enable(){
	UART0->C2 &= ~UART0_C2_RE_MASK;
	UART0->C2 |= UART_C2_RE(1U);
	//Enable interrupt
	UART0->C2 &= ~UART0_C2_RIE_MASK;
	UART0->C2 |= UART_C2_RIE(1U);
};
void UART0_RECEIVER_Disable(){
	UART0->C2 &= ~UART0_C2_RE_MASK;
	UART0->C2 &= ~UART0_C2_RIE_MASK;
};
uint8_t UART0_RECEIVER_Data(){
	while (((UART0->S1 & UART0_S1_RDRF_MASK)==0));
	return UART0->D;
};

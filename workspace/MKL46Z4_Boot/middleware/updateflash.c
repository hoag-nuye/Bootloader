
//================ INCLUDE ================/
#include "usb.h"
#include "MKL46Z4.h"
#include "port.h"
#include "nvic.h"
#include "uart0.h"
#include "clock.h"
#include "queue.h"
#include "srecfile.h"
#include "ftfa.h"
//================ DEFINED ================/
#define NULL ((void *)0)


static SREC_API_t *dataSREC;
//================ SUPPORT ================/
static void FLASH_ProgarmWord(){
	uint8_t idx;
	for(idx=0; idx<dataSREC->srec_data_len; idx+=4){
		uint32_t dataFlash = *((uint32_t *)&(dataSREC->srec_data[idx]));
		uint32_t addressFlash = dataSREC->srec_addr+idx;
		if(addressFlash > 0x410){
			FTFA_ProgramWord(addressFlash, dataFlash);
		}
	}
//	FTFA_ProgramWord(uint32_t address, uint32_t data);
}
//================ FOCUSED ================/
//
void FLASH_SrecLineValidate(){
	uint8_t *data;
	SREC_API_t *srecStatus;
		while(1){
			if(USB_GetNumberLineSREC() == 4){
			data = (uint8_t *)QUEUE_Pop();
			if (data != NULL) {
				srecStatus = (SREC_API_t *)SREC_ApiGetData(data, SREC_LINE_LEN_MAX, '\n');
				if(srecStatus->status == SREC_TRUE){
					dataSREC = srecStatus;
					FLASH_ProgarmWord();
				}
			}}
	}
}

//TEST GET DATA FROM SREC LINE
void FLASH_TransmitALineSrec(){
		// Receive data

	uint8_t *data;
	SREC_API_t *srecStatus;
	uint8_t i;
		while(1){
			data = (uint8_t *)QUEUE_Pop();
			if (data != NULL) {
				for(i =0; i< SREC_LINE_LEN_MAX; i++){
						UART0_TRANSMIT_Data(data[i]);
					}
				UART0_TRANSMIT_Data('W');
			}
		}
}



//TEST GET DATA FROM SREC LINE
void FLASH_TransmitTEST(){
		// Receive data

	uint8_t *data;
	SREC_API_t *srecStatus;
		while(1){
			data = (uint8_t *)QUEUE_Pop();
			if (data != NULL) {
				srecStatus = (SREC_API_t *)SREC_ApiGetData(data, SREC_LINE_LEN_MAX, '\n');
				if(srecStatus->status == SREC_TRUE){
					uint8_t i;
					uint8_t j;
					for(i =0; i< srecStatus->srec_addr_len; i++){
							UART0_TRANSMIT_Data(srecStatus->srec_addr);
					}
							UART0_TRANSMIT_Data('W');
					for(j =0; j< srecStatus->srec_data_len; j++){
							UART0_TRANSMIT_Data(srecStatus->srec_data[j]);
					}
							UART0_TRANSMIT_Data('w');
							UART0_TRANSMIT_Data('z');
				}
			}
		}
}

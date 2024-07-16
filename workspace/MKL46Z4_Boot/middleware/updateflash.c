
//================ INCLUDE ================/
#include "usb.h"
#include "updateflash.h"
#include "MKL46Z4.h"
#include "port.h"
#include "nvic.h"
#include "uart0.h"
#include "clock.h"
#include "queue.h"
#include "srecfile.h"
#include "ftfa.h"
#include "config.h"
//================ DEFINED ================/
#define NULL ((void *)0)

static SREC_API_t *dataSREC_First;
//================ SUPPORT ================/
static uint8_t FLASH_CheckEmptyAddr(uint32_t addr){
	uint8_t status = 0;
	uint32_t *ptrAddr = (uint32_t *)addr;
	if(*ptrAddr == 0xFFFFFFFF){
		status = 1;
	}
	return status;
}
static void FLASH_ProgarmWord(SREC_API_t *dataSREC){
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
/*LOAD DATA TO FLASH and return status
 *Status
 *Blocked : FLash not empty
 *Done : Flash contains the final information of the data file
 *Discontinuous : - Flash NOT contains the final
 *				information of the data file
 *				&
 *				  -Did not receive information
 *				for a period of time ()
 *DataError : Error when receiving data*/

FLASH_LOAD_Status_t FLASH_LOAD_USB2FLASH(){
	uint8_t *data;
	SREC_API_t *srecAPI;
	FLASH_LOAD_Status_t loadStatus = FLASH_LOAD_Loading;
	while(loadStatus == FLASH_LOAD_Loading){
		/*Check address first of data is valid*/
		if(USB_GetNumberLineSREC() == 2){
			data = (uint8_t *)QUEUE_Get(2);
			srecAPI = (SREC_API_t *)SREC_ApiGetData(data, SREC_LINE_LEN_MAX, '\n');
			if(srecAPI->status == SREC_TRUE){
				if((srecAPI->srec_addr == FLASH_ADDRESS_APP1) &&
					FLASH_CheckEmptyAddr(FLASH_ADDRESS_APP1)){
					loadStatus = FLASH_LOAD_Unlock;
				}else{
					loadStatus = FLASH_LOAD_Blocked;
					//Disable UART0
					UART0_RECEIVER_Disable();
				}
			}
		}

		/*LOAD DATA when the flash is unlocked*/
		if(loadStatus == FLASH_LOAD_Unlock){
			/*Take first line SREC and erase flash*/
			data = (uint8_t *)QUEUE_Pop();
			dataSREC_First = (SREC_API_t *)SREC_ApiGetData(data, SREC_LINE_LEN_MAX, '\n');

			if(USB_GetNumberLineSREC() == 4){
				data = (uint8_t *)QUEUE_Pop();
				if (data != NULL) {
					srecAPI = (SREC_API_t *)SREC_ApiGetData(data, SREC_LINE_LEN_MAX, '\n');
					if(srecAPI->status == SREC_TRUE){
						FLASH_ProgarmWord(srecAPI);
					}
					else if(srecAPI->status == SREC_Termination_DATA){
						FLASH_ProgarmWord(dataSREC_First);
						loadStatus = FLASH_LOAD_Done;
					}
				}
			}
		}

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

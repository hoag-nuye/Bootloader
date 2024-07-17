
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
static uint32_t interruptState;
static volatile SREC_API_t dataSREC_First;
//================ SUPPORT ================/
/* Disable all interrupts and save their state*/
static void disableInterrupts(void) {
    interruptState = __get_PRIMASK();
    __disable_irq();
}

/* Enable interrupts based on saved state */
static void enableInterrupts(void) {
    __set_PRIMASK(interruptState);
}

/*Copy STRUCT*/
static void Copy_Struct(uint8_t *dest, uint8_t *src , uint16_t size){
	uint16_t idx;
	for(idx=0; idx<size; idx++){
		dest[idx] = src[idx];
	}
}

/*Write data into flash*/
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


/*LOAD DATA TO FLASH and return status*/
FLASH_LOAD_API_t *FLASH_LOAD_USB2FLASH(){
	uint8_t *data;
	SREC_API_t *srecAPI;
	FLASH_LOAD_API_t _flashLoadAPI = {
		.sizeData = 0
	};
	FLASH_LOAD_API_t *flashLoadAPI = &_flashLoadAPI;

	flashLoadAPI->status = FLASH_LOAD_Loading;
	uint8_t checkFirstLine = 1;
	/*LOAD DATA */
		/*Take first line SREC and erase flash*/
	while(flashLoadAPI->status == FLASH_LOAD_Loading){
	data = (uint8_t *)QUEUE_Pop();
	if (data != NULL) {

		srecAPI = (SREC_API_t *)SREC_ApiGetData(data, SREC_LINE_LEN_MAX, '\n');

		/*Free data in heap when after parse*/
		free(data);

		if(srecAPI->status == SREC_TRUE){

			/*Save First Line to Program Flash in Last time if done Srec_file*/
			if(checkFirstLine){
				Copy_Struct((uint8_t*)&dataSREC_First, (uint8_t*)srecAPI, sizeof(dataSREC_First));
				checkFirstLine = 0;
			}else{
				FLASH_ProgarmWord(srecAPI);
				flashLoadAPI->sizeData++;
			}
		}
		else if(srecAPI->status == SREC_Termination_DATA){
			FLASH_ProgarmWord(&dataSREC_First);
			flashLoadAPI->status = FLASH_LOAD_Done;
		}
		else if(srecAPI->status == SREC_Header_DATA){
			//NEXT LINE
		}
		/*Not have the SREC terminal line*/
		else if(0){
			flashLoadAPI->status = FLASH_LOAD_Error;
		}
		else
		{
			//NEXT LINE
		}



	}
	}
	return flashLoadAPI;
}
//TEST GET DATA FROM SREC LINE
void FLASH_TransmitALineSrec(){
		// Receive data

	uint8_t *data;
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

uint8_t FLASH_CheckEmpty(uint32_t addr){
	uint8_t status = 0;
	uint32_t *ptrAddr = (uint32_t *)addr;
	if(*ptrAddr == 0xFFFFFFFF){
		status = 1;
	}
	return status;
}

void FLASH_Jump2Firmware(uint32_t addr) {
    typedef void (*pFunction)(void);
    pFunction firmWare;
    uint32_t fw_SP = *((volatile uint32_t *)addr);
    uint32_t fw_PC = *((volatile uint32_t *)(addr + 4));

    // Disable interrupts
    disableInterrupts();

    // Disable fault handlers
    SCB->SHCSR &= ~((1 << 16) | (1 << 17) | (1 << 18));  // Disable UsageFault, BusFault, and MemManageFault

    // Set the application stack pointer
    __set_MSP(fw_SP);
    SCB->VTOR = addr;

    // Set the program counter to the application entry point
    firmWare = (pFunction)fw_PC;

    // Jump to the firmware
    firmWare();

    // Re-enable interrupts and fault handlers (based on previous state)
    enableInterrupts();
    SCB->SHCSR |= ((1 << 16) | (1 << 17) | (1 << 18));  // Enable UsageFault, BusFault, and MemManageFault
}

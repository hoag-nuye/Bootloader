
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


static SREC_API_t *dataSREC;
//================ SUPPORT ================/

//================ FOCUSED ================/
//
//void FLASH_SrecLineValidate(){
//		// Receive data
//		uint8_t *data;
//		SREC_API_t *srecStatus;
//			while(1){
//				data = (uint8_t *)QUEUE_Pop();
//				if (data != NULL) {
//					srecStatus = (SREC_API_t *)SREC_ApiGetData(data, SREC_LINE_LEN_MAX, '\n');
//					dataSREC = srecStatus;
//				}
//}
//}

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



////TEST GET DATA FROM SREC LINE
//void FLASH_TransmitTEST(){
//		// Receive data
//
//	uint8_t *data;
//	SREC_API_t *srecStatus;
//		while(1){
//			if(USB_GetNumberLineSREC() == 3){
//			data = (uint8_t *)QUEUE_Pop();
//			srecStatus = (SREC_API_t *)SREC_ApiGetData(data, SREC_LINE_LEN_MAX, '\n');
//			if (data != NULL) {
//				uint8_t i;
//				uint8_t j;
//				for(i =0; i< SREC_ADDR_LEN_MAX; i++){
//						uint8_t add = (srecStatus->srec_addr)>>(i*4);
//						UART0_TRANSMIT_Data(add);
//					}
//				UART0_TRANSMIT_Data('W');
//				for(j =0; j< SREC_DATA_LEN_MAX; j++){
//					UART0_TRANSMIT_Data(srecStatus->srec_data[j]);
//				}
//				UART0_TRANSMIT_Data('W'); // Carriage return
//				UART0_TRANSMIT_Data('Z');
//			}
//		}}
//}

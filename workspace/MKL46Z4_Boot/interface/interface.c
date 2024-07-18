//================ INCLUDE ================/
#include "usb.h"
#include "updateflash.h"
#include "MKL46Z4.h"
#include "led.h"
#include "button.h"
#include "config.h"
#include "interface.h"


//================ DEFINED ================/

//MACHINE_WAIT_EVENT,
//MACHINE_BOOT_MODE,
//MACHINE_RUN_APP,
static void handleButton(BUTTON_Name_t name){
	switch (name){
		case SW1:
			break;
		case SW2_Hold:
			/*Enable TIMER COUNT DOWN*/
			TIMER_COUNTDOWN_Async_Start();
			break;
			/*Disable TIMER COUNT DOWN*/
		case SW2_Release:
			TIMER_COUNTDOWN_Async_Stop();
			break;
		}
}
//================ SUPPORT ================/

//================ FOCUSED ================/
void  Bootloader_Init(){
	BUTTON_Init(SW1);
	BUTTON_Init(SW2);
	LED_Init(LED1);
	LED_Init(LED2);
	Read_BUTTON(handleButton);
	TIMER_Init();

	//SET UP TIMER Count down for Hold SW2
	TIMER_COUNTDOWN_Async(300);//3s
}

void BootLoader_End(){

}

void Bootloader(){
	State_Machine_t stateMachine;
	stateMachine = MACHINE_WAIT_EVENT;
	while(1){
		switch(stateMachine){
			case(MACHINE_WAIT_EVENT):
				Flash_LED_Timer(LED2, 1, 200);

				//SET UP TIMER FOR MACHINE_WAIT_EVENT
				TIMER_WAIT_Sync(5000);//5s
				TIMER_WAIT_();
				if(BUTTON_SUCCESS_HOLD()){
					stateMachine = MACHINE_BOOT_MODE;
				}else{
					stateMachine = MACHINE_RUN_APP;
				}
				//
				break;

			case(MACHINE_BOOT_MODE):
				Flash_LED_Timer(LED2, 2, 200);
				USB_Init();
				USB_SetupComms();

				/*LOAD APP*/
				FTFA_EraseMultiSector(FLASH_ADDRESS_APP1_LSB, FLASH_ADDRESS_APP1_MSB);
				FLASH_LOAD_API_t *FLApi = FLASH_LOAD_USB2FLASH();
				USB_Disconnect();

				switch (FLApi->status){
					case FLASH_LOAD_Error:
						Flash_LED_Timer(LED2, 2, 200);
						//CHECK BACKUP EMPTY
						if(FLASH_CheckBackupEmpty()){
							//RUN_APP (Error at first load app time)
							stateMachine = MACHINE_RUN_APP;
						}else{
							//LOAD_BACKUP

							//RUN APP
							stateMachine = MACHINE_RUN_APP;
						}
					case FLASH_LOAD_Done:
						/*Backup*/


						/*Run APP*/
						stateMachine = MACHINE_RUN_APP;
						break;
				}
				//
				break;

			case(MACHINE_RUN_APP):
				if(FLASH_CheckFirmwareEmpty()){
					Flash_LED_Timer(LED2, 3, 200);
				}
				else{

					BUTTON_RESET();
					Flash_LED_Timer(LED1, 3, 200);
					FLASH_Jump2Firmware();
				}
				break;
		}
	}
}

//void Bootloader(){
//	USB_Init();
//	USB_SetupComms();
////	FTFA_EraseSector(FLASH_ADDRESS_APP1_LSB);
//
///*DONE LOAD*/
//	FTFA_EraseMultiSector(FLASH_ADDRESS_APP1_LSB, FLASH_ADDRESS_APP1_MSB);
//	FLASH_LOAD_API_t *FLApi = FLASH_LOAD_USB2FLASH();
//
//	USB_Disconnect();
///***********/
//
///*JUMP APP*/
//	FLASH_Jump2Firmware();
///***********/
//
//
//
////	FTFA_EraseMultiSector();
////	FLASH_TransmitALineSrec();
////	FLASH_TransmitTEST();
//};

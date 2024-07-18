//================ INCLUDE ================/
#include <stdint.h>
//================ DEFINED ================/
#ifndef __INTERFACE_H_
#define __INTERFACE_H_


//------------- Enum -----------//
//Define value of fields

typedef enum{
	MACHINE_WAIT_EVENT,
	MACHINE_BOOT_MODE,
	MACHINE_RUN_APP,
}State_Machine_t;

//------------- Struct -----------//



//================ SUPPORT ================/
void Bootloader_Init();
void Bootloader();
//================ FOCUSED ================/
#endif

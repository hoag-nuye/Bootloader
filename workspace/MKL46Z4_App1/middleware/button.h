//================ INCLUDE ================/
#include "MKL46Z4.h"
#include <stdint.h>
//================ DEFINED ================/
#ifndef __BUTTON_H_
#define __BUTTON_H_


//------------- Enum -----------//
//Define value of fields
typedef enum{
	SW1,
	SW2
}BUTTON_Name_t;
typedef void (*Handle_Button_t)(BUTTON_Name_t);

//------------- Struct -----------//

//================ SUPPORT ================/

//================ FOCUSED ================/

// Configuration control port
void BUTTON_Init(BUTTON_Name_t name);
void Read_BUTTON(Handle_Button_t handle_ButtonSwitch);
#endif

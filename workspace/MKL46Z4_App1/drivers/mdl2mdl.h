//================ INCLUDE ================/
#include "MKL46Z4.h"
#include <stdint.h>
//================ DEFINED ================/
#ifndef __MDL2MDL_H_
#define __MDL2MDL_H_


//------------- Enum -----------//
//Define value of fields

typedef enum{
	 M2M_PIT2ADC,
}M2M_Peripheral_t;


//------------- Struct -----------//

//================ SUPPORT ================/

//================ FOCUSED ================/

// Configuration control port
void M2M_Interconnects(M2M_Peripheral_t joinWhich);

#endif

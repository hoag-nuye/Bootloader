//================ INCLUDE ================/
#include "MKL46Z4.h"
#include <stdint.h>
//================ DEFINED ================/
#ifndef __FTFA_H_
#define __FTFA_H_


//------------- Enum -----------//
//Define value of fields
//------------- Struct -----------//

//================ SUPPORT ================/

//================ FOCUSED ================/
void FTFA_ProgramWord(uint32_t address, uint32_t data);
void FTFA_EraseSector(uint32_t address);
void FTFA_EraseMultiSector(uint32_t addrStart, uint32_t addrEnd);
// Configuration control port
#endif

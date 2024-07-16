//================ INCLUDE ================/
#include "MKL46Z4.h"
#include "ftfa.h"
//================ DEFINED ================/
//Get Clock From IR Clock

//================ SUPPORT ================/

//================ FOCUSED ================/
void FTFA_ProgramWord(uint32_t address, uint32_t data){
	/*REVIEW DATA\
	 * The FCCOB register group uses a BigEndian addressing convention
	 * the Most Significant data resides in the Lowest FCCOB register number
	 * LSB             MSB (FLASH)
	 * 0x00 0x01 0x02 0x03
	 * FC7  FC6  FC5  FC4
	 * AB   CD   EF   GH ->(data : 0xGHEFCDAB)(SREC : 0xABCDEFGH )
	 * AB->FCCOB7 (uint8_t)(data>>0)
	 * CD->FCCOB6 (uint8_t)(data>>8)
	 * EF->FCCOB5 (uint8_t)(data>>16)
	 * GH->FCCOB4 (uint8_t)(data>>24)
	 * */

	/*PRE-CHECK DATA AND ADDRESS*/
    uint8_t FCCOB1 = (address >> 16) & 0xFF;
    uint8_t FCCOB2 = (address >> 8) & 0xFF;
    uint8_t FCCOB3 = address & 0xFF;
    // Data parameter
    uint8_t FCCOB4 = (uint8_t)(data>>24); //MSB
    uint8_t FCCOB5 = (uint8_t)(data>>16);
    uint8_t FCCOB6 = (uint8_t)(data>>8);
    uint8_t FCCOB7 = (uint8_t)(data>>0);        //LSB


    /*PROGRAM FLASH*/
    // Wait FTFA FCCOB Availability Check = 1
    while (!(FTFA->FSTAT & FTFA_FSTAT_CCIF_MASK));
    // Clear the old errors
    FTFA->FSTAT = FTFA_FSTAT_RDCOLERR_MASK | FTFA_FSTAT_ACCERR_MASK | FTFA_FSTAT_FPVIOL_MASK;
    // Write to the FCCOB registers to load the required command parameter.
    FTFA->FCCOB0 = 0x06;
    // Address parameter
    FTFA->FCCOB1 = FCCOB1;
    FTFA->FCCOB2 = FCCOB2;
    FTFA->FCCOB3 = FCCOB3;
    // Data parameter
    FTFA->FCCOB4 = FCCOB4;
    FTFA->FCCOB5 = FCCOB5;
    FTFA->FCCOB6 = FCCOB6;
    FTFA->FCCOB7 = FCCOB7;
    // Clear the CCIF to launch the command
    FTFA->FSTAT = FTFA_FSTAT_CCIF_MASK;
    // Wait FTFA FCCOB Availability Check = 1
    while (!(FTFA->FSTAT & FTFA_FSTAT_CCIF_MASK));
}

//COPY OF PRO-Master.DO XUAN DUC :))
void FTFA_EraseSector(uint32_t address){
	// Chờ cho đến khi bộ điều khiển flash sẵn sàng
	 while (!(FTFA->FSTAT & FTFA_FSTAT_CCIF_MASK));
	 // Xóa các lỗi hiện có
	 FTFA->FSTAT = FTFA_FSTAT_RDCOLERR_MASK | FTFA_FSTAT_ACCERR_MASK | FTFA_FSTAT_FPVIOL_MASK;
	 // Thiết lập lệnh xóa
	 FTFA->FCCOB0 = 0x09;
	 // Thiết lập địa chỉ
	 FTFA->FCCOB1 = (address >> 16) & 0xFF;
	 FTFA->FCCOB2 = (address >> 8) & 0xFF;
	 FTFA->FCCOB3 = address & 0xFF;

	 // Khởi động lệnh
	 FTFA->FSTAT = FTFA_FSTAT_CCIF_MASK;

	 // Chờ cho đến khi lệnh hoàn thành
	 while (!(FTFA->FSTAT & FTFA_FSTAT_CCIF_MASK));
}

void FTFA_EraseMultiSector(uint32_t addrStart, uint32_t addrEnd){
	uint32_t idxAddr;
	for(idxAddr = addrStart; idxAddr<addrEnd; idxAddr+=0x400){//1024B
		FTFA_EraseSector(idxAddr);
	}
};

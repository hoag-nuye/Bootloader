/*
 * srecfile.h
 *
 *  Created on: Jul 14, 2024
 *      Author: admin
 */

#ifndef SRECFILE_H_
#define SRECFILE_H_

//================ INCLUDE ================/
#include "MKL46Z4.h"
#include <stdint.h>

//================ DEFINED ================/
#define SREC_LINE_LEN_MAX 96 // 1(S)+1(T)+2(B)+8(A)+80(D)+2(S)+2(END) = 96
#define SREC_DATA_LEN_MAX 80
#define SREC_ADDR_LEN_MAX 8

//------------- Enum -----------//
typedef enum{
	SREC_TRUE = 0x00,
	SREC_ERR_SYNTAX = 0x01,
	SREC_ERR_TYPE = 0x02,
	SREC_ERR_COUNT = 0x03,
	SREC_ERR_ADDRESS = 0x04,
	SREC_ERR_DATA = 0x05,
	SREC_ERR_CHECKSUM = 0x06,
	SREC_EMPTY = 0x07,
	SREC_ERR_STORAGE = 0x08,
	SREC_IGNORE_DATA = 0x09,
	SREC_Termination_DATA = 0x10,
}SREC_Status_t;

typedef enum{
	FALSE,
	TRUE
}Bool_t;

typedef struct{
	uint8_t type;
	uint8_t count;
	uint32_t address;
	uint8_t data[SREC_DATA_LEN_MAX/2];
	uint8_t checkSum;
}SREC_Data_t;

typedef enum{
	STATE_READ_START,
	STATE_READ_TYPE,
	STATE_READ_COUNT,
	STATE_READ_ADDRESS,
	STATE_READ_DATA,
	STATE_READ_CHECKSUM,
	STATE_READ_NEXT_LINE,
	STATE_NOT_EXIST_FILE,
	STATE_READ_EOF
}SREC_State_t;

//------------- Struct -----------//

typedef struct{
	uint32_t srec_addr;
	uint8_t srec_data[SREC_DATA_LEN_MAX/2];
	uint8_t srec_addr_len;
	uint8_t srec_data_len;
	SREC_Status_t status;
}SREC_API_t;

//================ SUPPORT ================/

//================ FOCUSED ================/
SREC_API_t *SREC_ApiGetData(uint8_t *srecLineData, uint8_t sizeData, uint8_t chrEOD);

#endif /* SRECFILE_H_ */

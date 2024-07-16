/*
 * srecfile.c
 *
 *  Created on: Jul 14, 2024
 *      Author: admin
 */

#include <stdint.h>
#include <math.h>
#include "srecfile.h"
//================ DEFINED ================/
#define HEX_INVALID 255
static SREC_Data_t dataSrec = {0};
static SREC_State_t state;
static SREC_API_t apiResult = {0};

//------------- Struct -----------//

//------------- Enum -----------//


//================ SUPPORT ================/

//chtoHex: Convert character to hexa
uint8_t chtoHex(char ch){
	uint8_t result;

	if('0' <= ch && '9' >= ch){
		result = ch - '0';
	}else if('A' <= ch && 'F' >= ch){
		result = ch - 'A' + 0xA;
	}else {
		result = HEX_INVALID;
	}

	return result;
}

//strtoHex: Convert string to hex
SREC_Status_t strtoHex(uint8_t *str, uint8_t len, uint32_t *decimal){
	SREC_Status_t status = SREC_TRUE;
	*decimal = 0;
	uint8_t idx;
	uint8_t result;
	for(idx = 0; idx < len; idx++){
		result = chtoHex(str[idx]);
		if(result == HEX_INVALID){
			status = SREC_ERR_SYNTAX;
			break;
		}
		*decimal += result*pow(16, len-idx-1);
	}
	return status;
}

// GetAddressNum(dataSrec.type) to get value of address length into Record types table
uint8_t GetAddressNum(uint8_t record_field){
	uint8_t LEN_ADDRESS_FIELD = 0;
		switch(record_field){
			case 0://16 bit = 4w
				LEN_ADDRESS_FIELD = 4;
				break;
			case 1://16 bit = 4w
				LEN_ADDRESS_FIELD = 4;
				break;
			case 2://24 bit = 6w
				LEN_ADDRESS_FIELD = 6;
				break;
			case 3://32 bit = 8w
				LEN_ADDRESS_FIELD = 8;
				break;
			case 4://0 bit = 0w
				LEN_ADDRESS_FIELD = 0;
				break;
			case 5://16 bit = 4w
				LEN_ADDRESS_FIELD = 4;
				break;
			case 6://24 bit = 6w
				LEN_ADDRESS_FIELD = 6;
				break;
			case 7://32 bit = 4w
				LEN_ADDRESS_FIELD = 8;
				break;
			case 8://24 bit = 4w
				LEN_ADDRESS_FIELD = 4;
				break;
			case 9://16 bit = 4w
				LEN_ADDRESS_FIELD = 4;
				break;
			default :
				LEN_ADDRESS_FIELD = -1;
				break;
		}
		return LEN_ADDRESS_FIELD;
}
// Caculate Sum
static uint8_t caculateSum(uint8_t AddressNum, uint8_t DataNum){
	// + byte count
	uint8_t sum = dataSrec.count;
	// + byte address
	uint8_t idx;
	uint32_t tempSum = dataSrec.address;
	for(idx = 0; idx<AddressNum/2; idx++){
		sum += (uint8_t)tempSum;
		tempSum = tempSum>>8;
	}
	//+ byte data
	for(idx = 0; idx<DataNum/2; idx++){
		sum += dataSrec.data[idx];
	}
	return sum;
};

//================ FOCUSED ================/

// Analysis A Line
/*PARSE of a line SREC and return data
 * data : pointer of line data
 * sizeData : size of data
 * chrEOD : finish character of line data */
SREC_API_t *SREC_ApiGetData(uint8_t *srecLineData, uint8_t sizeData, uint8_t chrEOD){
	SREC_Status_t status = SREC_TRUE;
	uint8_t AddressNum = 0;
	uint8_t DataNum = 0;
	uint32_t resultConvert;

	switch(state){
		case STATE_NOT_EXIST_FILE:
			break;
		//1. Read Record start field
		case STATE_READ_START:
			if(srecLineData[0] == chrEOD){
				status = SREC_EMPTY;
				break;
			}else if(srecLineData[0] != 'S'){
				status = SREC_ERR_SYNTAX;
				break;
			}
		//2. Read Record type field
		case STATE_READ_TYPE:
			status = strtoHex(&srecLineData[1], 1, (uint32_t *)&resultConvert);
			dataSrec.type = (uint8_t)resultConvert;
			uint8_t condit_T = dataSrec.type >= 0 && dataSrec.type <= 9 && dataSrec.type != 4;
			if(!condit_T || status == SREC_ERR_SYNTAX){
				status = SREC_ERR_TYPE;
				break;
			}
			// caculate address num
			AddressNum = GetAddressNum(dataSrec.type);
			apiResult.srec_addr_len = AddressNum/2;
		//3. Read Byte count field
		case STATE_READ_COUNT:
			status = strtoHex(&srecLineData[2], 2, (uint32_t *)&resultConvert);
			dataSrec.count = (uint8_t)resultConvert;
			uint8_t condit_C = dataSrec.count >= 0x03 && dataSrec.type <= 0xFF;
			if(!condit_C || status == SREC_ERR_SYNTAX){
				status = SREC_ERR_COUNT;
				break;
			}
			// caculate data num
			DataNum = dataSrec.count*2 - AddressNum - 2;
			apiResult.srec_data_len = DataNum/2;
		//3. Read Address field
		case STATE_READ_ADDRESS:
			status = strtoHex(&srecLineData[4], AddressNum, (uint32_t *)&(dataSrec.address));
			apiResult.srec_addr = dataSrec.address;
			if(status != SREC_TRUE || status == SREC_ERR_SYNTAX){
				status = SREC_ERR_ADDRESS;
				break;
			}
		//4. Read Data field
		uint8_t idx;
		case STATE_READ_DATA:
			for(idx = 0; idx < SREC_DATA_LEN_MAX/2 ; idx++){
				status = strtoHex(&srecLineData[4+AddressNum+idx*2], 2, (uint32_t *)&resultConvert);
				dataSrec.data[idx] = (uint8_t )resultConvert;
				apiResult.srec_data[idx] = dataSrec.data[idx];
			}
			if(status != SREC_TRUE || status == SREC_ERR_SYNTAX){
				status = SREC_ERR_DATA;
				break;
			}
		//5. Read Checksum field
		case STATE_READ_CHECKSUM:
			status = strtoHex(&srecLineData[4+ AddressNum + DataNum], 2, (uint32_t *)&resultConvert);
			dataSrec.checkSum = (uint8_t)resultConvert;
			uint8_t condit_S = (caculateSum(AddressNum, DataNum) | dataSrec.checkSum) == 0xFF;
			if(!condit_S || status == SREC_ERR_SYNTAX){
				status = SREC_ERR_CHECKSUM;
				break;
		}
	}
	if(!((srecLineData[1] == '1') || (srecLineData[1] == '2') || (srecLineData[1] == '3'))){
		status = SREC_IGNORE_DATA;
		}
	if((srecLineData[1] == '7') || (srecLineData[1] == '8') || (srecLineData[1] == '9')){
		status = SREC_Termination_DATA;
	}
	apiResult.status = status;
	return &apiResult;
}






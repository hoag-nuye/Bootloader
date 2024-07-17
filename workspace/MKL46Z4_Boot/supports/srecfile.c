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
static uint8_t chtoHex(char ch) {
    if ('0' <= ch && ch <= '9') return ch - '0';
    if ('A' <= ch && ch <= 'F') return ch - 'A' + 0xA;
    return HEX_INVALID;
}

//strtoHex: Convert string to hex
static SREC_Status_t strtoHex(const char *str, uint8_t len, uint32_t *decimal) {
    *decimal = 0;
    for (uint8_t idx = 0; idx < len; idx++) {
        uint8_t result = chtoHex(str[idx]);
        if (result == HEX_INVALID) {
            return SREC_ERR_SYNTAX;
        }
        *decimal = (*decimal << 4) | result;
    }
    return SREC_TRUE;
}

// GetAddressNum(dataSrec.type) to get value of address length into Record types table
static int8_t GetAddressNum(uint8_t record_field) {
    switch (record_field) {
        case 0: case 1: case 5: case 9: return 4;
        case 2: case 6: return 6;
        case 3: case 7: return 8;
        case 4: case 8: return 4;
        default: return -1;
    }
}
// Caculate Sum
static uint8_t calculateSum(uint8_t AddressNum, uint8_t DataNum) {
    uint8_t sum = dataSrec.count;
    uint32_t tempSum = dataSrec.address;
    for (uint8_t idx = 0; idx < AddressNum / 2; idx++) {
        sum += (uint8_t)tempSum;
        tempSum >>= 8;
    }
    for (uint8_t idx = 0; idx < DataNum / 2; idx++) {
        sum += dataSrec.data[idx];
    }
    return sum;
}

//================ FOCUSED ================/

// Analysis A Line
/*PARSE of a line SREC and return data
 * data : pointer of line data
 * sizeData : size of data
 * chrEOD : finish character of line data */
SREC_API_t *SREC_ApiGetData(uint8_t *srecLineData, uint8_t sizeData, uint8_t chrEOD) {
    SREC_Status_t status = SREC_TRUE;
    uint8_t AddressNum = 0;
    uint8_t DataNum = 0;
    uint32_t resultConvert;

    if (srecLineData[0] != 'S') {
        apiResult.status = SREC_ERR_SYNTAX;
        return &apiResult;
    }

    status = strtoHex((char *)&srecLineData[1], 1, &resultConvert);
    dataSrec.type = (uint8_t)resultConvert;
    AddressNum = GetAddressNum(dataSrec.type);
    if (AddressNum == -1 || status == SREC_ERR_SYNTAX) {
        apiResult.status = SREC_ERR_TYPE;
        return &apiResult;
    }

    status = strtoHex((char *)&srecLineData[2], 2, &resultConvert);
    dataSrec.count = (uint8_t)resultConvert;
    if (!(dataSrec.count >= 0x03 && dataSrec.type <= 0xFF) || status == SREC_ERR_SYNTAX) {
        apiResult.status = SREC_ERR_COUNT;
        return &apiResult;
    }

    DataNum = dataSrec.count * 2 - AddressNum - 2;
    apiResult.srec_data_len = DataNum / 2;

    status = strtoHex((char *)&srecLineData[4], AddressNum, &dataSrec.address);
    apiResult.srec_addr = dataSrec.address;
    if (status != SREC_TRUE) {
        apiResult.status = SREC_ERR_ADDRESS;
        return &apiResult;
    }

    for (uint8_t idx = 0; idx < DataNum / 2; idx++) {
        status = strtoHex((char *)&srecLineData[4 + AddressNum + idx * 2], 2, &resultConvert);
        if (status != SREC_TRUE) {
            apiResult.status = SREC_ERR_DATA;
            return &apiResult;
        }
        dataSrec.data[idx] = (uint8_t)resultConvert;
        apiResult.srec_data[idx] = dataSrec.data[idx];
    }

    status = strtoHex((char *)&srecLineData[4 + AddressNum + DataNum], 2, &resultConvert);
    dataSrec.checkSum = (uint8_t)resultConvert;
    if (((calculateSum(AddressNum, DataNum) + dataSrec.checkSum) & 0xFF) != 0xFF) {
        apiResult.status = SREC_ERR_CHECKSUM;
        return &apiResult;
    }

    if (srecLineData[1] == '4' || srecLineData[1] == '5' || srecLineData[1] == '6') {
        apiResult.status = SREC_IGNORE_DATA;
    } else if (srecLineData[1] == '7' || srecLineData[1] == '8' || srecLineData[1] == '9') {
        apiResult.status = SREC_Termination_DATA;
    } else if (srecLineData[1] == '0') {
        apiResult.status = SREC_Header_DATA;
    } else {
        apiResult.status = SREC_TRUE;
    }

    return &apiResult;
}







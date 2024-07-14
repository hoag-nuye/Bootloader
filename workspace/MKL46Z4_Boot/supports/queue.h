//================ INCLUDE ================/
#include "MKL46Z4.h"
#include <stdint.h>

//================ DEFINED ================/
#ifndef __QUEUE_H_
#define __QUEUE_H_

//------------- Struct -----------//
typedef struct node_t{
	uint8_t *data;
	struct node_t *pNext;
}node_t;
//------------- Enum -----------//


//================ SUPPORT ================/

//================ FOCUSED ================/
void QUEUE_Init(uint8_t sizeofData);
void QUEUE_Push(void *data);
uint8_t *QUEUE_Pop();

#endif

////User manual
//typedef struct{
//	char name [20];
//	char ID [10];
//	uint32_t power;
//	uint32_t price;
//	uint32_t age;
//}Device;
//void main(){
//
//	Device device1 = {
//		 .name = "LED1",
//		 .ID = "L0001",
//		 .power = 100,
//		 .price = 200,
//		 .age = 2
//	};
//
//		Device device2 = {
//		 .name = "LED2",
//		 .ID = "L0002",
//		 .power = 200,
//		 .price = 400,
//		 .age = 3
//	};
//		Device device3 = {
//		 .name = "LED3",
//		 .ID = "L0003",
//		 .power = 300,
//		 .price = 400,
//		 .age = 1
//	};
//	QUEUE_Init(sizeof(Device));
//	QUEUE_Push(&device1);
//	QUEUE_Push(&device2);
//	QUEUE_Push(&device3);
//
//
//	Device *device;
//	do{
//		device = (Device *)QUEUE_Pop();
//		if(device!=NULL){
//			printf("%s %s %d %d %d\n", device->ID, device->name, device->power, device->price, device->age);
//		}
//	}while(device!=NULL);
//}


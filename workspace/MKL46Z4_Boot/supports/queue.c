#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <supports/queue.h>
//================ DEFINED ================/

static node_t *HEAD = NULL;
static uint8_t SIZE_DATA = 0;
static node_t *preNode;
static uint8_t isHEAD = 0;
//------------- Struct -----------//

//------------- Enum -----------//


//================ SUPPORT ================/
static void copy_data(uint8_t *dest, uint8_t *src){
	uint8_t idx;
	for(idx = 0; idx<SIZE_DATA; idx++){
		dest[idx] = src[idx];
	}
}

//================ FOCUSED ================/
void QUEUE_Init(uint8_t sizeofData){
	SIZE_DATA = sizeofData;
}

//Push data into queue
void QUEUE_Push(void *data){
	node_t *ptr = (node_t *)malloc(sizeof(node_t));
	ptr->data = (uint8_t *)malloc(SIZE_DATA);
	copy_data(ptr->data,(uint8_t *)data);
	ptr->pNext = NULL;
	if(HEAD == NULL){
		HEAD = ptr;
	}else{
		node_t *preNode = HEAD;
		while(preNode->pNext != NULL){
			preNode = preNode->pNext;
		}
		preNode->pNext = ptr;
	}
}

//Pop data out queue
uint8_t *QUEUE_Pop(){
	uint8_t *pData;
	if(isHEAD ==0){
		preNode = HEAD;
		pData = (uint8_t *)preNode->data;
		preNode = preNode->pNext;
		isHEAD = 1;
	}else{
		if(preNode == NULL){
			pData = NULL;
		}
		else{
			pData = (uint8_t *)preNode->data;
			preNode = preNode->pNext;
		}
	}
	return (uint8_t *)pData;
}



#include <stdint.h>
#include <stdlib.h>
#include <supports/queue.h>
//================ DEFINED ================/

static node_t *HEAD = NULL;
static uint8_t SIZE_DATA = 0;
static uint32_t nodeNum = 0;
static uint32_t popNodeNum = 0;
static uint32_t restNodeNum = 0;
//------------- Struct -----------//

//------------- Enum -----------//


//================ SUPPORT ================/
static void copy_data(uint8_t *dest, uint8_t *src){
	uint8_t idx;
	for(idx = 0; idx<SIZE_DATA; idx++){
		dest[idx] = src[idx];
	}
}
//Clear heap
static void QUEUE_Clear(){
    uint8_t *pData;
    while((pData = QUEUE_Pop()) != NULL){
        free(pData);
    }
}

//FREE HEEP
static void QUEUE_Free(){
	node_t *preNode;
	while(HEAD != NULL){
		preNode = HEAD;
		HEAD = preNode->pNext;
		free(preNode);
		free(preNode->data);
	}
}
//================ FOCUSED ================/
void QUEUE_Init(uint8_t sizeofData){
	QUEUE_Clear();
//	QUEUE_Free();
	SIZE_DATA = sizeofData;
	nodeNum = 0;
}

//Push data into queue
void QUEUE_Push(void *data){
	node_t *ptr = (node_t *)malloc(sizeof(node_t));
	if (ptr == NULL) {
		 return;
	}

	ptr->data = (uint8_t *)malloc(SIZE_DATA);
	if (ptr->data == NULL) {
		free(ptr);
		return;
	}
	copy_data(ptr->data,(uint8_t *)data);
	ptr->pNext = NULL;
	if(HEAD == NULL){
		HEAD = ptr;
		nodeNum++;
	}else{
		node_t *preNode = HEAD;
		while(preNode->pNext != NULL){
			preNode = preNode->pNext;
		}
		preNode->pNext = ptr;
		nodeNum++;
	}

}

//Pop data out queue
uint8_t *QUEUE_Pop(){
	uint8_t *pData;
	node_t *preNode;
	if(HEAD == NULL){
		pData = NULL;
	}else{
		preNode = HEAD;
		pData = preNode->data;
		HEAD = preNode->pNext;
		free(preNode);
		nodeNum--;
	}
	return (uint8_t *)pData;
}

uint8_t *QUEUE_Get(uint8_t index){
	if(index >= nodeNum){
	   return NULL;
	}
	uint8_t idx;
	uint8_t *pData;
	node_t *preNode = HEAD;

	for(uint8_t idx = 0; idx<index; idx++){
		if(preNode!= NULL){
			pData = preNode->data;
			preNode = preNode->pNext;
		}
	}

	return (uint8_t *)pData;
}






//================ INCLUDE ================/
#include "gpio.h"
#include "MKL46Z4.h"
//================ DEFINED ================/

//================ SUPPORT ================/

//================ FOCUSED ================/
void GPIO_PinConfig(GPIO_PinConfig_Type *GPIO_Config){
	if(GPIO_Config->pdd == Direct_Output){
		GPIO_Config->gpio->PDOR &= ~(GPIO_PDOR_PDO_SHIFT<<GPIO_Config->pin);
		GPIO_Config->gpio->PDOR |= GPIO_PDOR_PDO(GPIO_Config->data << GPIO_Config->pin);
	}
	GPIO_Config->gpio->PDDR &= ~(GPIO_PDDR_PDD_SHIFT<<GPIO_Config->pin);
	GPIO_Config->gpio->PDDR |= GPIO_PDDR_PDD(GPIO_Config->pdd << GPIO_Config->pin);
};
void GPIO_SetPin(GPIO_Type* gpio, uint8_t pin){
	gpio->PSOR |= GPIO_PSOR_PTSO(1<<pin);
};
GPIO_Data_t GPIO_ReadPin(GPIO_Type* gpio, uint8_t pin){
	GPIO_Data_t data = GPIO_DATA_lowLOGIC;
	if((gpio->PDDR & (GPIO_PDDR_PDD_SHIFT<<pin)) != data){
		data = GPIO_DATA_highLOGIC;
	}
	return data;
};

void GPIO_ClearPin(GPIO_Type* gpio, uint8_t pin){
	gpio->PCOR |= GPIO_PCOR_PTCO(1<<pin);
};
void GPIO_TogglePin(GPIO_Type* gpio, uint8_t pin){
	gpio->PTOR |= GPIO_PTOR_PTTO(1<<pin);
};

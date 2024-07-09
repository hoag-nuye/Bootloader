//================ INCLUDE ================/
#include "MKL46Z4.h"
#include "port.h"
//================ DEFINED ================/

//================ SUPPORT ================/

//================ FOCUSED ================/

//Config base port in each pin
void PORT_PinConfig(PORT_Config_Type *PORT_Config){
	PORT_Config->port->PCR[PORT_Config->pin] &= ~ PORT_PCR_MUX_MASK;
	PORT_Config->port->PCR[PORT_Config->pin] |= PORT_PCR_MUX(PORT_Config->mux);
};

//Config pin, want to use interrupts
void PORT_EXTI_Config(PORT_Config_Type *PORT_Config){
	if(PORT_Config->pull != Pull_DISABLE){
		//Enable Pull
		PORT_Config->port->PCR[PORT_Config->pin] = \
		(PORT_Config->port->PCR[PORT_Config->pin] & \
		~(PORT_PCR_PE_MASK + PORT_PCR_PS_MASK)) | \
		PORT_Config->pull << PORT_PCR_PS_SHIFT;
		//Select edge
		PORT_Config->port->PCR[PORT_Config->pin] &= ~PORT_PCR_IRQC_MASK;
		PORT_Config->port->PCR[PORT_Config->pin] |= PORT_PCR_IRQC(PORT_Config->irqc);


	}

};

//Clear flag interrupts
void PORT_EXTI_ClearFlag (PORT_Type* port, uint8_t pin){
	port->PCR[pin] |= PORT_PCR_ISF(1);
}

//Read flag interrupts
Port_Interrupt_Flag_t PORT_Interrupt(PORT_Type* port, uint8_t pin){
	Port_Interrupt_Flag_t flag = PORT_INTERRUPT_NOTdetected;
	if((port->PCR[pin] & PORT_PCR_ISF_MASK) != 0){
		flag = PORT_INTERRUPT_detected;
	}
	return flag;
};



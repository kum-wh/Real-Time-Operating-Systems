#include "gpio.h"
#include <MKL25Z4.h>

void initGPIOPorts(PORT_Type *port, GPIO_Type * gpioType, uint32_t pinNum)
{
	port->PCR[pinNum] &= ~PORT_PCR_MUX_MASK;
	port->PCR[pinNum] |= PORT_PCR_MUX(1);
	gpioType->PDDR |= MASK(pinNum);
}

void initGreenLedStripPorts(void) {
	initGPIOPorts(PORTB, PTB, LED_STRIP_B_8);
	initGPIOPorts(PORTB, PTB, LED_STRIP_B_9);
	initGPIOPorts(PORTB, PTB, LED_STRIP_B_10);
	initGPIOPorts(PORTB, PTB, LED_STRIP_B_11);
	
	initGPIOPorts(PORTE, PTE, LED_STRIP_E_2);
	initGPIOPorts(PORTE, PTE, LED_STRIP_E_3);
	initGPIOPorts(PORTE, PTE, LED_STRIP_E_4);
	initGPIOPorts(PORTE, PTE, LED_STRIP_E_5);
}

void initRedLedStripPorts(void) {
	initGPIOPorts(PORTC, PTC, LED_STRIP_C_8);
	initGPIOPorts(PORTC, PTC, LED_STRIP_C_9);
	initGPIOPorts(PORTC, PTC, LED_STRIP_C_10);
	initGPIOPorts(PORTC, PTC, LED_STRIP_C_11);
}

void initTriggerPort(void)
{
	initGPIOPorts(PORTD, PTD, TRIGGER_D_1);
}

// set to input
void initEchoPort(void)
{
	PORTD->PCR[ECHO_D_3] &= ~PORT_PCR_MUX_MASK;
	PORTD->PCR[ECHO_D_3] |= PORT_PCR_MUX(1);
	PTD->PDDR &= ~MASK(ECHO_D_3);
	PORTD->PCR[ECHO_D_3] &= ~PORT_PCR_IRQC_MASK;
	
	// configure on falling and rising edge 
	PORTD->PCR[ECHO_D_3] |= PORT_PCR_IRQC(11);
	
	NVIC_EnableIRQ(PORTD_IRQn);
}

void initGPIO(void)
{
	// need to enable the portB and portD clock before using the ports
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTC_MASK | SIM_SCGC5_PORTD_MASK | SIM_SCGC5_PORTE_MASK;
	
	initGreenLedStripPorts();		
	initRedLedStripPorts();
	initTriggerPort();
	initEchoPort();
}

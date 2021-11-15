#include "led.h"
#include "gpio.h"
#include "common.h"
#include <MKL25Z4.h>
#include "RTE_Components.h"
#include  CMSIS_device_header
#include "cmsis_os2.h"

GPIO_Type* allTypes[] = {PTB, PTB, PTB, PTB, PTE, PTE, PTE, PTE, PTE, PTE};
uint32_t allPinNumbers[] = {LED_STRIP_B_8, LED_STRIP_B_9, LED_STRIP_B_10, LED_STRIP_B_11,
		LED_STRIP_E_2, LED_STRIP_E_3, LED_STRIP_E_4, LED_STRIP_E_5};

uint32_t allRedPinNumbers[] = {LED_STRIP_C_8, LED_STRIP_C_9, LED_STRIP_C_10, LED_STRIP_C_11};
	

void onLed(GPIO_Type * gpioType, uint32_t pinNum)
{
	gpioType->PSOR |= MASK(pinNum);
}

void offLed(GPIO_Type * gpioType, uint32_t pinNum)
{
	gpioType->PCOR |= MASK(pinNum);
}

void lightFrontTwoGreenLeds(void) {
	for (int i = 0; i < 2; i++) {
		onLed(PTB, LED_STRIP_B_8);
		onLed(PTB, LED_STRIP_B_9);
		delay(0x80000);
		offLed(PTB, LED_STRIP_B_8);
		offLed(PTB, LED_STRIP_B_9);
		delay(0x80000);
	}
}

void lightLedOnAndOff(GPIO_Type * gpioType, uint32_t pinNum)
{
	onLed(gpioType, pinNum);
	osDelay(125);
	offLed(gpioType, pinNum);
	osDelay(125);
}

void lightGreenLedsTogether(void) {
	for (int i = 0; i < 8; i++) {
		onLed(allTypes[i], allPinNumbers[i]);
	}
}

void offGreenLedsTogether(void) {
	for (int i = 0; i < 8; i++) {
		offLed(allTypes[i], allPinNumbers[i]);
	}
}

void lightRedLedsOn(void) {
	for (int i = 0; i < 8; i++) {
		onLed(PTC, allRedPinNumbers[i]);
	}
}
void lightRedLedsOff(void) {
	for (int i = 0; i < 8; i++) {
		offLed(PTC, allRedPinNumbers[i]);
	}
}

void board_led_on(color_t color)
{
	switch(color) {
		case RED:
			PTB->PDOR &= ~MASK(RED_LED);
			break;
		case GREEN:
			PTB->PDOR &= ~MASK(GREEN_LED);
			break;
	}
}

void board_led_off(color_t color)
{
	switch(color) {
		case RED:
			PTB->PDOR |= MASK(RED_LED);
			break;
		case GREEN:
			PTB->PDOR |= MASK(GREEN_LED);
			break;
	}
}

void initBoardLED() {
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTD_MASK;

	// configure MUX settings to make all 3 pins GPIO
	// port_pcr_mux_mask is 011100000000
	PORTB->PCR[RED_LED] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[RED_LED] |= PORT_PCR_MUX(1);
	
	PORTB->PCR[GREEN_LED] &= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[GREEN_LED] |= PORT_PCR_MUX(1);
	
	// set the data direction registers for portb and portd
	PTB->PDDR |= MASK(RED_LED) | MASK(GREEN_LED);
	
	board_led_off(RED);
	board_led_off(GREEN);
}

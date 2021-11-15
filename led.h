#ifndef LED_H
#define LED_H

#include <MKL25Z4.h>
#include "gpio.h"

extern GPIO_Type* allTypes[];
extern uint32_t allPinNumbers[];

void onLed(GPIO_Type * gpioType, uint32_t pinNum);
void offLed(GPIO_Type * gpioType, uint32_t pinNum);
void lightFrontTwoGreenLeds(void);
void lightLedOnAndOff(GPIO_Type * gpioType, uint32_t pinNum);
void lightGreenLedsTogether(void);
void offGreenLedsTogether(void);

void lightRedLedsOn(void);
void lightRedLedsOff(void);

void initBoardLED(void);
void board_led_on(color_t color);
void board_led_off(color_t color);

#endif

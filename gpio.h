#ifndef GPIO_H
#define GPIO_H

#include <MKL25Z4.h>
#define LED_STRIP_B_8 	8 // Port B pin 8
#define LED_STRIP_B_9 	9 // Port B pin 9
#define LED_STRIP_B_10 	10 // Port B pin 10
#define LED_STRIP_B_11  11 // Port B pin 11
#define LED_STRIP_E_2 	2 // Port E pin 2
#define LED_STRIP_E_3 	3 // Port E pin 3
#define LED_STRIP_E_4 	4 // Port E pin 4
#define LED_STRIP_E_5 	5 // Port E pin 5

#define LED_STRIP_C_8 	8 // Port C pin 8
#define LED_STRIP_C_9 	9 // Port C pin 9
#define LED_STRIP_C_10 	10 // Port C pin 10
#define LED_STRIP_C_11 	11 // Port C pin 11

#define TRIGGER_D_1 	  1 // Port D pin 1
#define ECHO_D_3				3 // Port D pin 3

enum color { RED, GREEN };
typedef enum color color_t;
#define RED_LED 				18 // PortB Pin 18
#define GREEN_LED 			19 // PortB Pin 19

#define MASK(x) 	(1 << (x))

void initGPIOPorts(PORT_Type *port, GPIO_Type * gpioType, uint32_t pinNum);
void initGreenLedStripPorts(void);
void initRedLedStripPorts(void);
void initTriggerPort(void);
void initEchoPort(void);
void initGPIO(void);

#endif

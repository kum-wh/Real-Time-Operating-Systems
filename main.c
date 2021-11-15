/*----------------------------------------------------------------------------
 * CMSIS-RTOS 'main' function template
 *---------------------------------------------------------------------------*/
 
#include "RTE_Components.h"
#include  CMSIS_device_header
#include "cmsis_os2.h"
#include "common.h"
#include "uart.h"
#include "gpio.h"
#include "led.h"
#include "pwm.h"
#include "audio.h"
#include "motor.h"

/*----------------------------------------------------------------------------
 * Application main thread
 *---------------------------------------------------------------------------*/

volatile uint8_t rx_data = 8;

volatile uint8_t duration = 0;
volatile uint8_t counter = 0;
volatile uint8_t prev_time = 0;
volatile uint8_t isRising = 1;

volatile double dist = 0;

osSemaphoreId_t sem;

// stop, self, boost, right, left, reverse, forward, end
int state = STOP_STATE;

const osThreadAttr_t brainAttr = {
	.priority = osPriorityAboveNormal6
};

const osThreadAttr_t ultraAttr = {
	.priority = osPriorityAboveNormal5
};

void UART2_IRQHandler(void)
{
	NVIC_ClearPendingIRQ(UART2_IRQn);

	if (UART2->S1 & UART_S1_RDRF_MASK)
	{
		// read UART2->D
		rx_data = UART2->D;
		osSemaphoreRelease(sem);
	}
}

void PORTD_IRQHandler() {
	// clear pending IRQ
	NVIC_ClearPendingIRQ(PORTD_IRQn);
	
	// update the variable
	if (PORTD->ISFR & MASK(ECHO_D_3)) {
		if (isRising) {
			prev_time = counter;
		} else {
			duration = counter - prev_time;
			counter = 0;
		}
		isRising = 1 - isRising;
	}
	
	PORTD->ISFR = 0xffffffff;
}

void wifiConnected(void)
{
	lightFrontTwoGreenLeds();
	playWifiConnectedSong();
}

void brainThread(void *argument)
{
	for (;;) {
		osSemaphoreAcquire(sem, osWaitForever);
		if (rx_data == FORWARD) {
			state = FORWARD_STATE;
		} else if (rx_data == REVERSE) {
			state = REVERSE_STATE;
		} else if (rx_data == LEFT) {
			state = LEFT_STATE;
		} else if (rx_data == RIGHT) {
			state = RIGHT_STATE;
		} else if (rx_data == BOOST) {
			state = BOOST_STATE;
		} else if (rx_data == SELF_DRIVE) {
			state = SELF_DRIVE_STATE;
		} else if (rx_data == STOP) {
			state = STOP_STATE;
		} else if (rx_data == END) {
			state = END_STATE;
		} else if (rx_data == FORWARD_LEFT) {
			state = FORWARD_LEFT_STATE;
		} else if (rx_data == FORWARD_RIGHT) {
			state = FORWARD_RIGHT_STATE;
		}
	}
}

void ledGreenThreadInSeries(void *argument)
{
	int i = 0;
	for (;;) {
		if (state & (FORWARD_STATE | BOOST_STATE | REVERSE_STATE | LEFT_STATE | RIGHT_STATE | SELF_DRIVE_STATE | FORWARD_LEFT_STATE | FORWARD_RIGHT_STATE)) {
			offGreenLedsTogether();
			lightLedOnAndOff(allTypes[i], allPinNumbers[i]);
			i++;
			i %= 10;
		}
	}
}

void ledGreenThreadTogether(void *argument)
{
	for (;;) {
		if (state & (STOP_STATE | END_STATE)) {
			lightGreenLedsTogether();
		}
	}
}

void ledRedThreadStationery(void *argument)
{
	int i = 0;
	for (;;) {
		if (state & (STOP_STATE | END_STATE)) {
			if (i == 0) {
				lightRedLedsOn();
				i = 1;
			} else {
				lightRedLedsOff();
				i = 0;
			}
		}
		osDelay(250);
	}
}

void ledRedThreadMoving(void *argument) 
{
	int i = 0;
	for (;;) {
		if (state & (FORWARD_STATE | BOOST_STATE | REVERSE_STATE | LEFT_STATE | RIGHT_STATE | SELF_DRIVE_STATE | FORWARD_LEFT_STATE | FORWARD_RIGHT_STATE)) {
			if (i == 0) {
				lightRedLedsOn();
				i = 1;
			} else {
				lightRedLedsOff();
				i = 0;
			}
		}
		osDelay(500);
	}
}

void motorThread(void *argument)
{
	for (;;) {
		if (state & FORWARD_STATE) {
			moveForward();
		} else if (state & LEFT_STATE) {
			moveLeft();
		} else if (state & RIGHT_STATE) {
			moveRight();
		} else if (state & BOOST_STATE) {
			moveBoost();
		} else if (state & REVERSE_STATE) {
			moveReverse();
		} else if (state & FORWARD_LEFT_STATE) {
			moveForwardAndLeft();
		} else if (state & FORWARD_RIGHT_STATE) {
			moveForwardAndRight();
		} else if (state & (STOP_STATE | END_STATE)) {
			stopMovement();
		} 
	}
}

void ultrasonicThread(void *argument)
{
	int stopDelay = 100;
	int rotateDelay = 300;
	int rightRotateDelay = 250;
	int forwardDelay1 = 450;
	int forwardDelay2 = 400; 
	int isForward = 1;
	int isBackward = 0;
	int isTurning = 0;
	int isEnd = 0;
	for (;;) {
		if (state & SELF_DRIVE_STATE) {
			if (isEnd) {
				stopMovement();
				continue;
			}
			PTD->PDOR &= ~MASK(TRIGGER_D_1);
			osDelay(2);
			PTD->PDOR |= MASK(TRIGGER_D_1);
			osDelay(10);
			PTD->PDOR &= ~MASK(TRIGGER_D_1);
			osDelay(50);
			double time = duration * 0.0005 / 2;
			dist = 343 * time;
			if (isForward) {
				board_led_off(RED);
				board_led_off(GREEN);
				if (dist <= 0.65) {
					isForward = 0;
					isTurning = 1;
					stopMovement();
					moveReverse();
					osDelay(1000);
				} else {
					moveForward();
				}
			}
			if (isTurning) {
				board_led_on(RED);
				board_led_off(GREEN);
				moveLeft();
				osDelay(rotateDelay);
				moveForward();
				osDelay(forwardDelay1);
				
				stopMovement();
				osDelay(stopDelay);
				
				moveRight();
				osDelay(rightRotateDelay * 2);
				moveForward();
				osDelay(forwardDelay1);
				
				stopMovement();
				osDelay(stopDelay);
				
				moveRight();
				osDelay(rightRotateDelay * 2);
				moveForward();
				osDelay(forwardDelay1);
				
				stopMovement();
				osDelay(stopDelay);
				
				moveRight();
				osDelay(rightRotateDelay * 2);
				moveForward();
				osDelay(forwardDelay1);
				
				stopMovement();
				osDelay(stopDelay);
				
				moveLeft();
				osDelay(rotateDelay);
				stopMovement();
				isTurning = 0;
				isBackward = 1;
				dist = 1000;
			}
			if (isBackward) {
				board_led_on(RED);
				board_led_on(GREEN);
				if (dist <= 0.55) {
					stopMovement();
					isBackward = 1;
					isEnd = 1;
					state = END_STATE;
				} else {
					moveForward();
				}
			}
		}
	}
}

void end_music_thread(void *argument) {
	for (;;) {
		if (state & END_STATE) {
			playEndingTune();
		}
	}
}

void looping_music_thread(void *argument) {
	for (;;) {
		if (state & ~END_STATE) {
			playLoopingTune();
		}
	}
}

void PIT_IRQHandler() {
	NVIC_ClearPendingIRQ(PIT_IRQn); //Enable the PIT interrupt in the NVIC 
	if (PIT->CHANNEL[0].TFLG & PIT_TFLG_TIF_MASK) {
		counter++;
	}
	//Clear interrupt request flag for channel 
	PIT->CHANNEL[0].TFLG &= PIT_TFLG_TIF_MASK; 
}

void initClock() {
	SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;
	PIT->MCR &= ~PIT_MCR_MDIS_MASK;
	
	PIT->CHANNEL[0].LDVAL |= 0x1479;
	PIT->CHANNEL[0].TCTRL &= PIT_TCTRL_CHN_MASK;
	PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TEN_MASK;
	
	PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TIE_MASK;
	
	NVIC_SetPriority(PIT_IRQn, 2);
	NVIC_EnableIRQ(PIT_IRQn);
}
 
int main (void) {
 
  // System Initialization
  SystemCoreClockUpdate();
  initUART(BAUD_RATE);
	initGPIO();
	initPWM();
	initClock();
	initBoardLED();
	while (rx_data != 0);
	wifiConnected();
	
  osKernelInitialize();                 // Initialize CMSIS-RTOS
	sem = osSemaphoreNew(1, 0, NULL);
	osThreadNew(brainThread,NULL,&brainAttr);
	osThreadNew(ledGreenThreadInSeries, NULL, NULL);
	osThreadNew(ledGreenThreadTogether, NULL, NULL);
	osThreadNew(ledRedThreadMoving, NULL, NULL);
	osThreadNew(ledRedThreadStationery, NULL, NULL);
	osThreadNew(motorThread, NULL, NULL);
	osThreadNew(ultrasonicThread, NULL, NULL);
	osThreadNew(looping_music_thread, NULL, NULL);
	osThreadNew(end_music_thread, NULL, NULL);
  osKernelStart();                      // Start thread execution*/
  for (;;) {}
}

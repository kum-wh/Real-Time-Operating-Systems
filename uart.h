#ifndef UART_H
#define UART_H

#include <MKL25Z4.h>
#define UART2_TX_PIN 22
#define UART2_RX_PIN 23
#define UART2_INT_PRIO 128 
#define BAUD_RATE 9600

extern volatile uint8_t rx_data;
void initUART(uint32_t baud_rate);

#endif

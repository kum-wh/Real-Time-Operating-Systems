#include "uart.h"
#include <MKL25Z4.h>

void initUART(uint32_t baud_rate)
{
	uint32_t divisor, bus_clock;
	
	SIM_SCGC4 |= SIM_SCGC4_UART2_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
	
	// set to use ALT 4 in PTE22 and PTE23 to use UART2
	PORTE->PCR[UART2_TX_PIN] &= ~PORT_PCR_MUX_MASK;
	PORTE->PCR[UART2_TX_PIN] |= PORT_PCR_MUX(4);
	PORTE->PCR[UART2_RX_PIN] &= ~PORT_PCR_MUX_MASK;
	PORTE->PCR[UART2_RX_PIN] |= PORT_PCR_MUX(4);
	
	// ensure transmitter enable and receiver enable are disabled before configuration
	UART2->C2 &= ~((UART_C2_TE_MASK | UART_C2_RE_MASK));
	
	// docs stated that the 13 bit baud rate setting [SBR12:0] can only be updated when
	// transmitter and receiver are both disabled
	bus_clock = (DEFAULT_SYSTEM_CLOCK)/2;
	
	// fixed 16x oversampling for UART2 and UART1 to improve noise immunity
	// baud_rate = UART_MODULE_CLOCK / (SBR[12:0] * 16)
	divisor = bus_clock / (baud_rate * 16);
	UART2->BDH |= UART_BDH_SBR(divisor >> 8);
	UART2->BDL |= UART_BDL_SBR(divisor);
	
	// 8 bit mode no parity mode
	UART2->C1 = 0;
	UART2->S2 = 0;
	UART2->C3 = 0;
	
	UART2->C2 |= (UART_C2_TE_MASK | UART_C2_RE_MASK);
	
	NVIC_SetPriority(UART2_IRQn, UART2_INT_PRIO);
	NVIC_ClearPendingIRQ(UART2_IRQn);
	NVIC_EnableIRQ(UART2_IRQn);
	
	UART2->C2 |= UART_C2_RIE_MASK;
}

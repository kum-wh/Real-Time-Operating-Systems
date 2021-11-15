#include "common.h"
#include <MKL25Z4.h>

void delay(volatile uint32_t nof)
{
	while (nof != 0)
	{
		__ASM("NOP");
		nof--;
	}
}

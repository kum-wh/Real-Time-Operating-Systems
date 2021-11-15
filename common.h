#ifndef COMMON_H
#define COMMON_H

#include <MKL25Z4.h>

#define FORWARD				0x1
#define REVERSE				0x2
#define LEFT 					0x3
#define RIGHT 				0x4
#define BOOST 				0x5
#define SELF_DRIVE 		0x6
#define STOP 					0x7
#define END 					0x8
#define FORWARD_LEFT 	0x9
#define FORWARD_RIGHT 0x10

#define FORWARD_STATE					MASK(FORWARD - 1)
#define REVERSE_STATE					MASK(REVERSE - 1)
#define LEFT_STATE			 			MASK(LEFT - 1)
#define RIGHT_STATE			 			MASK(RIGHT - 1)
#define BOOST_STATE			 			MASK(BOOST - 1)
#define SELF_DRIVE_STATE			MASK(SELF_DRIVE - 1)
#define STOP_STATE			 			MASK(STOP - 1)
#define END_STATE        			MASK(END - 1)
#define FORWARD_LEFT_STATE		MASK(FORWARD_LEFT - 1)
#define FORWARD_RIGHT_STATE   MASK(FORWARD_RIGHT - 1)

void delay(volatile uint32_t nof);

#endif

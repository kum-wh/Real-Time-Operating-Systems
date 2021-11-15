#include "motor.h"
#include <MKL25Z4.h>

const int COUNT = 3000;
const int LEFT_COUNT = 4000;
const int RIGHT_COUNT = 4500;
const int LEFT_COUNT_FOR_RIGHT_TURN = 6000;
const int RIGHT_COUNT_FOR_RIGHT_TURN = 1000;
const int LEFT_COUNT_FOR_LEFT_TURN = 1000;
const int RIGHT_COUNT_FOR_LEFT_TURN = 6000;
const int LEFT_BOOSTCOUNT = 6000;
const int RIGHT_BOOSTCOUNT = 6500;

void moveForwardAndLeft(void)
{
	TPM1_C0V = RIGHT_COUNT_FOR_LEFT_TURN;
	TPM1_C1V = LEFT_COUNT_FOR_LEFT_TURN;
	TPM2_C0V = 0;
	TPM2_C1V = 0;
}

void moveForwardAndRight(void)
{
	TPM1_C0V = RIGHT_COUNT_FOR_RIGHT_TURN;
	TPM1_C1V = LEFT_COUNT_FOR_RIGHT_TURN;
	TPM2_C0V = 0;
	TPM2_C1V = 0;
}

void moveForward(void)
{
	TPM1_C0V = RIGHT_COUNT;
	TPM1_C1V = LEFT_COUNT;
	TPM2_C0V = 0;
	TPM2_C1V = 0;
}

void moveLeft(void)
{
	TPM1_C0V = COUNT;
	TPM1_C1V = 0;
	TPM2_C0V = 0;
	TPM2_C1V = COUNT;
}

void moveRight(void)
{
	TPM1_C0V = 0;
	TPM1_C1V = COUNT;
	TPM2_C0V = COUNT;
	TPM2_C1V = 0;
}

void moveBoost(void)
{
	TPM1_C0V = RIGHT_BOOSTCOUNT;
	TPM1_C1V = LEFT_BOOSTCOUNT;
	TPM2_C0V = 0;
	TPM2_C1V = 0;
}

void stopMovement(void)
{
	TPM1_C0V = 0;
	TPM1_C1V = 0;
	TPM2_C0V = 0;
	TPM2_C1V = 0;
}

void moveReverse (void)
{
	TPM1_C0V = 0;
	TPM1_C1V = 0;
	TPM2_C0V = RIGHT_COUNT;
	TPM2_C1V = LEFT_COUNT;
}

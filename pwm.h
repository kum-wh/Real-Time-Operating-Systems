#ifndef PWM_H
#define PWM_H

#include <MKL25Z4.h>
#define TPM1_CHANNEL_1_PTB1_PIN	1 
#define TPM2_CHANNEL_0_PTB2_PIN 2
#define TPM2_CHANNEL_1_PTB3_PIN 3

#define TPM0_CHANNEL_2_PTA5_PIN 5
#define TPM1_CHANNEL_0_PTE20_PIN	20


void initPWM(void);


#endif

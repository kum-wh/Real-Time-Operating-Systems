#include "pwm.h"
#include <MKL25Z4.h>

void initPWMPorts(PORT_Type *port, uint32_t pinNum)
{
	port->PCR[pinNum] &= ~PORT_PCR_MUX_MASK;
	port->PCR[pinNum] |= PORT_PCR_MUX(3);
}

void initPWM()
{
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
	
	// check that you dont use portA 0, portA 3
	initPWMPorts(PORTE, TPM1_CHANNEL_0_PTE20_PIN);
	initPWMPorts(PORTB, TPM1_CHANNEL_1_PTB1_PIN);
	initPWMPorts(PORTB, TPM2_CHANNEL_1_PTB3_PIN);
	initPWMPorts(PORTB, TPM2_CHANNEL_0_PTB2_PIN);
	initPWMPorts(PORTA, TPM0_CHANNEL_2_PTA5_PIN);
	
	SIM->SCGC6 |= SIM_SCGC6_TPM1_MASK;
	SIM->SCGC6 |= SIM_SCGC6_TPM2_MASK;
	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;
	
  SIM->SOPT2 &= ~SIM_SOPT2_TPMSRC_MASK;
  SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1);
  
	TPM0->MOD = 7500;
  TPM1->MOD = 7500;
	TPM2->MOD = 7500;
  
	TPM0->SC &= ~((TPM_SC_CMOD_MASK) | (TPM_SC_PS_MASK));
	TPM0->SC |= (TPM_SC_CMOD(1) | TPM_SC_PS(7));
	TPM0->SC &= ~(TPM_SC_CPWMS_MASK);
	
	TPM0_C2SC &= ~((TPM_CnSC_ELSB_MASK) | (TPM_CnSC_ELSA_MASK) | (TPM_CnSC_MSB_MASK) | (TPM_CnSC_MSA_MASK));
	TPM0_C2SC |= (TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1));
	
  TPM1->SC &= ~((TPM_SC_CMOD_MASK) | (TPM_SC_PS_MASK)); 
	TPM1->SC |= (TPM_SC_CMOD(1) | TPM_SC_PS(7)); 
	TPM1->SC &= ~(TPM_SC_CPWMS_MASK); 
  
	TPM2->SC &= ~((TPM_SC_CMOD_MASK) | (TPM_SC_PS_MASK)); 
	TPM2->SC |= (TPM_SC_CMOD(1) | TPM_SC_PS(7)); 
	TPM2->SC &= ~(TPM_SC_CPWMS_MASK); 
  
	TPM1_C0SC &= ~((TPM_CnSC_ELSB_MASK) | (TPM_CnSC_ELSA_MASK) | (TPM_CnSC_MSB_MASK) | (TPM_CnSC_MSA_MASK)); 
	TPM1_C0SC |= (TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1)); 
  
	TPM1_C1SC &= ~((TPM_CnSC_ELSB_MASK) | (TPM_CnSC_ELSA_MASK) | (TPM_CnSC_MSB_MASK) | (TPM_CnSC_MSA_MASK)); 
	TPM1_C1SC |= (TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1)); 
  
	TPM2_C0SC &= ~((TPM_CnSC_ELSB_MASK) | (TPM_CnSC_ELSA_MASK) | (TPM_CnSC_MSB_MASK) | (TPM_CnSC_MSA_MASK)); 
	TPM2_C0SC |= (TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1)); 
  
	TPM2_C1SC &= ~((TPM_CnSC_ELSB_MASK) | (TPM_CnSC_ELSA_MASK) | (TPM_CnSC_MSB_MASK) | (TPM_CnSC_MSA_MASK)); 
	TPM2_C1SC |= (TPM_CnSC_ELSB(1) | TPM_CnSC_MSB(1)); 
}

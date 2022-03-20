#include "lm4f120h5qr.h"
#include "io.h"
#include "functions.h"

void DEBUG_delay(int time)
{
for(int i = 0; i < time; i++)
  for(int j = 0; j < 3180; j++)
  {} //NOPS
}

void DEBUG_OUTPUT_TEST()
{
  PUMP_1_ON();
  DEBUG_delay(20);
  PUMP_1_OFF();
  DEBUG_delay(20);
  PUMP_2_ON();
  DEBUG_delay(20);
  PUMP_2_OFF();
  DEBUG_delay(20);
  FAULT_P1_P2_RELAIE_ON(); //PB2
  DEBUG_delay(20);
  FAULT_P1_P2_RELAIE_OFF(); //PB2
  DEBUG_delay(20);
  FAULT_RELAIE_P1_ON(); //PB0
  DEBUG_delay(20);
  FAULT_RELAIE_P1_OFF(); //PB0
  DEBUG_delay(20);
  FAULT_RELAIE_P2_ON(); //PB1
  DEBUG_delay(20);
  FAULT_RELAIE_P2_OFF(); //PB1
  DEBUG_delay(20);
}

//Interupt
void init_NVIC_PORTE(void)
{
   NVIC_EN0_R |= (1<<4);
}

void GPIO_PORTE_INTERRUPT(void)
 {
  GPIO_PORTF_DATA_R |= LED_GREEN; 
  GPIO_PORTE_ICR_R |= SENS_HIGH_WATER | SENS_P2_WATER | SENS_P1_WATER | SENS_DRYRUN;
  DEBUG_delay(500);
  GPIO_PORTF_DATA_R &= ~LED_GREEN;
  
 }
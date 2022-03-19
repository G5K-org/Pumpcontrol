#include "lm4f120h5qr.h"
#include "io.h"
#include "functions.h"

int main()
{ 
  
  //OUTPUT STATUS ARRAY
  
 
  
  init_PORTB();
  config_PORTB();
  
  init_PORTE();
  config_PORTE();
  
  init_PORTF();
  config_PORTF();
  
  
  while(1)
  {

  PUMP_1_ON();
  DEBUG_delay(20);
  PUMP_1_OFF();
  DEBUG_delay(20);
  PUMP_2_ON();
  DEBUG_delay(20);
  PUMP_2_OFF();

  FAULT_RELAIE_P1_ON(); //PB0
  DEBUG_delay(20);
  FAULT_RELAIE_P1_OFF(); //PB0
  DEBUG_delay(20);
  FAULT_RELAIE_P2_ON(); //PB1
  DEBUG_delay(20);
  FAULT_RELAIE_P2_OFF(); //PB1
  DEBUG_delay(20);
  FAULT_P1_P2_RELAIE_ON(); //PB2
  DEBUG_delay(20);
  FAULT_P1_P2_RELAIE_OFF(); //PB2
  DEBUG_delay(20);
 
  
  }
  return 0;
}



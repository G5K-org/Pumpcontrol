/*
  





*/



#include "lm4f120h5qr.h"
#include <stdbool.h>
#include "io.h"
#include "functions.h"
#include <stdint.h>
#include <stdio.h>

#define ENABLE 1


int main()
{ 

  init_PORTB();
  config_PORTB();
  
  init_PORTE();
  config_PORTE();
  //init_NVIC_PORTE();
  
  init_PORTF();
  config_PORTF();
  
while(1)
{
//DIGITAL_IN_STATUS_PORTE(ENABLE);
GPIO_PORTB_DATA_R = 0;
DEBUG_delay(1000);
FAULT_P1_P2_RELAIE_ON();
DEBUG_delay(1000);
FAULT_RELAIE_P1_ON();
DEBUG_delay(1000);
FAULT_RELAIE_P2_ON();
DEBUG_delay(1000);

}
return 0;
}
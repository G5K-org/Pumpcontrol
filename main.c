#include "lm4f120h5qr.h"
#include <stdbool.h>
#include "io.h"
#include "functions.h"
#include <stdint.h>
#include <stdio.h>

#define ACTIVE 1


int main()
{ 

  init_PORTB();
  config_PORTB();
  
  init_PORTE();
  config_PORTE();
  init_NVIC_PORTE();
  
  init_PORTF();
  config_PORTF();
  
while(1)
{
  //DEBUG_OUTPUT_TEST();
  NORMAL_MODE(DIGI_SENSE(),ACTIVE);
  FAIL_CHECK(DIGI_SENSE(),ACTIVE);
}
return 0;
}
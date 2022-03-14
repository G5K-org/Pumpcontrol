#include "lm4f120h5qr.h"
#include "io.h"
#include "functions.h"

int main()
{
  init_PORTB();
  config_PORTB();
  
  init_PORTE();
  config_PORTE();
  
  init_PORTF();
  config_PORTF();
  
  GPIO_PORTF_DATA_R = 0;
  while(1)
  {
  GPIO_PORTF_DATA_BITS_R[LED_WHITE] |= LED_WHITE; 
  }
  return 0;
}



#include "lm4f120h5qr.h"
#include "io.h"
#include "functions.h"

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
   DEBUG_OUTPUT_TEST();
  }
  return 0;
}



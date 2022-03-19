#include "lm4f120h5qr.h"
#include "io.h"
#include "functions.h"

void DEBUG_delay(int time)
{


for(int i = 0; i < time; i++)
  for(int j = 0; j < 3180; j++)
  {} //NOPS
}
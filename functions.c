#include "lm4f120h5qr.h"
#include "io.h"
#include "functions.h"





//FUNCTIONS

void init_PORTB()
{
 SYSCTL_RCGCGPIO_R |= PORTB;
}
void config_PORTB()
{
 GPIO_PORTB_DEN_R |= FAULT_OUT_RELAIE | FAULT_P1 | FAULT_P1;
 GPIO_PORTB_DIR_R |= FAULT_OUT_RELAIE | FAULT_P1 | FAULT_P1;
}

void init_PORTE()
{
 SYSCTL_RCGCGPIO_R |= PORTE;
}

void config_PORTE()
{
 GPIO_PORTE_DEN_R |= SENS_HIGH_WATER | SENS_P2_WATER | SENS_P1_WATER | SENS_DRYRUN;
 GPIO_PORTE_DIR_R &= ~(SENS_HIGH_WATER | SENS_P2_WATER | SENS_P1_WATER | SENS_DRYRUN);
}
void init_PORTF()
{
    SYSCTL_RCGCGPIO_R |= PORTF;    
}

void config_PORTF()
{
   GPIO_PORTF_DEN_R |= LED_RED | LED_GREEN | LED_BLUE;
   GPIO_PORTF_DIR_R |= LED_RED | LED_GREEN | LED_BLUE;
   GPIO_PORTF_DIR_R &= ~QUITT_SW;
}


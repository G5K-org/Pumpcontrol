#include "io.h"
#include "lm4f120h5qr.h"
#include "functions.h"

//OUTPUT STATUS ARRAY 
// { PUMP1, PUMP2, FAULT_COLLECTOR, FAULT_P1, FAULT_P2 }
static int STATUS_OUTPUT[5] = { 0, 0, 0, 0, 0 };
//init config
void init_PORTB()
{
 SYSCTL_RCGCGPIO_R |= PORTB;
}
void config_PORTB()
{
 GPIO_PORTB_DEN_R |= FAULT_OUT_RELAIE | FAULT_P1 | FAULT_P1 | PUMP1 | PUMP2;
 GPIO_PORTB_DIR_R |= FAULT_OUT_RELAIE | FAULT_P1 | FAULT_P1 | PUMP1 | PUMP2;
 GPIO_PORTB_PDR_R |= FAULT_OUT_RELAIE | FAULT_P1 | FAULT_P1 | PUMP1 | PUMP2;
}
void init_PORTE()
{
 SYSCTL_RCGCGPIO_R |= PORTE;
}
void config_PORTE()
{
 //DIGITAL
 GPIO_PORTE_DEN_R |= SENS_HIGH_WATER | SENS_P2_WATER | SENS_P1_WATER | SENS_DRYRUN;
 GPIO_PORTE_DIR_R &= ~(SENS_HIGH_WATER | SENS_P2_WATER | SENS_P1_WATER | SENS_DRYRUN);
 GPIO_PORTE_PUR_R |= SENS_HIGH_WATER | SENS_P1_WATER | SENS_P2_WATER | SENS_DRYRUN;
 
 //Interrupt
 GPIO_PORTE_IM_R = 0;
 GPIO_PORTE_IS_R &= ~(SENS_HIGH_WATER | SENS_DRYRUN | SENS_P1_WATER | SENS_P1_WATER);
 GPIO_PORTE_IBE_R &= ~(SENS_HIGH_WATER | SENS_DRYRUN | SENS_P1_WATER | SENS_P1_WATER);
 GPIO_PORTE_IEV_R &= ~(SENS_HIGH_WATER | SENS_DRYRUN | SENS_P1_WATER | SENS_P1_WATER);
 GPIO_PORTE_RIS_R = 0;
 GPIO_PORTE_IM_R |= SENS_HIGH_WATER | SENS_DRYRUN | SENS_P1_WATER | SENS_P1_WATER;
 GPIO_PORTE_IM_R &= ~(SENS_ANA_MQ7 | SENS_P1_WATER | SENS_P2_WATER);

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

//OUTPUT FUNCTIONS
//PUMPS
void PUMP_1_ON()
{
GPIO_PORTB_DATA_BITS_R[PUMP1] = PUMP1;
STATUS_OUTPUT[0] = 1;
}
void PUMP_1_OFF()
{
  GPIO_PORTB_DATA_BITS_R[PUMP1] &= ~PUMP1;
  STATUS_OUTPUT[0] = 0;
}
void PUMP_2_ON()
{
GPIO_PORTB_DATA_BITS_R[PUMP2] |= PUMP2;
STATUS_OUTPUT[1] = 1;
}
void PUMP_2_OFF()
{
GPIO_PORTB_DATA_BITS_R[PUMP2] &= ~PUMP2;
STATUS_OUTPUT[1] = 0;  
}

//RELAIS
void FAULT_RELAIE_P1_ON()
{
  GPIO_PORTB_DATA_BITS_R[FAULT_P1] |= FAULT_P1; 
  STATUS_OUTPUT[3] = 1;
}
void FAULT_RELAIE_P1_OFF()
{
  GPIO_PORTB_DATA_BITS_R[FAULT_P1] &= ~FAULT_P1;
  STATUS_OUTPUT[3] = 0;
}

void FAULT_RELAIE_P2_ON()
{
  GPIO_PORTB_DATA_R |= FAULT_P2;
  STATUS_OUTPUT[4] = 1;
}
void FAULT_RELAIE_P2_OFF()
{
  GPIO_PORTB_DATA_BITS_R[FAULT_P2] &= ~FAULT_P2;
  STATUS_OUTPUT[4] = 0;
}

void FAULT_P1_P2_RELAIE_ON()
{
 GPIO_PORTB_DATA_BITS_R[FAULT_OUT_RELAIE] |= FAULT_OUT_RELAIE;
 STATUS_OUTPUT[2] = 1;
}
void FAULT_P1_P2_RELAIE_OFF()
{
 GPIO_PORTB_DATA_BITS_R[FAULT_OUT_RELAIE] &= ~FAULT_OUT_RELAIE;
 STATUS_OUTPUT[2] = 0;
}




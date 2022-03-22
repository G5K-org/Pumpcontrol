#include "lm4f120h5qr.h"
#include "io.h"
#include "functions.h"

////////////////////////DEBUG//////////////////////////////////
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
///////////////////////////////////////////////////////////////

////////////////////////Interupt//////////////////////////////
void init_NVIC_PORTE(void)
{
   NVIC_EN0_R |= (1<<4);
}


void GPIO_PORTE_INTERRUPT(void) //===============PLAUSIBILITÄTS CHECK================================ ÜBERBLEIBSEL
 {

 GPIO_PORTE_ICR_R |= SENS_HIGH_WATER | SENS_DRYRUN| SENS_P1_WATER | SENS_P1_WATER;   
 }


/////////////////////////////////////////////////////////////
//Schwimmerschalter DIGITAL Eingänge

int* DIGI_SENSE(void)
{
    static int STATUS_INPUT[4] = { 0, 0, 0, 0};

      if((GPIO_PORTE_DATA_BITS_R[SENS_DRYRUN] & SENS_DRYRUN) == 0)  //Sensor Trockenlauf
      {
      //GPIO_PORTF_DATA_R |= LED_RED;
      DEBUG_delay(2);
      STATUS_INPUT[0] = 1;
      }
      else
      {
      //GPIO_PORTF_DATA_R &= ~LED_RED;
      STATUS_INPUT[0] = 0;
      }
      
      if((GPIO_PORTE_DATA_BITS_R[SENS_P1_WATER] & SENS_P1_WATER) == 0) //Sensor Pumpe 1
      {
      //GPIO_PORTF_DATA_R |= LED_BLUE;
      DEBUG_delay(2);
      STATUS_INPUT[1] = 1;
      }
      else
      {
      //GPIO_PORTF_DATA_R &= ~LED_BLUE;
      STATUS_INPUT[1] = 0;
      }
      if((GPIO_PORTE_DATA_BITS_R[SENS_P2_WATER] & SENS_P2_WATER) == 0) //Sensor Pumpe 2
      {
      //GPIO_PORTF_DATA_R |= LED_WHITE;
      DEBUG_delay(2);
      STATUS_INPUT[2] = 1;
      }
      else
      {
      //GPIO_PORTF_DATA_R &= ~LED_WHITE;
      STATUS_INPUT[2] = 0;
      }
      if((GPIO_PORTE_DATA_BITS_R[SENS_HIGH_WATER] & SENS_HIGH_WATER) == 0) //High Water
      {
      //GPIO_PORTF_DATA_R |= LED_WHITE;
      DEBUG_delay(2);
      STATUS_INPUT[3] = 1;
      }
      else
      {
      //GPIO_PORTF_DATA_R &= ~LED_WHITE;
      STATUS_INPUT[3] = 0;
      }
           
   return STATUS_INPUT;
}

/////////////////////////////////////////////////////////////
int NORMAL_MODE(int* DIGI_sensors, int active)
{
 if(active == 1)
 {
if(((DIGI_sensors[0] == 1) && (DIGI_sensors[1] == 1) && (DIGI_sensors[2] == 1) && (DIGI_sensors[3] == 1))) //HIGH WATER ALARM P1 P2
  {
  PUMP_1_ON();
  PUMP_2_ON();
  GPIO_PORTF_DATA_R = LED_BLUE;
  //LED BLINKT ERROR HUPE ETC.
  }
if((DIGI_sensors[0] == 1) && (DIGI_sensors[1] == 1) && DIGI_sensors[2] == 1) //P1 and P2 active
  {
   PUMP_1_ON();
   PUMP_2_ON();
   GPIO_PORTF_DATA_R = LED_RED;
  }
if((DIGI_sensors[0] == 1) && (DIGI_sensors[1] == 1)) //P1 active
  {
  PUMP_1_ON();
  GPIO_PORTF_DATA_R = LED_WHITE;
  return 1;
  }
if(DIGI_sensors[0] == 0) //Dryrun (Water level must be)
  {
  //delay
  //If 0 ERROR WASSERSTAND ZU NIEDRIG
  GPIO_PORTF_DATA_R = LED_GREEN;
  return 1;
  }

else
  GPIO_PORTF_DATA_R = 0;
  PUMP_1_OFF();
  PUMP_2_OFF();
  return 0;
 }
 return 0;
}

void FAIL_CHECK(int* DIGI_sensor,int active)
{
  if(active == 1)
  {
  if((DIGI_sensor[0] == 1) && (DIGI_sensor[1] == 1) && (DIGI_sensor[2] == 1) && (DIGI_sensor[3] == 1)) 
  {
  //HOCHWASSER ALARM
  FAULT_P1_P2_RELAIE_ON(); //SAMMELSTÖRUNG
  GPIO_PORTF_DATA_R = LED_BLUE;
  printf("HW\n");
  }
  if((DIGI_sensor[0] == 1) && (DIGI_sensor[1] == 0) && (DIGI_sensor[2] == 1) && (DIGI_sensor[3] == 1)) 
  {
  //FEHLER
  FAULT_P1_P2_RELAIE_ON();//SAMMELSTÖRUNG
  GPIO_PORTF_DATA_R = LED_GREEN;
  printf("SS\n");
  }
  if((DIGI_sensor[0] == 1) && (DIGI_sensor[1] == 0) && (DIGI_sensor[2] == 0) && (DIGI_sensor[3] == 1))
  {
  //FEHLER
  FAULT_P1_P2_RELAIE_ON(); //SAMMELSTÖRUNG 
  GPIO_PORTF_DATA_R = LED_RED;
  printf("SS1\n");
  }
  if((DIGI_sensor[0] == 1) && (DIGI_sensor[1] == 0) && (DIGI_sensor[2] == 0) && (DIGI_sensor[3] == 0))
  {
  //FEHLER
  FAULT_P1_P2_RELAIE_ON(); //SAMMELSTÖRUNG
  GPIO_PORTF_DATA_R = (LED_RED | LED_GREEN);
  printf("SS2\n");
  }
  if((DIGI_sensor[0] == 0) && (DIGI_sensor[1] == 1) && (DIGI_sensor[2] == 0) && (DIGI_sensor[3] == 0))
  {
  //FEHLER
  FAULT_P1_P2_RELAIE_ON(); //SAMMELSTÖRUNG 
  GPIO_PORTF_DATA_R = (LED_GREEN | LED_BLUE);
  printf("SS3\n");
  }
  if((DIGI_sensor[0] == 0) && (DIGI_sensor[1] == 0) && (DIGI_sensor[2] == 1) && (DIGI_sensor[3] == 0))
  {
  //FEHLER
  FAULT_P1_P2_RELAIE_ON(); //SAMMELSTÖRUNG
  GPIO_PORTF_DATA_R = (LED_RED | LED_BLUE);
  printf("SS4\n");
  }
  if((DIGI_sensor[0] == 0) && (DIGI_sensor[1] == 0) && (DIGI_sensor[2] == 0) && (DIGI_sensor[3] == 1))
  {
  //DRYRUN OK
  printf("DRYRUN OK\n");
  }
  if((DIGI_sensor[0] == 0) && (DIGI_sensor[1] == 0) && (DIGI_sensor[2] == 0) && (DIGI_sensor[3] == 0))
  {
  //DRYRUN FAILURE
  FAULT_P1_P2_RELAIE_ON();//SAMMELSTÖRUNG
  printf("DRYRUN FAILURE\n");
  }
  }
}


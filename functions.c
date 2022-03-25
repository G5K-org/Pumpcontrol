#include "lm4f120h5qr.h"
#include "io.h"
#include "functions.h"
#include <stdio.h>

void DEBUG_delay(int time)
{
for(int i = 0; i < time; i++)
  for(int j = 0; j < 3180; j++)
  {} //NOPS
}

void DEBUG_OUTPUT_TEST()
{
  DEBUG_delay(20);
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

void init_NVIC_PORTE(void)
{
   NVIC_EN0_R |= (1<<4);
}


void GPIO_PORTE_INTERRUPT(void) 
 {
 GPIO_PORTE_ICR_R |= SENS_HIGH_WATER | SENS_DRYRUN| SENS_P1_WATER | SENS_P1_WATER;   
 }


int DIGITAL_IN_STATUS_PORTE(int active)
{
  if(active == 1)
  {
    switch(GPIO_PORTE_DATA_R)
  {
  case 0x0F: printf("0x0F\n");                                                  // 1111 15 Dryrun Trockenlaufschutz
             low_on_water_dryrun();
             return 1;
             break;
  case 0x0E: printf("0x0E OK\n");                                               // 1110 14  OK Wasserstand ausreichend hoch keine Gefahr des Trockenlaufs                                       
             //OK                                                               // Sollwert
             PUMP_1_OFF();
             PUMP_2_OFF();
             return 0;
             break;
  case 0x0D: printf("0x0D\n");                                                  // 1101 13  Fehler
             not_plausible();  
             low_on_water_dryrun();
             break;
  case 0x0C: printf("0x0C\n");                                                  // 1100 12 OK Pumpe 1 einschalten 
             //OK
             PUMP_1_ON();
             break;
  case 0x0B: printf("0x0B\n");                                                  // 1011  11 Fehler
             not_plausible();
             no_sensor_data("0x0B\n");
             break;
  case 0x0A: printf("0x0A\n");                                                  // 1010  10 Fehler
             not_plausible();
             no_sensor_data("0x0A\n");
             break;
  case 0x09: printf("0x09\n");                                                  // 1001  9  Fehler
             not_plausible();
             no_sensor_data("0x09\n");
             break;
  case 0x08: printf("0x08 OK\n");                                               // 1000 8   OK Pumpe 2 dazuschalten bzw beide einschalten
             //OK
             PUMP_1_ON();
             PUMP_2_ON();
             break;
  case 0x07: printf("0x07\n");                                                  // 0111 7   Fehler                                        
             not_plausible();
             no_sensor_data("0x07\n");
             low_on_water_dryrun();
             break;
  case 0x06: printf("0x06\n");                                                  // 0110 6   Fehler
             not_plausible();
             no_sensor_data("0x06\n");
             break;
  case 0x05: printf("0x05\n");                                                  // 0101 5  Fehler
             not_plausible();
             no_sensor_data("0x05\n");
             break;
  case 0x04: printf("0x04\n");                                                  // 0100 4  Fehler
             not_plausible();
             no_sensor_data("0x04\n");
             break;
  case 0x03: printf("0x03\n");                                                  // 0011 3  Fehler
             not_plausible();
             no_sensor_data("0x03\n");
             break;
  case 0x02: printf("0x02\n");                                                  // 0010 2 Fehler  
             not_plausible();
             no_sensor_data("0x02\n");
             break;
  case 0x01: printf("0x01\n");                                                  // 0001 1  Fehler 
             not_plausible();
             low_on_water_dryrun();
             break;
  case 0x00: printf("0x00 OK\n");                                               // 0000   //Hochwasser
             PUMP_1_ON();
             PUMP_2_ON();
             highwater_alarm();
             break;
  }
  
  }
  return 0;
}

void not_plausible()
{
printf(" | not_plausible ");
PUMP_1_OFF();
PUMP_2_OFF();
FAULT_P1_P2_RELAIE_ON();
}

void low_on_water_dryrun()
{
printf(" | low on water!! ");
PUMP_1_OFF();
PUMP_2_OFF();
FAULT_P1_P2_RELAIE_ON();
}

void no_sensor_data(const char* sensor)
{
printf("no_sensor_data");
PUMP_1_OFF();
PUMP_2_OFF();
FAULT_P1_P2_RELAIE_ON();
}

void highwater_alarm(void)
{
  printf("High Water\n");
  FAULT_P1_P2_RELAIE_ON();
  
}

void quit_failure(void)
{
  FAULT_P1_P2_RELAIE_OFF();
  FAULT_RELAIE_P1_OFF();
  FAULT_RELAIE_P2_OFF();

}
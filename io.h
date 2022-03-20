#ifndef __IO
#define __IO



//PORTS
#define PORTB (1<<1)
#define PORTE (1<<4)
#define PORTF (1<<5)

//INPUTS
//PE
#define SENS_HIGH_WATER   (1<<0)
#define SENS_P2_WATER     (1<<1) 
#define SENS_P1_WATER     (1<<2)
#define SENS_DRYRUN       (1<<3)
#define SENS_ANA_MQ7      (1<<4) //p801 //p651

//PF
#define QUITT_SW          (1<<4)

//OUTPUTS
//PB
#define PUMP1                     (1<<0)
#define PUMP2                     (1<<1)
#define FAULT_OUT_RELAIE          (1<<2)
#define FAULT_P1                  (1<<3)
#define FAULT_P2                  (1<<4)
//PF
#define LED_RED                   (1<<1)
#define LED_GREEN                 (1<<3)
#define LED_BLUE                  (1<<2)
#define LED_WHITE                 (14<<0)         //0b 0000 1110


//PROTOTYPES
void init_PORTB(void);
void config_PORTB(void);

void init_PORTE(void);
void config_PORTE(void);

void init_PORTF(void);
void config_PORTF();

void PUMP_1_ON(void);
void PUMP_1_OFF(void);
void PUMP_2_ON(void);
void PUMP_2_OFF(void);

void FAULT_RELAIE_P1_ON(void);
void FAULT_RELAIE_P1_OFF(void);
void FAULT_RELAIE_P2_ON(void);
void FAULT_RELAIE_P2_OFF(void);
void FAULT_P1_P2_RELAIE_ON(void);
void FAULT_P1_P2_RELAIE_OFF(void);

//Interrupt
void init_NVIC_PORTE(void);
void GPIO_PORTE_INTERRUPT(void);

#endif
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
#define SENS_ANA_MQ7           (1<<4) //ANALOG ??? möglich an dem PIN?
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




#endif
#ifndef __functions
#define __functions



//DEBUG
void DEBUG_delay(int);
void DEBUG_OUTPUT_TEST(void);

//SCHWIMMERSCHALTER DIGITAL
int* DIGI_SENSE(void);


//MODES
int NORMAL_MODE(int* DIGI_sensors, int active);
void FAIL_CHECK(int* DIGI_sensor,int active);

#endif
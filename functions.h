#ifndef __functions
#define __functions



//DEBUG
void DEBUG_delay(int);
void DEBUG_OUTPUT_TEST(void);



int DIGITAL_IN_STATUS_PORTE(int);


//FEHLERFÄLLE
void not_plausible(void);
void low_on_water_dryrun(void);
void no_sensor_data(const char*);
void highwater_alarm(void);
void quit_failure(void);
#endif
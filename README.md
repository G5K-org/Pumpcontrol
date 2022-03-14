# Pumpcontrol
TM4C123GH6PM pump control written in C with IAR ARM

TEIV Project
Project idea 1.)
Construction of a small pump control with 4 float switch inputs
The float switch inputs are galvanically isolated from the power supply of the µC by optocouplers. The float switches represent the water level a LED gives feedback if the water level is reached.
Sensor inputs:
Float switch arrangement:

4 high water
3 water level pump-2 active
2 Water level pump-1 active
1 dry run protection

Methane measurement to avoid explosions. MQ7 Sensor EX range

Outputs:
BC847 NPN transistor switches print Relaie 
Pump 1 Pump 2
Digital inputs (float switch)
PE0 Dry run protection float switch
PE1 Water level P1
PE2 Water level P2
PE3 High water
PE4 MQ7 Analog input

Activate interrupt routine for PE0-4

Outputs:
PB0 Relay pump 1 start
PB1 Relay pump 2 start
PB2 Collective fault
PB3 Fault P1
PB4 Fault P2

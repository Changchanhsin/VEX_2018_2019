#include "virtualvex.h"
//  mapping ROBOTC
#define ballCollector_1 0
#define riser           1
#define flipper         2
#define r_1             4
#define l_1             5
#define l_2             6
#define r_2             7
#define charger_1       8
#define charger_2       9
#define ballCollector_2 10
#define deg             1
#define touch           2
void __carLeft(int spd)  // for debug
{
  motor[l_1]=spd;
  motor[l_2]=spd;
}
void __carRight(int spd)  // for debug
{
  motor[r_1]=spd;
  motor[r_2]=spd;
}
void __mapping_port__()  // for debug
{
  __car_left_move__ = (float)(motor[l_1]+motor[l_2])/700.0;
  __car_right_move__ = (float)(motor[r_1]+motor[r_2])/700.0;
}
// virtualvex config to fit pragma

/*************************************************************************************************
#pragma config(Sensor, in1,    deg,            sensorAccelerometer)
#pragma config(Sensor, dgtl1,  touch,          sensorTouch)
#pragma config(Motor,  port1,           ballCollector_1, tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           riser,         tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           flipper,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           r_1,           tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           l_1,           tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           l_2,           tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           r_2,           tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           charger_1,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           charger_2,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          ballCollector_2, tmotorVex393_HBridge, openLoop, reversed)
#pragma platform(VEX2)
#pragma competitionControl(Competition)
#include "Vex_Competition_Includes.c"
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!//
 *************************************************************************************************/

void step_auto()
{
	;
}
  
void step()
{
	;
}

void init()
{
  ;
}

void pre_auton()
{
  bStopTasksBetweenModes = true;
  init();
}

int autonomous()
{
  //while (1)     // ignore and replace to 'if' for M5Stack
    step_auto();
}
  
int usercontrol()
{
  //while (1)     // ignore for M5Stack
    step();
}

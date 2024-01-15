#ifndef ROBOTCONFIG_H
#define ROBOTCONFIG_H
#include"vex.h"
using namespace vex;

void vexcodeInit(void);

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
extern brain Brain;
extern controller con;
extern motor left1;
extern motor left2;
extern motor left3;
extern motor right1;
extern motor right2;
extern motor right3;
extern motor intake;
extern motor kicker;
extern pneumatics leftwing;
extern pneumatics rightwing;
extern pneumatics dropDown;
extern pneumatics lift;

extern motor_group leftdrive;
extern motor_group rightdrive;
extern inertial Inertial;
extern motor_group allmotors;
extern drivetrainObj Drive;

#endif
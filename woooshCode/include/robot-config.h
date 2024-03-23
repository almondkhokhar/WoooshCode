#ifndef ROBOTCONFIG_H
#define ROBOTCONFIG_H
#include "vex.h"
using namespace vex;

void vexcodeInit(void);

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
extern vex::brain Brain;
extern vex::controller con;
extern vex::motor left1;
extern vex::motor left2;
extern vex::motor left3;
extern vex::motor right1;
extern vex::motor right2;
extern vex::motor right3;
extern vex::motor intake;
extern vex::motor kicker;
extern vex::motor kicker2;
extern vex::pneumatics leftwing;
extern vex::pneumatics rightwing;
extern vex::pneumatics rDropDown;
extern vex::pneumatics lDropDown;
extern vex::pneumatics hang;
extern vex::pot potSelector;

extern vex::motor_group leftdrive;
extern vex::motor_group rightdrive;
extern vex::inertial Inertial;
extern vex::motor_group allmotors;
extern drivetrainObj Drive;

#endif
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
//declares left drive motors
extern vex::motor right1;
extern vex::motor right2;
extern vex::motor right3;
//declares right drive motors
extern vex::motor intake;
// declares intake motor
extern vex::motor lift;
//declares lift motor

extern vex::pneumatics leftwing;
extern vex::pneumatics rightwing;
extern vex::pneumatics rDropDown;
extern vex::pneumatics lDropDown;
extern vex::pneumatics hang;
extern vex::pot potSelector;

extern vex::motor_group leftdrive;
extern vex::motor_group rightdrive;
//declares drivetrain motor groups
extern vex::inertial Inertial;
extern vex::inertial Inert2;
//declares inertial sensors, we have 2 so if one disconnects or has an error we can override it's input and use the second inertial sensor instead
extern vex::motor_group allmotors;
//declares a motor group to allow us to stop everything at once 
extern drivetrainObj Drive;
//declares the drivetrain as an object
#endif
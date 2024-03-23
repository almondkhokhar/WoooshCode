#include "vex.h"
using namespace vex;

// A global instance of brain used for printing to the V5 brain screen
brain Brain;
controller con;
motor right1 = motor(PORT10,false);
motor right2 = motor(PORT8,false);
motor right3 = motor(PORT9,false);
motor left1 = motor(PORT18,true);
motor left2 = motor(PORT19, true);
motor left3 = motor(PORT20, true);
motor kicker = motor(PORT7, true);
motor intake = motor(PORT17, false);
pneumatics rightwing = pneumatics(Brain.ThreeWirePort.A);
pneumatics leftwing = pneumatics(Brain.ThreeWirePort.D);
pneumatics dropDown = pneumatics(Brain.ThreeWirePort.B);
pneumatics lift = pneumatics(Brain.ThreeWirePort.E);
pot potSelector = pot(Brain.ThreeWirePort.F);

motor_group leftdrive(left1, left2, left3);
motor_group rightdrive(right1, right2, right3);
inertial Inertial = inertial(PORT5);
motor_group allmotors(left1, left2, left3, right1, right2, right3, intake, kicker);
drivetrainObj Drive(3.25, 0.75);
/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  // Nothing to initialize
}
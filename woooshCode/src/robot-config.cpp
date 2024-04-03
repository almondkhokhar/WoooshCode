#include "vex.h"
using namespace vex;


// A global instance of brain used for printing to the V5 brain screen
brain Brain;
controller con;
motor right1 = motor(PORT10, ratio6_1, true);
motor right2 = motor(PORT18, ratio6_1, true);
motor right3 = motor(PORT8, ratio6_1, true);
motor left1 = motor(PORT13, ratio6_1, false);
motor left2 = motor(PORT11,  ratio6_1, false);
motor left3 = motor(PORT1,  ratio6_1, false);
motor kicker = motor(PORT12, true);
motor kicker2 = motor(PORT20, false);
motor intake = motor(PORT19, false);
pneumatics rightwing = pneumatics(Brain.ThreeWirePort.A);
pneumatics leftwing = pneumatics(Brain.ThreeWirePort.B);
pneumatics rDropDown = pneumatics(Brain.ThreeWirePort.C);
pneumatics hang = pneumatics(Brain.ThreeWirePort.D);
pot potSelector = pot(Brain.ThreeWirePort.E);


motor_group leftdrive(left1, left2, left3);
motor_group rightdrive(right1, right2, right3);
inertial Inertial = inertial(PORT14);
motor_group allmotors(left1, left2, left3, right1, right2, right3, intake, kicker, kicker2);
drivetrainObj Drive(2.75, 1);
/**
* Used to initialize code/tasks/devices added using tools in VEXcode Pro.
*
* This should be called at the start of your int main function.
*/
void vexcodeInit(void) {
 // Nothing to initialize
}
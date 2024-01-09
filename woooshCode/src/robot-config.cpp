#include "vex.h"

using namespace vex;

// A global instance of brain used for printing to the V5 brain screen
brain Brain;
controller con;
motor right1 = motor(PORT10,true);
motor right2 = motor(PORT8,true);
motor right3 = motor(PORT6,true);
motor left1 = motor(PORT2,true);
motor left2 = motor(PORT1, true);
motor left3 = motor(PORT4, true);
motor cata1 = motor(PORT11, true);
motor cata2 = motor(PORT20,false);
motor intake = motor(PORT7, false);
pneumatics rightwing = pneumatics(Brain.ThreeWirePort.G);
pneumatics leftwing = pneumatics(Brain.ThreeWirePort.H);
inertial Inertial = inertial(PORT19);
rotation Catarotate = rotation(PORT12);
/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  // Nothing to initialize
}
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
motor Punchything = motor(PORT7, true);
motor intake = motor(PORT17, false);
pneumatics rightwing = pneumatics(Brain.ThreeWirePort.A);
pneumatics leftwing = pneumatics(Brain.ThreeWirePort.H);
pneumatics uppy1 = pneumatics(Brain.ThreeWirePort.B);
pneumatics uppy2 = pneumatics(Brain.ThreeWirePort.C);
pneumatics uppy3 = pneumatics(Brain.ThreeWirePort.G);
pneumatics uppy4 = pneumatics(Brain.ThreeWirePort.F);
inertial Inertial = inertial(PORT6);
/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  // Nothing to initialize
}
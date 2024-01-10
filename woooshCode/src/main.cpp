/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       mainy.cpp                                                  */
/*    Author:       2025arjomandkhokhar                                       */
/*    Created:      Mon Oct 16 2023                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
// initializes variables
bool conToggle1 = true;
bool conToggle2 = true;
bool conToggle3 = true;
bool conToggle4 = true;
bool intakeToggle = false;
bool rwingtoggle = false;
bool lwingtoggle = false;
bool bwingtoggle = false;
bool f1 = true;
bool f2 = true;
bool f3 = true;
bool f1loop = true;
bool f2loop = true;
bool f3loop = true;
int counter = 0;
double cataLoadedPos = 112;
using namespace vex;
// defines motor groups and abstracts the motors into simpler components
competition Competition;
motor_group leftdrive(left1, left2, left3);
motor_group rightdrive(right1, right2, right3);
motor_group allmotors(left1, left2, left3, right1, right2, right3, intake, Punchything);

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Inertial.calibrate();
  wait(5, sec);
  Brain.Screen.print("Ready");
}

void gyroTurn (float target, float timeout) {
  // establishes when the turn started 
  int startTime = vex::timer::system();
  // limits the time so that it doesn't waste time fixing marginal error
  while (vex::timer::system() - startTime < timeout * 1000) {
    //limits the speed so as the robot gets closer to where you want it it slows down the speed and doesn't overshoot the distance
    float speed = (target - Inertial.rotation(deg)) * .2;
    rightdrive.spin(fwd, -speed, pct);
    leftdrive.spin(fwd, speed, pct);
    if ((target - Inertial.rotation(deg)) < 1){
      break;
    }
  }
  //stops slowly opposed to abruptly
  leftdrive.stop(brake);
  rightdrive.stop(brake);
}

void lineDrive (float dist, float timelim){
  //establishes when we started the procedure
  //records a starting position of the bot
  double startPos = right1.position(deg);
  //records a starting position of the bot
  double startAng = Inertial.rotation(deg);
  int startTime = vex::timer::system();
  //limits the time the procedure can run
  while (vex::timer::system() - startTime < timelim * 1000) {
    //limits the speed so as the robot gets closer to where you want it it slows down the speed and doesn't overshoot the distance
    double speed = (dist - (right1.position(deg)-startPos)*3.14159/180*3.25) * 2.4;
    // explain here
    double turnErr = startAng - Inertial.rotation(deg);
    rightdrive.spin(fwd, speed-turnErr, pct);
    leftdrive.spin(fwd, speed+turnErr, pct);
    wait(5, msec);
 }
}

void lineDriveAbsolute (double dist, double timelim, double targetAngle){
  //establishes when we started the procedure
  //records a starting position of the bot
  //records a starting position of the bot
  double startAng = Inertial.rotation(deg);
  int startTime = vex::timer::system();
  //limits the time the procedure can run
  while (vex::timer::system() - startTime < timelim * 1000) {
    //limits the speed so as the robot gets closer to where you want it it slows down the speed and doesn't overshoot the distance
    double speed = (dist - (right1.position(deg)-targetAngle)*3.14159/180*3.25) * 7;
    // explain here
    double turnErr = startAng - Inertial.rotation(deg);
    rightdrive.spin(fwd, speed-turnErr, pct);
    leftdrive.spin(fwd, speed+turnErr, pct);
    wait(5, msec);
 }
}


void defense () {
  //opens wing to remove ball in the corner
  //rightwing.open();
  //drives towards the wall to remove the tri ball
  lineDrive(-20,1.5);
  // closes the wings to prevent damages to the wings
  // turns to face the goal
  gyroTurn(30,2);
  //rightwing.close();
  //drives match load into the goal
  lineDrive(-20,1);
  lineDrive(10,1);
  gyroTurn(0, 2);
  lineDrive(40,1);
  gyroTurn(-50,1);
  lineDrive(50,1.5);
  allmotors.stop();
  // // turns to touch the elevation pole
  // gyroTurn(-15,2);
  // //drives to the pole
  // lineDrive(10,2);
  // // turns to the pole 
  // gyroTurn(-45,2);
  // // touches the pole
  // lineDrive(30,2);
  // // stops everything
  // allmotors.stop();
}
void fourball(){
  rightwing.open();
  intake.spin(fwd,-15,pct);
  wait(.4,sec);
  rightwing.close();
  lineDrive(10,1);
  gyroTurn(-30,1);
  intake.spin(fwd,-100,pct);
  lineDrive(100,.6);
  lineDrive(-15,1);
  gyroTurn(-135,.7);
  intake.spin(fwd,100,pct);
  lineDrive(62,1.3);
  gyroTurn(160-185,1.2);
  lineDrive(32,1.5);
  gyroTurn(250+175,.7);
  intake.spin(fwd,-100,pct);
  wait(.45,sec);
  lineDrive(1000,.6);
  intake.spin(fwd,100,pct);
  lineDrive(-20,1);
  gyroTurn(70+165,.6);
  lineDrive(25,1);
  gyroTurn(250+165,1.2);
  intake.spin(fwd,-100,pct);
  lineDrive(1000,.75);
  lineDrive(-10,1);
  allmotors.stop();

}
void qualsoffense () {
  // opens the wing to remove the tri ball
  //drives to remove the tri ball
  lineDrive(-35,3);
  gyroTurn(-30,1);
  lineDrive(-15,.5);
  lineDrive(10,.75);
  gyroTurn(0,1.5);
  lineDrive(35,2);
  gyroTurn(63,2);
  lineDrive(50,2);
  allmotors.stop();
  //closes the wing to prevent damaging the robot
  //turns to face the goal
  // gyroTurn(40,2);
  // //scores the matchload triball
  // lineDrive(40,2);
  // //turns to face the elevation pole
  // gyroTurn(10,2);
  // //drives closer to the elevation pole
  // lineDrive(30,2);
  // //turns to be in line with the pole
  // gyroTurn(45,1);
  // intake.spin(fwd,-15,pct);
  // //touches the pole
  // lineDrive(30,2);
  // //stops all motors
  // allmotors.stop();
}
void elimoffense(){
  lineDrive(-100,.8);
  gyroTurn(-30,.4);
  lineDrive(20,.75);
  gyroTurn(80,1);
  lineDrive(50,2);
  intake.spin(fwd,-15,pct);
  gyroTurn(160,1);
  intake.spin(fwd,100,pct);
  lineDrive(32,1.5);
  gyroTurn(250,1);
  intake.spin(fwd,-100,pct);
  wait(.4,sec);
  lineDrive(30,1);
  intake.spin(fwd,100,pct);
  lineDrive(-30,1.5);
  gyroTurn(60,1);
  lineDrive(15,.5);
  gyroTurn(250,1);
  intake.spin(fwd,-100,pct);
  lineDrive(1000,1);
  lineDrive(-10,1);
  allmotors.stop();
}
void finalsdefense(){
  //opens wing to remove ball in the corner
  rightwing.open();
  //drives towards the wall to remove the tri ball
  lineDrive(-20,1.5);
  // closes the wings to prevent damages to the wings
  // turns to face the goal
  gyroTurn(30,2);
  rightwing.close();
  //drives match load into the goal
  lineDrive(-20,1);
  lineDrive(10,1);
  gyroTurn(-45,1);
  lineDrive(60,2);
}

void autonomous () {
  defense();
}

void usercontrol () {
  while (true)
  { 
    //driving portion
    //controls the speed at which the robot moves
    right1.spin(fwd, con.Axis2.value(), pct);
    right2.spin(fwd, con.Axis2.value(), pct);
    right3.spin(fwd, con.Axis2.value(), pct);
    left1.spin(fwd, con.Axis3.value(), pct);
    left2.spin(fwd, con.Axis3.value(), pct);
    left3.spin(fwd, con.Axis3.value(), pct);
    //turns the intake on or off
    if(con.ButtonL2.pressing()){
      if (conToggle1) {
        conToggle1 = false;
        intakeToggle = !intakeToggle;
      }
    } else {
      conToggle1 = true;
    }
    //manual override to spin intake forward
    if (con.ButtonY.pressing()) {
      intake.spin(fwd, 100, pct);
      //manual override to reverse intake
    } else if (con.ButtonL1.pressing()) {
      intake.spin(reverse, 100, pct);
      //if no buttons are being pressed the toggle runs
    } else if (intakeToggle) {
      intake.spin(fwd,100,pct);
    } else {
      intake.stop();
    }

    //toggles the right wing on and off
    if (con.ButtonA.pressing()) {
      if (f1loop) {
        rwingtoggle = !rwingtoggle;
      }
      if (rwingtoggle && f1loop){
        rightwing.open();
        f1loop=false;
      }
      if (!rwingtoggle && f1loop){
        rightwing.close();
        f1loop=false;
      }
    }
    else{
      f1loop=true;
    }
      
    //toggles the left wing on and off
    if (con.ButtonLeft.pressing()) {
      if (f2loop) {
        lwingtoggle = !lwingtoggle;
      }
      if (lwingtoggle && f2loop){
        leftwing.open();
        f2loop=false;
      }
      if (!lwingtoggle && f2loop){
        leftwing.close();
        f2loop=false;
      }
    }
    else{
      f2loop=true;
    }
    //toggles both wings on or off
    if (con.ButtonR2.pressing()){
      if (f3loop) {
        bwingtoggle = !bwingtoggle;
      }
      if (bwingtoggle && f3loop){
        leftwing.open();
        rightwing.open();
        f3loop=false;
      }
      if (!bwingtoggle && f3loop){
        leftwing.close();
        rightwing.close();
        f3loop=false;
      }
    }
    else{
      f3loop=true;
    }
        


    if (con.ButtonB.pressing()){
      Punchything.spin(fwd,100,pct);
    }
    else {
      Punchything.stop();
    }
}
}


int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  pre_auton();
  while (true) {
    wait(100, msec);
  }
}

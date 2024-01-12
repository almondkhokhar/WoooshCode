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
bool Shoottogg = false;
bool f1loop = true;
bool f2loop = true;
bool f3loop = true;
bool f4loop = true;
int counter = 0;
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
  }
  //stops slowly opposed to abruptly
  leftdrive.stop();
  rightdrive.stop();

}


void lineDrive (float dist, float timelim){
  //establishes when we started the procedure
  //records a starting position of the bot
  double  startPos = right1.position(deg);

  //records a starting position of the bot
  double startAng = Inertial.rotation(deg);
  int startTime = vex::timer::system();
  //limits the time the procedure can run
  while (vex::timer::system() - startTime < timelim * 1000) {
    //limits the speed so as the robot gets closer to where you want it it slows down the speed and doesn't overshoot the distance
    double  speed = (dist - (right1.position(deg)-startPos)*3.14159/180*3.25) * 3.9;
    // explain here
    double turnErr = startAng - Inertial.rotation(deg);
    rightdrive.spin(fwd, speed-turnErr, pct);
    leftdrive.spin(fwd, speed+turnErr, pct);
    wait(5, msec);
  
  leftdrive.stop();
  rightdrive.stop();
}
} 

void backup(){
  lineDrive(-100,2);
  lineDrive(10,1);
}

/**
 * @brief does a straight line or a swing
 * 
 * @param turnSharpness how sharp it turns (-200, 200) + => right, - => left, 0 for straight
 * @param dist 
 * @param timelim 
 */
void swing (float turnSharpness,float dist, float timelim){
  //establishes when we started the procedure
  //records a starting position of the bot
  double startPos = left1.position(deg);
  if (turnSharpness < 0)
  {
    startPos = right1.position(deg);
  }

  //records a starting position of the bot
  double startAng = Inertial.rotation(deg);
  int startTime = vex::timer::system();
  //limits the time the procedure can run
  while (vex::timer::system() - startTime < timelim * 1000) {
    //limits the speed so as the robot gets closer to where you want it it slows down the speed and doesn't overshoot the distance
    double speed = (dist - (left1.position(deg)-startPos)*3.14159/180*3.25) * 3.9;
    if (turnSharpness < 0)
    {
      speed = (dist - (right1.position(deg)-startPos)*3.14159/180*3.25) * 3;
    }
    // explain here
    double turnErr = startAng - Inertial.rotation(deg);
    if (turnSharpness == 0){
      rightdrive.spin(fwd, speed-turnErr, pct);
      leftdrive.spin(fwd, speed+turnErr, pct);
    }
    if (100>turnSharpness > 0){
      rightdrive.spin(fwd, speed * ((100 - turnSharpness) / 100), pct);
      leftdrive.spin(fwd, speed, pct);
    }
    if (turnSharpness >100){
      rightdrive.spin(fwd, speed * ((100 - turnSharpness) / 100), pct);
      leftdrive.spin(fwd, -speed, pct);
    }
    if (-100 < turnSharpness < 0){
      rightdrive.spin(fwd, speed, pct);
      leftdrive.spin(fwd, speed * ((100 + turnSharpness) / 100), pct);
    }
    if (turnSharpness< -100){
      rightdrive.spin(fwd, -speed, pct);
      leftdrive.spin(fwd, speed * ((100 + turnSharpness) / 100), pct);
    }
    wait(5, msec);
  }
  allmotors.stop();
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

void wooshDefense(){
  Punchything.spin(fwd,100,pct);
  leftwing.open();
  intake.spin(fwd,100,pct);
  lineDrive(50, 2);
  leftwing.close();
  Punchything.stop(coast);
  lineDrive(-15,1);
  gyroTurn(45,1);
  intake.spin(fwd,-100,pct);
  lineDrive(30,1);
  swing(155, 15, 2);
  gyroTurn(80,1);
  swing(-130,40,2);
  lineDrive(10,1.5);
  gyroTurn(-60,1);
  rightwing.open();
  lineDrive(50,2);
}

void autonomous () {
  wooshDefense();
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
    if (con.ButtonX.pressing()){
      if (f4loop){
        Shoottogg = !Shoottogg;
      }
      if (Shoottogg && f4loop){
        uppy1.open();
        // uppy2.open();
        // uppy3.open();
        // uppy4.open();
        f4loop=false;
      }
      if (!Shoottogg && f4loop){
        uppy1.close();
        // uppy2.close();
        // uppy3.close();
        // uppy4.close();
        // f4loop=false;
        f4loop=false;
      }
    }
    else {
      f4loop = true;
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
        


    if (con.ButtonR1.pressing()){
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

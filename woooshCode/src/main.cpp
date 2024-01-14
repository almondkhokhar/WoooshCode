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
bool punchythingToggle = false;
bool dropdowntoggle=false;
bool hangToggle = false;
bool f1loop = true;
bool f2loop = true;
bool f3loop = true;
bool f4loop = true;
bool f5loop = true;
bool f6loop = true;
bool f7loop = true;
int counter = 0;

using namespace vex;
// defines motor groups and abstracts the motors into simpler components
competition Competition;
motor_group leftdrive(left1, left2, left3);
motor_group rightdrive(right1, right2, right3);
motor_group allmotors(left1, left2, left3, right1, right2, right3, intake, Punchything);

void gyroTurn(double target, double timeout, bool rightTurn)
{
  // establishes when the turn started
  int startTime = vex::timer::system();
  // limits the time so that it doesn't waste time fixing marginal error
  double speed;
  while (vex::timer::system() - startTime < timeout * 1000)
  {
    // limits the speed so as the robot gets closer to where you want it it slows down the speed and doesn't overshoot the distance
    speed = (target - Inertial.rotation(deg)) * .4;
    if (rightTurn)
    {
      rightdrive.spin(fwd, -speed, pct);
      leftdrive.spin(fwd, speed, pct);
    }
    else
    {
      rightdrive.spin(fwd, speed, pct);
      leftdrive.spin(fwd, -speed, pct);
    }
    wait(10, msec);
  }
  // stops slowly opposed to abruptly
  leftdrive.stop();
  rightdrive.stop();
}

void lineDrive(double targetDistance, double timeout)
{
  double distKp = 3.9;
  // establishes when we started the procedure
  // records a starting position of the bot
  double startPos = right1.position(deg);
  // records a starting position of the bot
  double startAng = Inertial.rotation(deg);
  int startTime = vex::timer::system();
  // limits the time the procedure can run
  double speed, turnErr;
  while (vex::timer::system() - startTime < timeout * 1000)
  {
    // limits the speed so as the robot gets closer to where you want it it slows down the speed and doesn't overshoot the distance
    speed = (targetDistance - (right1.position(deg) - startPos) * 3.14159 / 180 * 3.25) * distKp;
    // calculates the difference between our current angle and our initial angle
    turnErr = startAng - Inertial.rotation(deg);
    // set the drive to the correct speed
    rightdrive.spin(fwd, speed - turnErr, pct);
    leftdrive.spin(fwd, speed + turnErr, pct);
    wait(10, msec);
  }
  leftdrive.stop();
  rightdrive.stop();
}

void backup()
{
  lineDrive(-100, 2);
  lineDrive(10, 1);
}

void swing(double targetAngle, double targetDistance, double timeout, bool rightTurn)
{
  // variables
  double turnKp = 1;
  double distKp = 3.9;
  double speed, fractionOfDriveCompleted, distanceTraveled, currentTargetAngle, turnErr;
  double leftStartPos = left1.position(deg);
  double rightStartPos = right1.position(deg);
  double startAngle = Inertial.rotation(deg);
  int startTime = vex::timer::system();
  while (vex::timer::system() - startTime < timeout * 1000)
  {
    if (rightTurn)
    {
      distanceTraveled = ((left1.position(deg) - leftStartPos) * 3.14159 / 180 * 3.25);
    }
    else
    {
      distanceTraveled = ((right1.position(deg) - rightStartPos) * 3.14159 / 180 * 3.25);
    }
    // find the desired speed based on distance
    speed = (targetDistance - distanceTraveled) * distKp;
    // find percentage of distance driven
    fractionOfDriveCompleted = distanceTraveled / targetDistance;
    // calculate the angle the robot should be at based on percent driven
    currentTargetAngle = startAngle + fractionOfDriveCompleted * targetAngle;
    // find the error of the robots angle
    turnErr = (currentTargetAngle - Inertial.rotation(deg)) * turnKp;

    rightdrive.spin(fwd, speed - turnErr, pct);
    leftdrive.spin(fwd, speed + turnErr, pct);
    wait(20, msec);
  }
  leftdrive.stop();
  rightdrive.stop();
}

void wooshDefense()
{
  intake.spin(fwd, -100, pct);
  lineDrive(-40, 1);
  lineDrive(10, 1);
  gyroTurn(10, 1, false);
  dropDown.open();
  lineDrive(24, 1);
  gyroTurn(18, 1, false);
  dropDown.close();
  lineDrive(45, 1);
}
void agroDefense()
{
  Punchything.spin(fwd, 100, pct);
  intake.spin(fwd, 100, pct);
  leftwing.open();
  lineDrive(52.5, 1.7);
  Punchything.stop();
  lineDrive(-16, .75);
  gyroTurn(20, 1, true);
  intake.spin(fwd, -100, pct);
  lineDrive(40, 1);
  leftwing.close();
  lineDrive(-15, .75);
  gyroTurn(40, 1, true);
  lineDrive(54, 1.7);
  gyroTurn(20, 1, false);
  lineDrive(-55, 1);
  lineDrive(17, 1);
  gyroTurn(10, 1, false);
  dropDown.open();
  lineDrive(25, 1);
  intake.spin(fwd,-100,pct);
  gyroTurn(22.5, 1, false);
   dropDown.close();
   lineDrive(40,1.1);
}
void skills(){
  uppy3.open();
  Punchything.spin(fwd,100,pct);
  intake.spin(fwd,-100,pct);
  wait(45,sec);
  uppy3.close();
  wait(2,sec);
  Punchything.stop();
  gyroTurn(17,1,true);
  lineDrive(90,3);
  gyroTurn(19,1,false);
  rightwing.open();
  leftwing.open();
  lineDrive(70,3);
  lineDrive(-15,1.5);
}

void agroOffense(){
  dropDown.open();
  lineDrive(13,1);
  gyroTurn(15,1,false);
  dropDown.close();
  intake.spin(fwd,-100,pct);
  lineDrive(60,.75);
  lineDrive(-13,.5);
  gyroTurn(23.5,1,false);
  intake.spin(fwd,100,pct);
  lineDrive(58,1.5);
  gyroTurn(31,1,true);
  lineDrive(17,.8);
  gyroTurn(24,1,true);
  leftwing.open();
  intake.spin(fwd,-100,pct);
  lineDrive(50,1);
  leftwing.close();
  lineDrive(-20,.8);
  intake.spin(fwd,100,pct);
  gyroTurn(50,1,false);
  lineDrive(17,.8);
  lineDrive(-30,1);
  gyroTurn(50,1,true);
  intake.spin(fwd,-100,pct);
  lineDrive(30,1);





}
void pre_auton(void)
{
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Inertial.calibrate();
  wait(3, sec);
  Brain.Screen.print("Ready");
}

void autonomous()
{
  agroOffense();
}


void usercontrol()
{
  while (true)
  {
    // driving portion
    // controls the speed at which the robot moves
    rightdrive.spin(fwd, con.Axis2.value(), pct);
    leftdrive.spin(fwd, con.Axis3.value(), pct);
    // turns the intake on or off
    if (con.ButtonL2.pressing())
    {
      if (conToggle1)
      {
        conToggle1 = false;
        intakeToggle = !intakeToggle;
      }
    }
    else
    {
      conToggle1 = true;
    }

    // manual override to spin intake forward
    if (con.ButtonY.pressing())
    {
      intake.spin(fwd, 100, pct);
      // manual override to reverse intake
    }
    else if (con.ButtonL1.pressing())
    {
      intake.spin(reverse, 100, pct);
      // if no buttons are being pressed the toggle runs
    }
    else if (intakeToggle)
    {
      intake.spin(fwd, 100, pct);
    }
    else
    {
      intake.stop();
    }

    // toggles the right wing on and off
    if (con.ButtonA.pressing())
    {
      if (f1loop)
      {
        rwingtoggle = !rwingtoggle;
      }
      if (rwingtoggle && f1loop)
      {
        rightwing.open();
        f1loop = false;
      }
      if (!rwingtoggle && f1loop)
      {
        rightwing.close();
        f1loop = false;
      }
    }
    else
    {
      f1loop = true;
    }

    // toggles the left wing on and off
    if (con.ButtonLeft.pressing())
    {
      if (f2loop)
      {
        lwingtoggle = !lwingtoggle;
      }
      if (lwingtoggle && f2loop)
      {
        leftwing.open();
        f2loop = false;
      }
      if (!lwingtoggle && f2loop)
      {
        leftwing.close();
        f2loop = false;
      }
    }
    else
    {
      f2loop = true;
    }
    if (con.ButtonX.pressing())
    {
      if (f4loop)
      {
        Shoottogg = !Shoottogg;
      }
      if (Shoottogg && f4loop)
      {
        uppy3.open();
        // uppy2.open();
        // uppy3.open();
        // uppy4.open();
        f4loop = false;
      }
      if (!Shoottogg && f4loop)
      {
        uppy3.close();
        // uppy2.close();
        // uppy3.close();
        // uppy4.close();
        // f4loop=false;
        f4loop = false;
      }
    }
    else
    {
      f4loop = true;
    }
    // toggles both wings on or off
    if (con.ButtonR2.pressing())
    {
      if (f3loop)
      {
        bwingtoggle = !bwingtoggle;
      }
      if (bwingtoggle && f3loop)
      {
        leftwing.open();
        rightwing.open();
        f3loop = false;
      }
      if (!bwingtoggle && f3loop)
      {
        leftwing.close();
        rightwing.close();
        f3loop = false;
      }
    }
    else
    {
      f3loop = true;
    }

    if (con.ButtonR1.pressing())
    {
      if (f5loop){
        punchythingToggle=!punchythingToggle;
      }
      if (punchythingToggle && f5loop){
        Punchything.spin(fwd,100,pct);
        f5loop=false;
      }
      if (!punchythingToggle && f5loop){
        Punchything.stop();
        f5loop=false;
      }

    }
    else {
      f5loop = true;
    }
    if (con.ButtonUp.pressing()){
      if (f6loop){
        dropdowntoggle=!dropdowntoggle;
      }
      if (dropdowntoggle && f6loop){
        dropDown.open();
        f6loop = false;
      }
      if (!dropdowntoggle && f6loop){
        dropDown.close();
        f6loop =false;
      }
    }
    else{
      f6loop = true;
    }
  }
}

int main()
{
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  pre_auton();
  while (true)
  {
    wait(100, msec);
  }
}

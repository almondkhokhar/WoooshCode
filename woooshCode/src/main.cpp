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
class Drive{
  public:
    double wheelRatio;
    double gearRatio;
    double kp;
    double kd;
    double initialAngle;
    double finalAngle;
    double totalError;
    double currentError;
    double finalDistance;
    double currentDistance;
    double turningDistance;
    double turnTimeout;
    double totalTimeout;
    double firstDriveTimeout;
    double secondDriveTimeout;

};
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
int autoSelect = 0;


void pre_auton(void)
{
  Inertial.calibrate();
  wait(3, sec);
  Brain.Screen.print("Ready");
  bool firstTouch = true;
  while (!Competition.isDriverControl())
  {
    if (Brain.Screen.pressing())
    {
      if (firstTouch)
      {
        firstTouch = false;
        autoSelect = (autoSelect + 1) % 8;
      }
    }
    else
    {
      firstTouch = true;
    }
  }
}

void backup()
{
  Drive.move(-100, 2);
  Drive.move(10, 1);
}

void wooshDefense()
{
  intake.spin(fwd, -100, pct);
  Drive.move(-40, 1);
  Drive.move(10, 1);
  Drive.turn(10, 1);
  dropDown.open();
  Drive.move(24, 1);
  Drive.turn(18, 1);
  dropDown.close();
  Drive.move(45, 1);
}

void agroDefense()
{
  kicker.spin(fwd,100,pct);
  dropDown.open();
  Drive.move(5,.3);
  dropDown.close();
  Drive.turn(-49,1.2);
  kicker.stop();
  intake.spin(fwd,100,pct);
  Drive.move(56,2);
  Drive.turn(-9,1);
  Drive.move(-50,1.5);
  Drive.turn(70,1);
  intake.spin(fwd,-100,pct);
  wait(.3,sec);
  Drive.move(-23,1);
  Drive.turn(40,1);
  dropDown.open();
  Drive.turn(50,1);
  wait(.2,sec);
  dropDown.close();
  Drive.turn(-60,1);
  rightwing.open();
  Drive.move(25,1);
  Drive.turn(-40,1);
  Drive.move(39,1.4);
  rightwing.close();
  // kicker.spin(fwd, 100, pct);
  // intake.spin(fwd, 100, pct);
  // leftwing.open();
  // Drive.move(53, 1.75);
  // wait(.3,sec);
  // kicker.stop();
  // leftwing.close();
  // Drive.move(-55, 1.75);
  // Drive.turn(60, 1);
  // intake.spin(fwd,-100,pct);
  // wait(.5,sec);
  // Drive.turn(15,1);
  // Drive.move(-29,1.45);
  // Drive.turn(37,1);
  // Drive.move(-12.5,1);
  // Drive.move(18,1);
  // Drive.turn(-27 ,1);
  // dropDown.open();
  // Drive.move(18,1);
  // Drive.turn(-33,1);
  // dropDown.close();
  // rightwing.open();
  // Drive.move(39,1.2);
  // rightwing.close();
  
}

void skills(){
  lift.open();
  kicker.spin(fwd,100,pct);
  intake.spin(fwd,-100,pct);
  wait(45,sec);
  lift.close();
  wait(2,sec);
  kicker.stop();
  Drive.turn(17,1);
  Drive.move(90,3);
  Drive.turn(19,1);
  rightwing.open();
  leftwing.open();
  Drive.move(70,3);
  Drive.move(-15,1.5);
}

void sixball() {
  intake.spin(fwd,100,pct);
  lift.open();
  wait(.2,sec);
  lift.close();
  dropDown.open();
  wait(.3,sec);
  Drive.move(-36.5,1.3);
  dropDown.close();
  Drive.turn(170,1);
  leftwing.open();
  Drive.move(8,.3);
  rightwing.open();
  Drive.move(15,1);
  intake.spin(fwd,-100,pct);
  Drive.turn(97,1);
  Drive.move(1000,.6);
  Drive.move(-6,.5);
  Drive.move(1000,.6);
  rightwing.close();
  leftwing.close();
  Drive.move(-10,.5);
  Drive.turn(15,1);
  intake.spin(fwd,100,pct);
  Drive.move(55,1.3);
  Drive.turn(130,1);
  intake.spin(fwd,-80,pct);
  Drive.turn(90,1);
  intake.spin(fwd,100,pct);
  Drive.move(30,1.5);
  Drive.turn(180,1);
  rightwing.open();
  leftwing.open();
  intake.spin(fwd,-100,pct);
  Drive.move(100,1);
  Drive.move(-100,1);

  // intake.spin(fwd,-100,pct);
  // dropDown.close();
  // Drive.turn(-30,1);

}

void agroOffense(){
  dropDown.open();
  Drive.move(13,1);
  Drive.turn(-15,1);
  dropDown.close();
  intake.spin(fwd,-100,pct);
  Drive.move(60,.75);
  Drive.move(-13,.5);
  Drive.turn(-73.5,1);
  intake.spin(fwd,100,pct);
  Drive.move(58,1.5);
  Drive.turn(31,1);
  Drive.move(17,.8);
  Drive.turn(24,1);
  leftwing.open();
  intake.spin(fwd,-100,pct);
  Drive.move(50,1);
  leftwing.close();
  Drive.move(-20,.8);
  intake.spin(fwd,100,pct);
  Drive.turn(50,1);
  Drive.move(17,.8);
  Drive.move(-30,1);
  Drive.turn(50,1);
  intake.spin(fwd,-100,pct);
  Drive.move(30,1);
}

void (*autonsList[])()=
{
  sixball,
  wooshDefense
};

void autonomous()
{
  autonsList[autoSelect]();
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
        lift.open();
        // uppy2.open();
        // lift.open();
        // uppy4.open();
        f4loop = false;
      }
      if (!Shoottogg && f4loop)
      {
        lift.close();
        // uppy2.close();
        // lift.close();
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
        kicker.spin(fwd,100,pct);
        f5loop=false;
      }
      if (!punchythingToggle && f5loop){
        kicker.stop();
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
  vexcodeInit();
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  pre_auton();
  while (true)
  {
    wait(100, msec);
  }
}

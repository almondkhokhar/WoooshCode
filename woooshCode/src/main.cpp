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
competition Competition;
int autoSelect = 0;
int autoNum = 6;

void pre_auton(void)
{
  //Calibrates gyro for auton
  Inertial.calibrate();
  wait(3, sec);
  //Says when you are ready
  con.Screen.print("Ready");

  //Auton selector with potentiometer

  // double potMax = 250;
  // double potMin = 0;
  // double frac;
  // while (!Competition.isDriverControl())
  // {
  //   frac = (potSelector.angle(deg) - potMin) / (potMax - potMin);
  //   autoSelect = floor(frac / (1.0 / autoNum))+1;
  //   con.Screen.clearScreen();
  //   con.Screen.setCursor(1,1);
  //   con.Screen.print(autoSelect);
  //   Brain.Screen.print(autoSelect);
  //   printf("%f\t", potSelector.angle(deg));
  //   printf("%d\n", autoSelect);
  // }
}

// Quals auton to remove ball and touch bar and shoot matchload
// Setup: against bar, with wing deployable intake facing wall
void AWPDefense()
{
  //removes triball
  rightwing.open();
  Drive.move(5 , .3);
  Drive.turn(-40 , 1.2);
  rightwing.close();
  //Shoots matchload
  Drive.turn(-75 , 1);
  kicker.spin(fwd,100,pct);
  wait(1.5 , sec);
  kicker.stop();
  //readjusts and touches bar
  Drive.turn(-40 , 1);
  lift.open();
  wait(.2 , sec);
  lift.close();
  wait(.6 , sec);
  intake.spin(fwd,-100,pct);
  rightwing.open();
  Drive.move(44 , 1.5);
  wait(.5 , sec);
  rightwing.close();
  
}
//Clears triballs starting on our side and removes one triball from the corner on the left side of the red goal
//Setup: Front left wheel in the notch of the field tiles intake up and aimed at the goal red triballs: one with midline at the back of the wing other with one corner in the blue goal
void skills(){
  int startTime = vex::timer::system();
  //shooting matchloads
  kicker.spin(fwd,100,pct);
  wait(30, sec);
  //drops intake
  lift.open();
  //scores 2 red triballs in the blue goal
  Drive.turn(75 , .5);
  kicker.stop();
  lift.close();
  Drive.move(-23 , .6);
  Drive.turn(100 , .5);
  Drive.move(-1000 , .3);
  // readjusts and drives to the triball in the corner of the mid barrier
  Drive.move(5 , .3);
  Drive.turn(39 , .7);
  intake.spin(fwd,100,pct);
  Drive.move(51 , 1);
  //readjusts and pushes triballs over the half bar
  Drive.turn(-60 , .8);
  rightwing.open();
  leftwing.open();
  intake.spin(fwd,-100,pct);
  Drive.move(85 , 1.6);
  leftwing.close();
  rightwing.close();
  //gets into the alley way and pushes triballs towards the goal
  intake.spin(fwd,100,pct);
  Drive.turn(-146 , .65);
  Drive.move(35 , .8);
  Drive.turn(-30 , .7);
  Drive.move(30 , .7);
  Drive.turn(32 , .6);
  leftwing.open();
  intake.spin(fwd,-100,pct);
  Drive.move(70 , 1.3);
  // leftwing.close();
  Drive.move(17 , .7);
  Drive.turn(63 , .55);
  leftwing.open();
  Drive.move(23 , .7);
  Drive.turn(140 , .6);
  //readjusts and pushes into the side of the goal
  leftwing.close();
  Drive.turn(70 , .5);
  Drive.move(10 , .3);
  intake.stop(coast);
  Drive.turn(105 , .4);
  rightwing.open();
  Drive.move(1000 , .6);
  Drive.move(-4 , .4);
  //turns and gets ready for the first push in the front
  rightwing.close();
  Drive.turn(210 , .7);
  intake.spin(fwd,100,pct);
  Drive.move(50 , .8);
  rightwing.open();
  Drive.turn(80 , .8);
  leftwing.open();
  intake.stop(coast);
  //first push in the front
  Drive.swingGood(40 , .75, .4, false);
  Drive.move(1000 , .3);
  Drive.turn(80 , .6);
  leftwing.close();
  rightwing.close();
  Drive.move(-35 , .8);
  intake.spin(fwd,100,pct);
  Drive.turn(130 , .7);
  Drive.move(25 , .6);
  Drive.turn(80 , .8);
  rightwing.open();
  leftwing.open();
  intake.stop(coast);
  Drive.swingGood(30 , .8, .4, false);
  Drive.move(1000 , .45);
  //Drive.turn(32,.3);
  leftwing.close();
  rightwing.close();
  //replace with swing
  Drive.swingGood(-30, .75, .5, true);
  // Drive.move(-10 , .5);
  // intake.spin(fwd,100,pct);
  // Drive.turn(-62 , .6);
  //end replacement
  //replace with swing
  rightwing.open();
  leftwing.open();
  Drive.swingGood(20 , .75, .3, true);
  // Drive.move(10 , .5);
  // Drive.turn(32 , .6);
  //end replacement
  intake.stop(coast);
  Drive.turn(32 , .2);  
  Drive.move(1000,.45);
  Drive.move(-20,.65);
  intake.spin(fwd,100,pct);
  Drive.turn(100 ,.65);
  leftwing.close();
  rightwing.close();
  Drive.move(70,1.2);
  Drive.turn(-30 , .5);
  leftwing.open();
  //replace this with a swing
  Drive.swingGood(40, .7, .6, false);
  // Drive.move(27 , .7);
  // Drive.turn(-75 , .7);
  // end swing replacement
  intake.stop(coast);
  Drive.move(1000 , .3);
  Drive.move(-10,.3);


  printf("%lu\n",(vex::timer::system()-startTime));

}
//scores 6 triballs safely
//Setup: intake facing neutral triball dropdown over the half bar for distance away and centered at that distance matchload in the center of the back of the bot
void sixball() {
  //picks up neutral triball
  intake.spin(fwd,100,pct);
  lift.open();
  wait(.2,sec);
  lift.close();
  wait(.2 , sec);
  //drives backwards to remove the triball in the corner
  Drive.move(-38 , 1.1);
  Drive.turn(150 , .6);
  rightwing.open();
  Drive.move(18.5 , .8);
  // turns and scores all 3 triballs
  Drive.turn(99 , 1);
  intake.spin(fwd,-100,pct);
  // intake.stop(coast);
  rightwing.open();
  Drive.move(2000 , .5);
  Drive.move(-10 , .5);
  Drive.move(2000 , .5);
  Drive.move(-10 , .5);
  rightwing.close();
  //turns to score triball on mid bar only in our zone
  Drive.turn(17 , .9);
  intake.spin(fwd,100,pct);
  Drive.move(52 , 1.1);
  //turns and uses wings to score the triball in the intake and the triball in the center
  Drive.turn(110 , .7);
  Drive.move(17 , .7);
  Drive.turn(180 , .6);
  leftwing.open();
  intake.spin(fwd,-100,pct);
  // intake.stop(coast);
  Drive.move(10000 , .7);
  //reverses to get the last triball and score it
  Drive.move(-15 , .6);
  leftwing.close();
  Drive.turn(9 , 1);
  intake.spin(fwd,100,pct);
  Drive.move(19 , .8);
  Drive.turn(190 , 1);
  intake.spin(fwd,-100,pct);
  // intake.stop(coast);
  rightwing.open();
  leftwing.open();
  Drive.move(1000 , .7);
  rightwing.close();
  leftwing.close();
  //backs away from the goal
  Drive.move(-20 , .5);


}
void doNothing(){
  //does nothing
  allmotors.stop();
  wait(1000000,sec);
}
void testing(){
  Drive.turn(65,2);
}

 
void midrush(){
  int startTime = vex::timer::system();
  intake.spin(fwd,100,pct);
  rightwing.open();
  lift.open();
  wait(.2 , sec);
  lift.close();
  Drive.move(59 , 1);
  rightwing.close();
  Drive.move(-8 , .4);
  Drive.turn(100 , .5);
  intake.stop(coast);
  Drive.move(1000 , .4);
  Drive.move(-15 , .6);
  intake.spin(fwd,100,pct);
  Drive.turn(-75 , .8);
  Drive.move(22 , .7);
  Drive.turn(100 , .9);
  intake.stop(coast);
  Drive.move(1000 , .6);
  rightwing.close();
  Drive.move(-10, .5);
  Drive.turn(250, .7);
  intake.spin(fwd,100,pct);
  Drive.move(36, 1.1);
  Drive.turn(130, .8);
  intake.spin(fwd, -100, pct);
  Drive.move(30 , .9);
  Drive.turn(180, .5);
  Drive.move(22, .9);
  Drive.turn(280 , .8);
  intake.spin(fwd,100,pct);
  Drive.move(30, .9);
  Drive.turn(285, .2);
  Drive.move(-36 , .9);
  Drive.turn(420 , .6);
  rightwing.open();
  Drive.move(17.5 , .7);
  // turns and scores all 3 triballs
  Drive.turn(390 , .4);
  intake.spin(fwd,-100,pct);
  // intake.stop(coast);
  rightwing.open();
  Drive.move(2000 , .5);
  printf("%lu\n",(vex::timer::system()-startTime));


  
  

}
void backBallDefense(){
  lift.open();
  kicker.spin(fwd,100,pct);
  wait(.1,sec);
  lift.close();
  intake.spin(fwd,100,pct);
  Drive.move(56 , 1.2);
  kicker.stop();
  Drive.move(-9 , .8);
  Drive.turn(220 , 1);
  Drive.move(50 , 1);
  Drive.turn(135 , 1);
  rightwing.open();
  Drive.move(5 , 1);
  Drive.turn(100 , .8);
  Drive.turn(135 , .6);
  Drive.move(7 , .6);
  Drive.turn(87 , 1);
  intake.spin(fwd,-100,pct);
  Drive.move(40 , 1);
  rightwing.close();
  Drive.move(-40 , 1);
  Drive.turn(130 , .7);
  Drive.move(-20 , 1);
  Drive.turn(60 , .8);
  Drive.move(-10 , 1);


}

void (*autonsList[])()=
{
  midrush,
  skills,
  testing,
  sixball,
  AWPDefense,
  backBallDefense,
  doNothing,

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

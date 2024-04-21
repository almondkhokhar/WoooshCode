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
#include <math.h>
#include <iostream> 
#define Pi 3.14159265358979323846
#define fieldscale 1.66548042705
#define SL 5 //distance from tracking center to middle of left wheel
#define SR 5 //distance from tracking center to middle of right wheel
#define SS 7.75 //distance from tracking center to middle of the tracking wheel
#define WheelDiam 3.25 //diameter of all the wheels being used for tracking
#define tpr 360  //Degrees per single encoder rotation
double DeltaL,DeltaR,DeltaB,currentL,currentR,PreviousL,PreviousR,DeltaTheta,X,Y,Theta,DeltaXSide,DeltaYSide,SideChord,OdomHeading;
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
bool rbwingtoggle = false;
bool lbwingtoggle = false;
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
  // Brain.Screen.print("Selected: Slot 1");
  // Brain.Screen.setCursor(2,1);
  // Brain.Screen.print("Check Air");
  // Brain.Screen.setCursor(3,1);
  // Brain.Screen.print("Skills");
  // Brain.Screen.setCursor(4,1);
  // Brain.Screen.print("Setting Tool SKILLS");
  // Brain.Screen.setCursor(5,1);
  // Brain.Screen.print("Triball On Rear and Partially in Goal");

  // Brain.Screen.print("Selected: Slot 2");
  // Brain.Screen.setCursor(2,1);
  // Brain.Screen.print("Check Air");
  // Brain.Screen.setCursor(3,1);
  // Brain.Screen.print("Four Ball Near Side");
  // Brain.Screen.setCursor(4,1);
  // Brain.Screen.print("Setting Tool 1");
  // Brain.Screen.setCursor(5,1);
  // Brain.Screen.print("Just Wing It");
  // Brain.Screen.setCursor(6,1);
  // Brain.Screen.print("Triball On Left Wing");
  // Brain.Screen.setCursor(7,1);
  // Brain.Screen.print("FINALS NO BAR TOUCH");

  Brain.Screen.print("Selected: Slot 3");
  Brain.Screen.setCursor(2,1);
  Brain.Screen.print("Check Air");
  Brain.Screen.setCursor(3,1);
  Brain.Screen.print("Four Ball Near Side");
  Brain.Screen.setCursor(4,1);
  Brain.Screen.print("Setting Tool 2");
  Brain.Screen.setCursor(5,1);
  Brain.Screen.print("Set Tool Edge on Goofy Corner");
  Brain.Screen.setCursor(6,1);
  Brain.Screen.print("Triball On Left Wing");
  Brain.Screen.setCursor(7,1);
  Brain.Screen.print("FINALS NO BAR TOUCH");

  // Brain.Screen.print("Selected: Slot 4");
  // Brain.Screen.setCursor(2,1);
  // Brain.Screen.print("Check Air");
  // Brain.Screen.setCursor(3,1);
  // Brain.Screen.print("Five Ball Near Side");
  // Brain.Screen.setCursor(4,1);
  // Brain.Screen.print("Setting Tool 1");
  // Brain.Screen.setCursor(5,1);
  // Brain.Screen.print("REMAKE TOOL");
  // Brain.Screen.setCursor(6,1);
  // Brain.Screen.print("Triball On Left Wing");
  // Brain.Screen.setCursor(7,1);
  // Brain.Screen.print("FINALS NO BAR TOUCH");

  // Brain.Screen.print("Selected: Slot 5");
  // Brain.Screen.setCursor(2,1);
  // Brain.Screen.print("Check Air");
  // Brain.Screen.setCursor(3,1);
  // Brain.Screen.print("Five Ball Near Side");
  // Brain.Screen.setCursor(4,1);
  // Brain.Screen.print("Setting Tool 1");
  // Brain.Screen.setCursor(5,1);
  // Brain.Screen.print("REMAKE TOOL");
  // Brain.Screen.setCursor(6,1);
  // Brain.Screen.print("Triball On Left Wing");
  // Brain.Screen.setCursor(7,1);
  // Brain.Screen.print("Touches Bar");

  // Brain.Screen.print("Selected: Slot 6");
  // Brain.Screen.setCursor(2,1);
  // Brain.Screen.print("Check Air");
  // Brain.Screen.setCursor(3,1);
  // Brain.Screen.print("Five Ball Far Side");
  // Brain.Screen.setCursor(4,1);
  // Brain.Screen.print("Setting Tool 2");
  // Brain.Screen.setCursor(5,1);
  // Brain.Screen.print("NOT YET CREATED");
  // Brain.Screen.setCursor(6,1);
  // Brain.Screen.print("Triball On Right Wing");
  // Brain.Screen.setCursor(7,1);
  // Brain.Screen.print("Touches Bar MAYBE");

  // Brain.Screen.print("Selected: Slot 7");
  // Brain.Screen.setCursor(2,1);
  // Brain.Screen.print("Check Air");
  // Brain.Screen.setCursor(3,1);
  // Brain.Screen.print("Six Ball Far Side");
  // Brain.Screen.setCursor(4,1);
  // Brain.Screen.print("Setting Tool 2");
  // Brain.Screen.setCursor(5,1);
  // Brain.Screen.print("NOT YET CREATED");
  // Brain.Screen.setCursor(6,1);
  // Brain.Screen.print("Triball On Right Wing");
  // Brain.Screen.setCursor(7,1);
  // Brain.Screen.print("NO BAR TOUCH");

  // Brain.Screen.print("Selected: Slot 8");
  // Brain.Screen.setCursor(2,1);
  // Brain.Screen.print("Check Air");
  // Brain.Screen.setCursor(3,1);
  // Brain.Screen.print("Five Ball Far Side");
  // Brain.Screen.setCursor(4,1);
  // Brain.Screen.print("Setting Tool 1");
  // Brain.Screen.setCursor(5,1);
  // Brain.Screen.print("3 Puzzle Pieces Away From Black Bar");
  // Brain.Screen.setCursor(6,1);
  // Brain.Screen.print("Triball On Right Wing");
  // Brain.Screen.setCursor(7,1);
  // Brain.Screen.print("NO BAR TOUCH");
  //Auton selector with potentiometer
}

int lfQuickfire(){
  leftwing.open();
  wait(.2, sec);
  leftwing.close();
  return (0);
}
int lfSlow(){
  wait(.2, sec);
  leftwing.open();
  return(0);
}
int rfQuickfire(){
  rightwing.open();
  wait(.2, sec);
  rightwing.close();
  return (0);
}
int slowDrop(){
  wait(.1, sec);
  rDropDown.open();
  return(0);
}

void AWPDefense()
{
  //removes triball
  rDropDown.open();
  Drive.move(5 , .3);
  Drive.turn(-39 , 1.2);
  rDropDown.close();
  //Shoots matchload
  wait(.6 , sec);
  intake.spin(fwd,-100,pct);
  wait(7, sec);
  rightwing.open();
  Drive.move(42 , 2);
  wait(.5 , sec);
  rightwing.close();
  
}
//Clears triballs starting on our side and removes one triball from the corner on the left side of the red goal
//Setup: Front left wheel in the notch of the field tiles intake up and aimed at the goal red triballs: one with midline at the back of the wing other with one corner in the blue goal


void doNothing(){
  //does nothing
}


void fiveMidFar() {
  int startTime = vex::timer::system();
  task rwing = task(rfQuickfire);
  intake.spin(fwd, 100, pct);
  Drive.move(48, .95);
  Drive.move(-5, .4);
  intake.stop();
  Drive.turn(97, .6);
  intake.spin(fwd, -100, pct);
  wait(.3, sec);
  Drive.move(1000, .6);
  Drive.move(-37, .7);
  intake.spin(fwd, 100, pct);
  Drive.turn(230, .7);
  Drive.move(17, .55);
  Drive.turn(145, .75);

  Drive.move(52, 1.2);
  Drive.turn(55, .6);
  rDropDown.open();
  intake.spin(fwd,-100, pct);
  Drive.move(18, .5);
  Drive.turn(10, .5);
  rDropDown.close();
  wait(.1, sec);
  Drive.turn(-110, .8);
  Drive.move(40, .8);
  Drive.turn(-77, .5);
  intake.spin(fwd, 100, pct);
  Drive.move(20, .9);
  Drive.move(-50, 1);
  Drive.turn(60, .7);
  intake.spin(fwd,-100, pct);
  leftwing.open();
  Drive.swing(30, .7, .6, 3, false);
  Drive.move(1000, .3);
  Drive.move(-10, .3);
  leftwing.close();
  // wait(.2, sec);
  Drive.move(1000, .4);
  Drive.move(-10, .4);

  




  
  printf("%lu\n",(vex::timer::system()-startTime));
}

void sixMidFar(){
  int startTime = vex::timer::system();
  task rwing = task(rfQuickfire);
  intake.spin(fwd, 100, pct);
  Drive.move(60, 1.2);


  printf("%lu\n",(vex::timer::system()-startTime));
}
void fourMidNearset1(){
  int startTime = vex::timer::system();
  task lwing = task(lfQuickfire);
  intake.spin(fwd,100,pct);
  Drive.move(49, 1);
  Drive.move(-54, 1.2);
  Drive.turn(70, 1);
  intake.spin(fwd, -100, pct);
  Drive.turn(100, .8);
  leftwing.open();
  Drive.move(-28, .7);
  leftwing.close();
  Drive.turn(130, .8);
  task dropSlow = task(slowDrop);
  Drive.move(25, .7);
  Drive.turn(30, .8);
  rDropDown.close();
  Drive.turn(120, .8);
  Drive.move(-20, .7);
  Drive.turn(170, .8);
  rDropDown.open();
  Drive.move(-15, .6);
  Drive.move(5, .4);
  rDropDown.close();
  Drive.turn(120, .8);
  rightwing.open();
  Drive.move(36, .8);
  Drive.turn(80, .7);
  rightwing.close();
  Drive.move(29, .8);
  Drive.turn(77, .4);
  Drive.move(-40, .8);
  Drive.turn(130, .4);
  printf("%lu\n",(vex::timer::system()-startTime));
}
void fourMidNearset2(){
  int startTime = vex::timer::system();
  task lwing = task(lfQuickfire);
  intake.spin(fwd, 100, pct);
  Drive.swing(65, 1.4, .86, 3, false);
  Drive.move(-20, .7);
  Drive.turn(-160, .8);
  Drive.move(58, 1.2);
  Drive.turn(-240, .7);
  task dropSlow = task(slowDrop);
  Drive.move(17, .6);
  Drive.turn(-300, .5);
  rDropDown.close();
  intake.spin(fwd, -100, pct);
  wait(.5, sec);
  Drive.turn(-260, .7);
  Drive.move(-27, .7);
  Drive.turn(-210, .5);
  rDropDown.open();
  Drive.move(-20, .6);
  Drive.turn(-215, .5);
  intake.spin(fwd, 100, pct);
  rDropDown.close();
  Drive.move(30, .8);
  Drive.turn(-300, .7);

  printf("%lu\n",(vex::timer::system()-startTime));
}

void fiveMidNear(){
  int startTime = vex::timer::system();
  task lwing = task(lfQuickfire);
  intake.spin(fwd,100,pct);
  Drive.move(50, 1);
  Drive.turn(80, .6);
  task slowlwing = task(lfSlow);
  Drive.move(28, .7);
  intake.stop();
  Drive.turn(75, .5);
  Drive.move(-20, .65);
  Drive.turn(190, .8);
  leftwing.close();
  Drive.move(53, 1.1);
  Drive.turn(110, .6);
  Drive.move(-24, .7);
  Drive.turn(167, .6);
  rDropDown.open();
  Drive.move(-17.6, .6);
  Drive.turn(167, .3);
  rDropDown.close();
  Drive.move(24, .7);
  Drive.turn(130, .6);
  task dropSlow = task(slowDrop);
  Drive.move(16.5, .6);
  Drive.turn(45, .4);
  wait(.5, sec);
  Drive.turn(130, .5);
  rDropDown.close();
  Drive.move(12, .6);
  Drive.turn(75, .6);
  intake.spin(fwd, -100, pct);
  Drive.move(33, .9);
  Drive.turn(77, .3);
  // Drive.move(-40, .8);
  // Drive.turn(130, .3);
  // Drive.move(-10, .5);
 
  printf("%lu\n",(vex::timer::system()-startTime));

}
void testing() {
  Drive.swing(65, 15, .6, 3, false);
}

void (*autonsList[])()=
{
  fourMidNearset2,
  doNothing, 
  fiveMidFar,
  fourMidNearset1,
  testing,
  fiveMidNear,
  sixMidFar,
};

void autonomous()
{
  autonsList[autoSelect]();
}

int conInfo(){
  while (true){
  con.Screen.clearScreen();
  con.Screen.setCursor(1,1);
  con.Screen.print("Battery:");
  con.Screen.print(Brain.Battery.capacity(percent));
  con.Screen.setCursor(2,1);
  con.Screen.print("Left  ");
  con.Screen.print((left1.temperature(fahrenheit)+left2.temperature(fahrenheit)+left3.temperature(fahrenheit))/3);
  con.Screen.setCursor(3,1);
  con.Screen.print("Right  ");
  con.Screen.print((right1.temperature(fahrenheit)+right2.temperature(fahrenheit)+right3.temperature(fahrenheit))/3);
  wait(1, sec);
  }
  return(0);
}
void usercontrol()
{
 //r2 intake reverse hold,
 // r1 intake fwd hold,
 // l1 shoot toggle,
 // l2 hang hold tap to fire piston then,
 //y right frontwing,
 // b right backwing,
 // right arrow front leftwing
 // down arrow back leftwing
 task printcon = task(conInfo);
 while (true)
 {
   // driving portion
   // controls the speed at which the robot moves
   //moving controls
   rightdrive.spin(fwd, con.Axis2.value(), pct);
   leftdrive.spin(fwd, con.Axis3.value(), pct);
   //intake controls
   if (con.ButtonR2.pressing()){
     intake.spin(fwd, -100, pct);
   }
   else if (con.ButtonR1.pressing()){
     intake.spin(fwd, 100, pct);
   }
   else{
     intake.stop(hold);
   }
   //kicker controls

    if (con.ButtonL2.pressing())
   {
    if (f6loop){
      f6loop=false;
      if (f7loop){
        hang.open();
        con.rumble(".-..--.--..");
        f7loop=false;
      }
      else{
        kicker.spin(fwd,-100,pct);
        kicker2.spin(fwd, -100,pct);
      }
    }
    }
    else if (con.ButtonL1.pressing())
    {
      if (f5loop){
        f5loop = false;
        punchythingToggle=!punchythingToggle;
      }
    }
    else
    {
      f5loop = true;
    }
    if (!con.ButtonL2.pressing()){
      f6loop=true;
    }
    if (punchythingToggle)
    {
      kicker.spin(fwd,100,pct);
      kicker2.spin(fwd,100,pct);
    }
    else if (!con.ButtonL2.pressing()) {
      kicker.stop();
      kicker2.stop();
    }
  


   //leftwing control
   if (con.ButtonRight.pressing())
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


   //rightwing control
   if (con.ButtonY.pressing())
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


   //right back wing control
   if (con.ButtonB.pressing())
   {
     if (f3loop)
     {
       rbwingtoggle = !rbwingtoggle;
     }
     if (rbwingtoggle && f3loop)
     {
       rDropDown.open();
       f3loop = false;
     }
     if (!rbwingtoggle && f3loop)
     {
       rDropDown.close();
       f3loop = false;
     }
   }
   else
   {
     f3loop = true;
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

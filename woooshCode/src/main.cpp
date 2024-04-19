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

  //Auton selector with potentiometer
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
void newskills(){
  int startTime = vex::timer::system();
  //shooting matchloads
  // kicker.spin(fwd,100,pct);
  // wait(29.8, sec);
  // //drops intake
  hang.open();
  //scores 2 red triballs in the blue goal
  Drive.turn(75 , .5);
  kicker.stop();
  hang.close();
  Drive.move(-23 , .6);
  Drive.turn(100 , .5);
  Drive.move(-1000 , .3);
  // readjusts and drives to the triball in the corner of the mid barrier
  Drive.move(5 , .3);
  Drive.turn(39 , .7);
  intake.spin(fwd,100,pct);
  Drive.move(52 , 1);
  //readjusts and pushes triballs over the half bar
  Drive.turn(-61 , .8);
  rightwing.open();
  leftwing.open();
  intake.spin(fwd,-100,pct);
  Drive.move(85 , 1.6);
  wait(.03, sec);
  leftwing.close();
  rightwing.close();
  //gets into the alley way and pushes triballs towards the goal
  intake.spin(fwd,100,pct);
  Drive.turn(-146 , .65);
  Drive.move(50 , 1.1);
  Drive.turn(-35 , .7);
  Drive.swingGood(34, .8, .5, true);
  Drive.turn(34, .4);
  rightwing.open();
  intake.spin(fwd,-100,pct);
  Drive.move(76 , 1.7);
  Drive.turn(39, .3);
  Drive.swingGood(36, .9, .6, true);
  //readjusts and pushes into the side of the goal
  Drive.swingGood(20, .7, .8, true);
  intake.stop(coast);
  Drive.move(1000 , .6);
  Drive.move(-7 , .5);
  rightwing.close();
  Drive.turn(205 , .6);
  intake.spin(fwd,100,pct);
  rightwing.open();
  Drive.move(50 , .8);
  Drive.turn(80 , .8);
  leftwing.open();
  intake.spin(fwd,-100,pct);
  //first push in the front
  Drive.swingGood(40 , .9, .4, false);
  intake.stop(coast);
  Drive.move(1000 , .3);
  Drive.move(-6, .4);
  leftwing.close();
  rightwing.close();
  Drive.turn(-115, .9);
  intake.spin(fwd,100,pct);
  Drive.move(25, .8);
  rightwing.open();
  Drive.turn(-255, .9);
  Drive.move(40, 1.2);
  Drive.turn(-360, .7);
  intake.stop(coast);
  leftwing.open();
  Drive.move(1000, 1);
  Drive.move(-6, .4);
  printf("%lu\n",(vex::timer::system()-startTime));

}


void doNothing(){
  //does nothing
}

 

void backBallDefense(){
  leftwing.open();
  hang.open();
  wait(.2,sec);
  hang.close();
  leftwing.close();
  intake.spin(fwd,100,pct);
  Drive.move(56 , 1.2);
  Drive.move(-9 , .8);
  Drive.turn(220 , 1);
  Drive.move(48 , 1.3);
  Drive.turn(135 , 1);
  rightwing.open();
  Drive.move(5 , .4);
  Drive.turn(100 , .8);
  rightwing.close();
  Drive.move(-15, .6);
  Drive.turn(190, .55);
  Drive.move(-12 , .85);
  Drive.move(10 , .5);
  Drive.turn(120 , .6);
  rightwing.open();
  Drive.move(33 , 1);
  Drive.turn(80 , .8);
  intake.spin(fwd,-100,pct);
  Drive.move(25 , 1.1);
}



//new autons

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
  wait(.2, sec);
  rDropDown.open();
  return(0);
}
void fiveMidFar() {
  int startTime = vex::timer::system();
  task rwing = task(rfQuickfire);
  intake.spin(fwd, 100, pct);
  Drive.move(48, 1);
  Drive.move(-5, .4);
  intake.stop();
  Drive.turn(97, .7);
  intake.spin(fwd, -100, pct);
  wait(.3, sec);
  Drive.move(1000, .5);
  //leftwing.close();
  Drive.move(-37, .7);
  intake.spin(fwd, 100, pct);
  Drive.turn(230, .9);
  Drive.move(17, .6);
  Drive.turn(145, .7);
  intake.stop();
  Drive.move(51, 1.1);
  Drive.turn(55, .6);
  rDropDown.open();
  Drive.move(17, .6);
  Drive.turn(0, .5);
  rDropDown.close();
  intake.spin(fwd,-100, pct);
  wait(.2, sec);
  Drive.turn(10, .3);
  Drive.move(1000, .6);
  Drive.move(-10, .4);
  Drive.turn(10, .3);
  Drive.move(1000, .5);
  Drive.move(-20, .6);
  Drive.turn(-110, .7);
  Drive.move(40, .9);
  Drive.turn(-70, .4);
  intake.spin(fwd,100, pct);
  Drive.move(24, .6);


  
  printf("%lu\n",(vex::timer::system()-startTime));
}
void fourMidNear(){
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

void fiveMidNear(){
  int startTime = vex::timer::system();
  task lwing = task(lfQuickfire);
  intake.spin(fwd,100,pct);
  Drive.move(50, 1);
  Drive.turn(80, .6);
  task slowlwing = task(lfSlow);
  Drive.move(23, .7);
  intake.stop();
  Drive.turn(75, .5);
  Drive.move(-20, .7);
  Drive.turn(190, .8);
  leftwing.close();
  Drive.move(53, 1.1);
  Drive.turn(100, .6);
  Drive.move(-24, .7);
  Drive.turn(167, .6);
  rDropDown.open();
  Drive.move(-17.6, .6);
  Drive.turn(167, .3);
  rDropDown.close();
  Drive.move(20, .7);
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
  Drive.move(35, .9);
  Drive.turn(77, .3);
  Drive.move(-40, .8);
  Drive.turn(130, .4);
 
  printf("%lu\n",(vex::timer::system()-startTime));

}
void testing() {
  Drive.turn(45, 15);
}

void (*autonsList[])()=
{
  fiveMidFar,
  doNothing, 
  fourMidNear,
  fiveMidNear,
  AWPDefense,
  testing,
  newskills,
  backBallDefense,
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

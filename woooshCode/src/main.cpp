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
  Brain.resetTimer();
  //sets starting position at (0,0) and resets motor encoders
  right1.setPosition(0, deg);
  right2.setPosition(0, deg);
  right3.setPosition(0, deg);
  left1.setPosition(0, deg);
  left2.setPosition(0, deg);
  left3.setPosition(0, deg);


  //SET VALUES FOR INITIAL ROBOT POSITION
  X = 0;
  Y = 0;
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
void positionTracker() {
// 2 cases could be occuring in odometry
// 1: Going in a straight line
// 2: Going in an arc motion
// If the bot is on an angle and going straight the displacement would be linear at angle Theta, meaning a right triangle is formed (Trig ratios to calc movement)
// Since it is a linear motion, the Left and right will move the same amount so we can just pick a side and do our movement calculation
// Since this calculation is working based of very infinitely small arcs, the displacement of the robot will be a chord
// Averages the Left and Right integrated motor encoders since we don't have encoders yet
  currentR = (right1.position(degrees) + right2.position(degrees)+(right3.position(degrees))) / 3;
  currentL = (left1.position(degrees) + left2.position(degrees)+(left3.position(degrees))) / 3;

  //Creates variables for change in each side info in inches (12.9590697 is circumference of wheel)
  DeltaL = ((currentL - PreviousL) * 12.9590697) / tpr;
  DeltaR = ((currentR - PreviousR) * 12.9590697) / tpr;
  //DeltaB = ((currentB - PreviousB) * 12.9590697) / tpr;

  //Determines the change in angle of the robot using the rotational change in each side
  DeltaTheta = (DeltaR - DeltaL) / (SL + SR);

  if(DeltaTheta == 0) {  //If there is no change in angle
    X += DeltaL * sin (Theta);
    Y += DeltaL * cos (Theta);
    //X += DeltaB * cos (Theta + 1.57079633);
    //Y += DeltaB * sin (Theta + 1.57079633);

  //If there is a change in angle, it will calculate the changes in X,Y from chords of an arc/circle.
  } else {  //If the angle changes
      SideChord = 2 * ((DeltaL / DeltaTheta) + SL) * sin (DeltaTheta / 2);
      //BackChord = 2 * ((DeltaB / DeltaTheta) + SS) * sin (DeltaTheta / 2);
      DeltaYSide = SideChord * cos (Theta + (DeltaTheta / 2));
      DeltaXSide = SideChord * sin (Theta + (DeltaTheta / 2));
      //DeltaXBack = BackChord * sin (Theta + (DeltaTheta / 2));
      //DeltaYBack = -BackChord * cos (Theta + (DeltaTheta / 2));
      Theta += DeltaTheta;
      X += DeltaXSide;
      Y += DeltaYSide;
    }

    //Odom heading is converting the radian value of Theta into degrees
    OdomHeading = Theta * 57.295779513;

    //Converts values into newer values to allow for code to effectively work in next cycle
    PreviousL = currentL;
    PreviousR = currentR;
    DeltaTheta = 0;
  /*--------------------Fancy Brain--------------------*/
    //Coordinates for each section of text
    int textadjustvalue = 55;
    int rowadjust = 39;

    //Sets graphical things for our display 
    Brain.Screen.setPenWidth( 1 );
    vex::color graytile = vex::color( 49, 51, 53 );
    Brain.Screen.setFillColor(vex::color( 0, 0, 0 ));
    Brain.Screen.setFont(vex::fontType::mono20);
    Brain.Screen.setPenColor( vex::color( 222, 49, 99 ) );

    //Displays all the field tiles, text of odom values, and a dot symbolizing the robot
    Brain.Screen.printAt(40,20 + textadjustvalue, "X-Pos:%f",-X);
    Brain.Screen.setPenColor( vex::color( 191, 10, 48 ) );
    Brain.Screen.printAt(40,50 + textadjustvalue, "Y-Pos:%f",Y);
    Brain.Screen.setPenColor( vex::color( 141, 2, 31 ) );
    Brain.Screen.printAt(40,80 + textadjustvalue, "Theta:%f",Theta);
    Brain.Screen.setPenColor( vex::color( 83, 2, 1 ) );
    Brain.Screen.printAt(40,110 + textadjustvalue, "Angle:%f",OdomHeading);
    Brain.Screen.setPenColor( vex::color( 255, 255, 255 ) );
    Brain.Screen.setFillColor( graytile );
    Brain.Screen.drawRectangle( 245, 2, 234, 234 );
    Brain.Screen.drawRectangle( 245, 2, 39, 39 );
    Brain.Screen.drawRectangle( 245, 80, 39, 39 );
    Brain.Screen.drawRectangle( 245, 119, 39, 39 );
    Brain.Screen.drawRectangle( 245, 197, 39, 39 );
    Brain.Screen.drawRectangle( 245+rowadjust, 2, 39, 39 );
    Brain.Screen.drawRectangle( 245+rowadjust, 41, 39, 39 );
    Brain.Screen.drawRectangle( 245+rowadjust, 80, 39, 39 );
    Brain.Screen.drawRectangle( 245+rowadjust, 119, 39, 39 );
    Brain.Screen.drawRectangle( 245+rowadjust, 158, 39, 39 );
    Brain.Screen.drawRectangle( 245+rowadjust, 197, 39, 39 );
    Brain.Screen.drawRectangle( 245+(2*rowadjust), 2, 39, 39 );
    Brain.Screen.drawRectangle( 245+(2*rowadjust), 41, 39, 39 );
    Brain.Screen.drawRectangle( 245+(2*rowadjust), 80, 39, 39 );
    Brain.Screen.drawRectangle( 245+(2*rowadjust), 119, 39, 39 );
    Brain.Screen.drawRectangle( 245+(2*rowadjust), 158, 39, 39 );
    Brain.Screen.drawRectangle( 245+(2*rowadjust), 197, 39, 39 );
    Brain.Screen.drawRectangle( 245+(3*rowadjust), 2, 39, 39 );
    Brain.Screen.drawRectangle( 245+(3*rowadjust), 41, 39, 39 );
    Brain.Screen.drawRectangle( 245+(3*rowadjust), 80, 39, 39 );
    Brain.Screen.drawRectangle( 245+(3*rowadjust), 119, 39, 39 );
    Brain.Screen.drawRectangle( 245+(3*rowadjust), 158, 39, 39 );
    Brain.Screen.drawRectangle( 245+(3*rowadjust), 197, 39, 39 );
    Brain.Screen.drawRectangle( 245+(4*rowadjust), 2, 39, 39 );
    Brain.Screen.drawRectangle( 245+(4*rowadjust), 41, 39, 39 );
    Brain.Screen.drawRectangle( 245+(4*rowadjust), 80, 39, 39 );
    Brain.Screen.drawRectangle( 245+(4*rowadjust), 119, 39, 39 );
    Brain.Screen.drawRectangle( 245+(4*rowadjust), 158, 39, 39 );
    Brain.Screen.drawRectangle( 245+(4*rowadjust), 197, 39, 39 );
    Brain.Screen.drawRectangle( 245+(5*rowadjust), 2, 39, 39 );
    Brain.Screen.drawRectangle( 245+(5*rowadjust), 80, 39, 39 );
    Brain.Screen.drawRectangle( 245+(5*rowadjust), 119, 39, 39 );
    Brain.Screen.drawRectangle( 245+(5*rowadjust), 197, 39, 39 );
    Brain.Screen.drawRectangle( 245, 158, 39, 39 );
    Brain.Screen.drawRectangle( 245, 41, 39, 39 );
    Brain.Screen.drawRectangle( 245+(5*rowadjust), 41, 39, 39 );
    Brain.Screen.drawRectangle( 245+(5*rowadjust), 158, 39, 39 );
    Brain.Screen.setPenColor( vex::color( 255,255,255));
    Brain.Screen.setFillColor( vex::color(0,0,0) );
    

    
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
  // wait(30.2, sec);
  // //drops intake
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
  Drive.swingGood(34, .8, .52, true);
  Drive.turn(37.8, .4);
  rightwing.open();
  intake.spin(fwd,-100,pct);
  Drive.move(76 , 1.7);
  Drive.turn(39, .3);
  Drive.swingGood(36, .9, .6, true);
  // //readjusts and pushes into the side of the goal
  Drive.swingGood(20, .7, .8, true);
  intake.stop(coast);
  Drive.move(1000 , .6);
  Drive.move(-5 , .4);
  //turns and gets ready for the first push in the front
  rightwing.close();
  Drive.turn(210 , .8);
  intake.spin(fwd,100,pct);
  Drive.move(50 , .8);
  rightwing.open();
  Drive.turn(75 , .8);
  leftwing.open();
  intake.spin(fwd,-100,pct);
  //first push in the front
  Drive.swingGood(33 , .9, .4, false);
  intake.stop(coast);
  Drive.move(1000 , .4);
  Drive.move(-4 , .3);
  Drive.move(1000 , .4);
  leftwing.close();
  rightwing.close();
  Drive.turn(-80, .8);
  Drive.move(20, .65);
  Drive.turn(-260, 1.2);
  Drive.move(15, .55);
  rightwing.open();
  leftwing.open();
  Drive.swingGood(35, .9, .4, false);
  Drive.move(1000 , .45);
  // leftwing.close();
  // rightwing.close();
  // intake.stop(coast);
  // Drive.turn(32 , .2);  
  // Drive.move(-23 , .65);
  // intake.spin(fwd, 100, pct);
  // leftwing.open();
  // Drive.turn(105 , .6);
  // Drive.move(58 , 1.1);
  // Drive.turn(-30 , .8);
  // rightwing.open();
  // Drive.swingGood(36 , .8, .53, false);
  // intake.spin(fwd, -100, pct);
  // Drive.move(1000 , .4);
  // Drive.move(-10, .4);
  // Drive.move(1000 , .4);
  // Drive.move(-10 , .4);
  printf("%lu\n",(vex::timer::system()-startTime));

}
//scores 6 triballs safely
//Setup: intake facing neutral triball dropdown over the half bar for distance away and centered at that distance matchload in the center of the back of the bot
void sixball() {
  int startTime = vex::timer::system();
  //picks up neutral triball
  intake.spin(fwd,100,pct);
  lift.open();
  wait(.2,sec);
  lift.close();
  wait(.2, sec);
  //drives backwards to remove the triball in the corner
  Drive.move(-38 , 1);
  Drive.turn(150 , .6);
  rightwing.open();
  Drive.move(18.5 , .8);
  // turns and scores all 3 triballs
  Drive.turn(99 , 1);
  intake.spin(fwd,-100,pct);
  // intake.stop(coast);
  rightwing.open();
  Drive.move(2000 , .5);
  Drive.move(-10 , .3);
  Drive.move(2000 , .4);
  Drive.move(-10 , .5);
  rightwing.close();
  //turns to score triball on mid bar only in our zone
  Drive.turn(16.5 , .85);
  intake.spin(fwd,100,pct);
  Drive.move(52 , 1.05);
  //turns and uses wings to score the triball in the intake and the triball in the center
  Drive.turn(110 , .65);
  Drive.move(16 , .6);
  intake.stop(coast);
  Drive.turn(180 , .45);
  leftwing.open();
  intake.spin(fwd,-100,pct);
  // intake.stop(coast);
  Drive.move(10000 , .7);
  //reverses to get the last triball and score it
  Drive.move(-15 , .6);
  leftwing.close();
  Drive.turn(9 , .75);
  intake.spin(fwd,100,pct);
  Drive.move(21 , .7);
  Drive.turn(190 , .8);
  intake.spin(fwd,-100,pct);
  // intake.stop(coast);
  rightwing.open();
  leftwing.open();
  Drive.move(1000 , .6);
  rightwing.close();
  leftwing.close();
  //backs away from the goal
  Drive.move(-10 , .6);
  // Drive.turn(320 , .7);
  // Drive.move(90 , 1.06);
  // dropDown.open();
  printf("%lu\n",(vex::timer::system()-startTime));


}
void doNothing(){
  //does nothing
  allmotors.stop();
  wait(1000000,sec);
}
void testing(){
  Drive.turn(65,2);
}
void easymidrush (){
  rightwing.open();
  lift.open();
  wait(.2 , sec);
  lift.close();
  intake.spin(fwd, 100, pct);
  Drive.swingGood(60 , 1.2, .4, false);
  Drive.turn(100 , .7);
  Drive.move(1000 , .7);
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
  Drive.move(-6 , .4);
  Drive.turn(95 , .5);
  intake.stop(coast);
  Drive.move(1000 , .6);
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
  Drive.move(33, .9);
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
  Drive.move(20.5 , .8);
  // turns and scores all 3 triballs
  Drive.turn(380 , .6);
  intake.spin(fwd,-100,pct);
  // intake.stop(coast);
  rightwing.open();
  Drive.move(2000 , .5);
  printf("%lu\n",(vex::timer::system()-startTime));


  
  

}
void backBallDefense(){
  leftwing.open();
  lift.open();
  wait(.2,sec);
  lift.close();
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
  Drive.move(-15 , .6);
  Drive.turn(190 , .55);
  Drive.move(-12 , .85);
  Drive.move(10 , .5);
  Drive.turn(120 , .6);
  rightwing.open();
  Drive.move(33 , 1);
  Drive.turn(80 , .8);
  intake.spin(fwd,-100,pct);
  Drive.move(25 , 1.1);

  // Drive.turn(135 , .6);
  // Drive.move(7 , .6);
  // Drive.turn(87 , 1);
  // intake.spin(fwd,-100,pct);
  // Drive.move(40 , 1);
  // rightwing.close();
  // Drive.move(-40 , 1);
  // Drive.turn(130 , .7);
  // Drive.move(-20 , 1);
  // Drive.turn(60 , .8);
  // Drive.move(-10 , 1);


}

void (*autonsList[])()=
{
  skills,
  sixball,
  AWPDefense,
  backBallDefense,
  easymidrush,
  testing,
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
    positionTracker();
    Brain.Screen.render(); //push data to the LCD all at once to prevent image flickering
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
        f4loop = false;
      }
      if (!Shoottogg && f4loop)
      {
        lift.close();
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

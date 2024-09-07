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


// make class called apple and make apple.myapple can place properties about all of the apples, like ripeness, color, myapple.ripeness()=5 days, myapple2.ripeness()= 7 days, motor is a class for vex motors with properties such as spin, temperature, so you can make a class drivetrain with inputs of drivegroups left and right and then make a drivestraight function inside the drive class, odom applications: take wheel diameter input so when you had a previous wheel diameter for your robot you can change that parameter when you rebuild and all of your code still works. 
// error is loss function, how far away are we from where we want to be. P value is just some number multiplied by your error and does most of the work to get you where you want to be. if p is to small your motor input will be to low to do anything and you won't reach the point you want to. if p is too high then you will reach the point you want to, but then you will overshoot it because you are going to fast so it will oscillate a lot. so you can try to get the P value very exact but its difficult and take a long time to tune, so what you can do is have it a little higher and then subtract your velocity. speed = error times kp - derivative of error times kd. what that does is calculate velocity and if we are moving faster move slower so we don't over shoot our target. dampening works by allowing us to not have to be super exact with our kp and dampen it's affect as we get closer to the target. when we are close to where we want to be but not eactly there the p value is basically 0 and the d value is basically 0 so you will be very close, but never exactly where you want to be. The I value which stands for integral is just the theoretical area under the graph of position vs time, telling you how long you've been that far away from your target. Derivative is current error and prev error starts at current error but after the first loop it becomes your current error, then current error updates, then you calculate your speed, and then your previous error. the way you track your integral is you take your error sum starting at 0 and every loop you just add your error to it, errorsum += error. so speed = error * kP + errorsum * kI - deriv of error * kD, then tune it until you have each value affecting the program how you want, not just one individual part of it. no analytical way to find kp ki and kd so you have to take educated guesses and test your program until you have a program that functions how you want it to 
#include "vex.h"
double DeltaL, DeltaR, DeltaB, currentL, currentR, PreviousL, PreviousR, DeltaTheta, X, Y, Theta, DeltaXSide, DeltaYSide, SideChord, OdomHeading;
// initializes variables
class Drive
{
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
bool dropdowntoggle = false;
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
  // Calibrates gyro for auton
  Inertial.calibrate();
  wait(3, sec);
  // Says when you are ready
  con.Screen.print("Ready");
  // Brain.Screen.print("Selected: Slot 1");
  // Brain.Screen.setCursor(2,1);
  // Brain.Screen.print("Check Air");
  // Brain.Screen.setCursor(3,1);
  // Brain.Screen.print("Skills");
  // Brain.Screen.setCursor(4,1);
  // Brain.Screen.print("Setting Tool SKILLS");
  // Brain.Screen.setCursor(5,1);

  // Brain.Screen.print("Selected: Slot 2");
  // Brain.Screen.setCursor(2,1);
  // Brain.Screen.print("Check Air");
  // Brain.Screen.setCursor(3,1);
  // Brain.Screen.print("Four Ball Near Side");
  // Brain.Screen.setCursor(4,1);
  // Brain.Screen.print("Setting Tool 1");
  // Brain.Screen.setCursor(5,1);


  // Brain.Screen.print("Selected: Slot 3");
  // Brain.Screen.setCursor(2, 1);
  // Brain.Screen.print("Check Air");
  // Brain.Screen.setCursor(3, 1);
  // Brain.Screen.print("Four Ball Near Side");
  // Brain.Screen.setCursor(4, 1);
  // Brain.Screen.print("Setting Tool 2");
  // Brain.Screen.setCursor(5, 1);
  
  // Brain.Screen.print("Selected: Slot 4");
  // Brain.Screen.setCursor(2,1);
  // Brain.Screen.print("Check Air");
  // Brain.Screen.setCursor(3,1);
  // Brain.Screen.print("Five Ball Near Side");
  // Brain.Screen.setCursor(4,1);
  // Brain.Screen.print("Setting Tool 1");
  // Brain.Screen.setCursor(5,1);

  // Brain.Screen.print("Selected: Slot 5");
  // Brain.Screen.setCursor(2,1);
  // Brain.Screen.print("Check Air");
  // Brain.Screen.setCursor(3,1);
  // Brain.Screen.print("Five Ball Far Side");
  // Brain.Screen.setCursor(4,1);
  // Brain.Screen.print("Setting Tool 1");
  // Brain.Screen.setCursor(5,1);
  // Brain.Screen.print("REMAKE TOOL");
  // Brain.Screen.setCursor(6,1);
  // Brain.Screen.print("Triball On Left Wing");
  // Brain.Screen.setCursor(7,1);
  // Brain.Screen.print("NO TOUCH");

  Brain.Screen.print("Selected: Slot 6");
  Brain.Screen.setCursor(2,1);
  Brain.Screen.print("Check Air");
  Brain.Screen.setCursor(3,1);
  Brain.Screen.print("Five Ball Far Side");
  Brain.Screen.setCursor(4,1);
  Brain.Screen.print("Setting Tool 2");
  Brain.Screen.setCursor(5,1);


  // Brain.Screen.print("Selected: Slot 7");
  // Brain.Screen.setCursor(2,1);
  // Brain.Screen.print("Check Air");
  // Brain.Screen.setCursor(3,1);
  // Brain.Screen.print("Six Ball Far Side");
  // Brain.Screen.setCursor(4,1);
  // Brain.Screen.print("Setting Tool 2");
  // Brain.Screen.setCursor(5,1);


  // Brain.Screen.print("Selected: Slot 8");
  // Brain.Screen.setCursor(2,1);
  // Brain.Screen.print("Check Air");
  // Brain.Screen.setCursor(3,1);
  // Brain.Screen.print("Five Ball Far Side");
  // Brain.Screen.setCursor(4,1);
  // Brain.Screen.print("Setting Tool 1");
  // Brain.Screen.setCursor(5,1);

  // Auton selector with potentiometer
}


void testing(){
  Drive.move(10, 15);
}
void (*autonsList[])() =
{
  testing,
  fourMidNearset1,
  fourMidNearset2, 
  doNothing,
  fiveMidFarset2,
  fiveMidNear,
  fiveMidFarset1,
  sixMidFar,

};

void autonomous()
{
  autonsList[autoSelect]();
}

int conInfo()
{
  while (true)
  {
    con.Screen.clearScreen();
    con.Screen.setCursor(1, 1);
    con.Screen.print("Battery:");
    con.Screen.print(Brain.Battery.capacity(percent));
    con.Screen.setCursor(2, 1);
    con.Screen.print("Left  ");
    con.Screen.print((left1.temperature(fahrenheit) + left2.temperature(fahrenheit) + left3.temperature(fahrenheit)) / 3);
    con.Screen.setCursor(3, 1);
    con.Screen.print("Right  ");
    con.Screen.print((right1.temperature(fahrenheit) + right2.temperature(fahrenheit) + right3.temperature(fahrenheit)) / 3);
    wait(1, sec);
  }
  return (0);
}
void usercontrol()
{
  // r2 intake reverse hold,
  //  r1 intake fwd hold,
  //  l1 shoot toggle,
  //  l2 hang hold tap to fire piston then,
  // y right frontwing,
  //  b right backwing,
  //  right arrow front leftwing
  //  down arrow back leftwing
  task printcon = task(conInfo);
  while (true)
  {
    // driving portion
    // controls the speed at which the robot moves
    // moving controls
    rightdrive.spin(fwd, con.Axis2.value(), pct);
    leftdrive.spin(fwd, con.Axis3.value(), pct);
    // intake controls
    if (con.ButtonR2.pressing())
    {
      intake.spin(fwd, -100, pct);
    }
    else if (con.ButtonR1.pressing())
    {
      intake.spin(fwd, 100, pct);
    }
    else
    {
      intake.stop(hold);
    }
    // kicker controls

    if (con.ButtonL2.pressing())
    {
      if (f6loop)
      {
        f6loop = false;
        if (f7loop)
        {
          hang.open();
          con.rumble(".-..--.--..");
          f7loop = false;
        }
        else
        {
          kicker.spin(fwd, -100, pct);
          kicker2.spin(fwd, -100, pct);
        }
      }
    }
    else if (con.ButtonL1.pressing())
    {
      if (f5loop)
      {
        f5loop = false;
        punchythingToggle = !punchythingToggle;
      }
    }
    else
    {
      f5loop = true;
    }
    if (!con.ButtonL2.pressing())
    {
      f6loop = true;
    }
    if (punchythingToggle)
    {
      kicker.spin(fwd, 100, pct);
      kicker2.spin(fwd, 100, pct);
    }
    else if (!con.ButtonL2.pressing())
    {
      kicker.stop();
      kicker2.stop();
    }

    // leftwing control
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

    // rightwing control
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

    // right back wing control
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

#include "vex.h"
using namespace vex;


drivetrainObj::drivetrainObj(double wheelDiameterInput, double gearLPlusRatioInput)
{
    wheelDiameter = wheelDiameterInput;
    gearRatio = gearLPlusRatioInput;
}

double drivetrainObj::getLeftEncoderValue()
{
    return leftdrive.position(deg);
}

double drivetrainObj::getRightEncoderValue()
{
    return rightdrive.position(deg);
}

double drivetrainObj::getEncoderValue()
{
    return (getLeftEncoderValue() + getRightEncoderValue()) / 2.0;
}

void drivetrainObj::move(double targetDistance, double timeout)
{
  double distKp = .75;
  // establishes when we started the procedure
  // records a starting position of the bot
  double startPos = left1.position(deg);
  // records a starting position of the bot
  double startAng = Inertial.rotation(deg);
  int startTime = vex::timer::system();
  // limits the time the procedure can run
  double speed, turnErr;
  while (vex::timer::system() - startTime < timeout * 1000)
  {
    // limits the speed so as the robot gets closer to where you want it it slows down the speed and doesn't overshoot the distance
    speed = (targetDistance - (((left1.position(deg) - startPos) * (3.14159 / 180.0)) * 2.9))* distKp;
    // calculates the difference between our current angle and our initial angle
    turnErr = startAng - Inertial.rotation(deg);
    // set the drive to the correct speed
    rightdrive.spin(fwd, speed  - turnErr , pct);
    leftdrive.spin(fwd, speed + turnErr , pct);
    wait(20, msec);
  }
  leftdrive.stop();
  rightdrive.stop();
}

void drivetrainObj::swingGood(double targetDistance, double timeout, double turnMult, bool RightSide)
{
  double distKp = 3.9;
  // establishes when we started the procedure
  // records a starting position of the bot
  double startPos = (right1.position(deg) + left1.position(deg)) / 2.0;
  // records a starting position of the bot
  int startTime = vex::timer::system();
  // limits the time the procedure can run
  double speed;
  while (vex::timer::system() - startTime < timeout * 1000)
  {
    // limits the speed so as the robot gets closer to where you want it it slows down the speed and doesn't overshoot the distance
    speed = (targetDistance - ((right1.position(deg) + left1.position(deg)) / 2.0 - startPos) * 3.14159 / 180 * 2.9) * distKp;
    // set the drive to the correct speed
    if (RightSide) {
      rightdrive.spin(fwd, speed * turnMult, pct);
      leftdrive.spin(fwd, speed, pct);
    }
    else
    {
      rightdrive.spin(fwd, speed, pct); 
      leftdrive.spin(fwd, speed * turnMult, pct);
    }
    
    wait(10, msec);
  }
  leftdrive.stop();
  rightdrive.stop();
}


void drivetrainObj::turn(double targetAngle, double timeout)
{
  // establishes when the turn started
  double kP = .329;
  int startTime = vex::timer::system();
  double speed;
  // limits the time so that it doesn't waste time fixing marginal error
  while (vex::timer::system() - startTime < timeout * 1000)
  {
    speed = (targetAngle - Inertial.rotation(deg)) * kP;
    rightdrive.spin(fwd, -speed, pct);
    leftdrive.spin(fwd, speed, pct);
    wait(10, msec);
    // limits the speed so as the robot gets closer to where you want it it slows down the speed and doesn't overshoot the distance
  }
  // stops slowly opposed to abruptly
  leftdrive.stop();
  rightdrive.stop();
}


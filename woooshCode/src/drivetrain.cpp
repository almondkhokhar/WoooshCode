#include "vex.h"
using namespace vex;


drivetrainObj::drivetrainObj(double wheelDiameterInput, double gearLPlusRatioInput)
{
    wheelDiameter = wheelDiameterInput;
    gearRatio = gearLPlusRatioInput;
}

double drivetrainObj::getLeftEncoderValue()
{
    return left1.position(deg);
}

double drivetrainObj::getRightEncoderValue()
{
  right1.resetPosition();
    return rightdrive.position(deg);
}

double drivetrainObj::getEncoderValue()
{
    return (getLeftEncoderValue() + getRightEncoderValue()) / 2.0;
}

void drivetrainObj::move(double targetDistance, double timeout)
{
  left1.resetPosition();
  double distKp = 3.9;

  // establishes when we started the procedure
  // records a starting position of the bot
  // records a starting position of the bot
  double startAng = Inertial.rotation(deg);
  int startTime = vex::timer::system();
  // limits the time the procedure can run
  double speed1, turnErr;
  printf("%f\n",Drive.getLeftEncoderValue());
  while (vex::timer::system() - startTime < timeout * 1000)
  {
    // limits the speed so as the robot gets closer to where you want it it slows down the speed and doesn't overshoot the distance
    double inRem=targetDistance-Drive.getLeftEncoderValue()* 3.14159265359/180 *1.6;
    speed1= inRem*distKp;

    //printf("%f\n",speed1);
    printf("%f\n",inRem);
    //printf("%f\n",Drive.getLeftEncoderValue());
    // calculates the difference between our current angle and our initial angle
    turnErr = startAng - Inertial.rotation(deg);
    // set the drive to the correct speed
    rightdrive.spin(fwd, speed1 - turnErr*.0, pct);
    leftdrive.spin(fwd, speed1 + turnErr*.0, pct);
    wait(10, msec);
  }
  leftdrive.stop(brake);
  rightdrive.stop(brake);
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
  double speed2;
  while (vex::timer::system() - startTime < timeout * 1000)
  {
    // limits the speed so as the robot gets closer to where you want it it slows down the speed and doesn't overshoot the distance
    speed2 = (targetDistance - ((right1.position(deg) + left1.position(deg)) / 2.0 - startPos) * 3.14159 / 180 * 3.25) * distKp;
    // set the drive to the correct speed
    if (RightSide) {
      rightdrive.spin(fwd, speed2 * turnMult, pct);
      leftdrive.spin(fwd, speed2, pct);
    }
    else
    {
      rightdrive.spin(fwd, speed2, pct); 
      leftdrive.spin(fwd, speed2 * turnMult, pct);
    }
    
    wait(10, msec);
  }
  leftdrive.stop();
  rightdrive.stop();
}

void drivetrainObj::turn(double targetAngle, double timeout)
{
  // establishes when the turn started
  int startTime = vex::timer::system();
  double speed3;
  // limits the time so that it doesn't waste time fixing marginal error
  while (vex::timer::system() - startTime < timeout * 1000)
  {
    speed3 = (targetAngle - Inertial.rotation(deg)) * .329;
    rightdrive.spin(fwd, -speed3, pct);
    leftdrive.spin(fwd, speed3, pct);
    wait(10, msec);
    // limits the speed so as the robot gets closer to where you want it it slows down the speed and doesn't overshoot the distance
  }
  // stops slowly opposed to abruptly
  leftdrive.stop();
  rightdrive.stop();
}
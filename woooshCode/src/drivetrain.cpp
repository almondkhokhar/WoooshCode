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
  double distKp = 500.0;
  double turnKp = 350.0;
  double wheelDiameter = 2.75;
  // establishes when we started the procedure
  // records a starting position of the bot
  // records a starting position of the bot
  double startAng = Inertial.rotation(deg);
  double startPos = Drive.getEncoderValue();
  int startTime = vex::timer::system();

  // limits the time the procedure can run
  while (vex::timer::system() - startTime < timeout * 1000)
  {
    // limits the speed so as the robot gets closer to where you want it it slows down the speed and doesn't overshoot the distance
    double currentDistance = (Drive.getEncoderValue() - startPos) * M_PI / 180 * wheelDiameter / 2;
    double error = targetDistance - currentDistance;

    // calculates the difference between our current angle and our initial angle
    double turnErr = startAng - Inertial.rotation(deg);

    double speed = error * distKp;
    double turnSpeed = turnErr * turnKp;

    // set the drive to the correct speed
    rightdrive.spin(fwd, speed - turnSpeed, vex::voltageUnits::mV);
    leftdrive.spin(fwd, speed + turnSpeed, vex::voltageUnits::mV);
    printf("%f\n", turnErr);

    wait(20, msec);
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
    speed2 = (Drive.getEncoderValue() - startPos) * M_PI / 180 * wheelDiameter / 2 * distKp;
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
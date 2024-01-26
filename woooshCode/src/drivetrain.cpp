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

void drivetrainObj::turn(double targetAngle, double timeout)
{
  double kp = 0.5;
  double kd = 10;
  // establishes when the turn started
  int startTime = vex::timer::system();

  double error, prevError, deriv, output;
  prevError = (targetAngle - Inertial.rotation(deg));
  // limits the time so that it doesn't waste time fixing marginal error
  while (vex::timer::system() - startTime < timeout * 1000)
  {
    // limits the speed so as the robot gets closer to where you want it it slows down the speed and doesn't overshoot the distance
    error = (targetAngle - Inertial.rotation(deg));
    deriv = prevError - error;

    output =  error * kp - deriv * kd;

    prevError = error;

    rightdrive.spin(fwd, -output, pct);
    leftdrive.spin(fwd, output, pct);
    wait(20, msec);
  }
  // stops slowly opposed to abruptly
  leftdrive.stop();
  rightdrive.stop();
}


void drivetrainObj::swing(double targetAngle, double targetDistance, double timeout, bool rightTurn)
{
  // variables
  double  turnKp = .8;
  double  turnKd = 0;
  double  distKp = 1.2;

  double  leftStartPos = left1.position(deg);
  double  rightStartPos = right1.position(deg);
  double  startAngle = Inertial.rotation(deg);
  int     startTime = vex::timer::system();

  double  speed, turnDeriv, turnSpeed, distanceTraveled, fractionOfDriveCompleted, currentTargetAngle, turnErr;
  double  prevTurnError = 0;
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
    currentTargetAngle = startAngle + fractionOfDriveCompleted * targetAngle * 1.2;
    // find the error of the robots angle
    turnErr = (currentTargetAngle - Inertial.rotation(deg));

    turnDeriv = prevTurnError - turnErr;

    prevTurnError = turnErr;

    turnSpeed = turnErr * turnKp - turnDeriv * turnKd;


    rightdrive.spin(fwd, speed - turnErr, pct);
    leftdrive.spin(fwd, speed + turnErr, pct);
    wait(20, msec);
  }
  leftdrive.stop();
  rightdrive.stop();
}

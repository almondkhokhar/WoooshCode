#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H
#include "vex.h"
using namespace vex;

class drivetrainObj
{
    public:
        drivetrainObj(double wheelDiameterInput, double gearLPlusRatioInput);
        double getLeftEncoderValue();
        double getRightEncoderValue();
        double getEncoderValue();
        void move(double targetDistance, double timeout);
        void turn(double targetAngle, double timeout);
        void swing(double targetDistance, double timeout, double turnMult, double distKp, bool RightSide);
    private:
        double wheelDiameter;
        double gearRatio;        
};

#endif
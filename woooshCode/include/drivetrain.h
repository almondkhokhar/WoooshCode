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
        // functions to allow us to know where the robot is whilst performing a void action
        void move(double targetDistance, double timeout);
        //drive in a straight line
        void turn(double targetAngle, double timeout);
        // turning in place
        void swing(double targetDistance, double timeout, double turnMult, double distKp, bool RightSide);
        //driving while turning
    private:
        double wheelDiameter;
        double gearRatio;    
    //allows changes to the robot to occur without spending extensive time adjusting in the program    
};
//declares a class to allow different functions to affect the drivetrain and cause different movements
#endif
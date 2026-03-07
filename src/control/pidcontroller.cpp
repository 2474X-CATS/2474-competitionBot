#include "math.h"
#include <cstdlib>
#include "pidcontroller.h"

pidcontroller::pidcontroller(PIDConstants conts, double destination) : kP(conts.P),
                                                                       kI(conts.I),
                                                                       kD(conts.D),
                                                                       errorTolerance(conts.errorTolerance),
                                                                       iLimit(conts.iLimit)
{
   setpoint = destination;
};

pidcontroller::pidcontroller() : kP(0),
                                 kI(0),
                                 kD(0),
                                 errorTolerance(0),
                                 iLimit(0)
{
   setpoint = 0;
};

bool pidcontroller::atSetpoint(double position)
{
   return fabs(setpoint - position) <= errorTolerance;
};

double pidcontroller::calculate(double position, double timestamp)
{
   double dt = (timestamp - lastTimestamp) / 1000;
   lastTimestamp = timestamp;
   double error = setpoint - position;
   if (atSetpoint(position))
      return 0;
   integral += error * dt;
   if (iLimit > 0)
   {
      if (integral > iLimit)
         integral = iLimit;
      else if (integral < -iLimit)
         integral = -iLimit;
   }
   derivative = (error - prevError) / dt;
   prevError = error;
   return (kP * error) + (kI * integral) + (kD * derivative);
};

void pidcontroller::setLastTimestamp(double timestamp)
{
   lastTimestamp = timestamp;
}; 

double pidcontroller::getDerivative(){ 
   return derivative;
}

double pidcontroller::getSetpoint()
{
   return setpoint;
}

double pidcontroller::setSetpoint(double setpoint){ 
   this->setpoint = setpoint; 
   reset();
}

void pidcontroller::reset()
{
   integral = 0;
   derivative = 0;
   prevError = 0;
}
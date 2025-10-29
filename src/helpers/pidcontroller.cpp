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



bool pidcontroller::atSetpoint()
{
   return fabs(error) <= errorTolerance;
};

double pidcontroller::calculate(double position, double timestamp)
{
   double dt = timestamp - lastTimestamp;
   if (dt <= 0)
      dt = 1e-6;
   lastTimestamp = timestamp;
   error = setpoint - position; 
   if (atSetpoint()) 
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

double pidcontroller::getSetpoint(){ 
   return setpoint;
}
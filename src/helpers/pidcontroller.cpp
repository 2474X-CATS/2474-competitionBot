#include "math.h" 
#include <cstdlib>  
#include "pidcontroller.h"


pidcontroller::pidcontroller(PIDConstants conts, double destination) :  
kP(conts.P),  
kI(conts.I),  
kD(conts.D), 
errorTolerance(conts.errorTolerance), 
iLimit(conts.iLimit){  
    setpoint = destination;
    prevError = destination; 
    error = destination;
}; 

bool pidcontroller::atSetpoint(){ 
   return fabs(error) <= errorTolerance;
}; 

double pidcontroller::calculate(double position){ 
   error = setpoint - position; 
   integral += error; 
   if ((fabs(error) <= errorTolerance) || (iLimit != -1 && integral > iLimit)){ 
         integral = 0;
   }    
   derivative = error - prevError; 
   prevError = error;  
   return (kP * error) + (kI * integral) + (kD * derivative);
};
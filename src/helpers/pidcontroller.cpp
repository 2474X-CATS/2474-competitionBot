
#include "math.h" 
#include <cstdlib> 

typedef struct { 
    double P; 
    double I; 
    double D;  
    double iLimit = -1; 
    double errorTolerance = 0;
} PIDConstants;

class pidcontroller {  
   private:  

     double kP; 
     double kI; 
     double kD;  
     
     double error; 
     double integral = 0; 
     double derivative; 

     double errorTolerance;  
     double iLimit;

     double prevError;  

     double setpoint; 

   public: 
     pidcontroller(double p, double i, double d, double destination, double errorTolerance = 0, double iLimit = -1) : 
     kP(p), 
     kI(i), 
     kD(d), 
     errorTolerance(errorTolerance), 
     iLimit(iLimit),  
     setpoint(destination)
     { 
        prevError = destination; 
        error = destination;
     } 

     double calculate(double position){ 
        error = setpoint - position; 
        integral += error; 
        if ((fabs(error) <= errorTolerance) || (iLimit != -1 && integral > iLimit)){ 
            integral = 0;
        }    
        derivative = error - prevError; 
        prevError = error;  
        return (kP * error) + (kI * integral) + (kD * derivative);
     } 

     bool atSetpoint(){ 
        return fabs(error) <= errorTolerance;
     }
};
#ifndef __PID_H__ 
#define __PID_H__ 
/* 
Uses Proportional Integral Derviative control to insure motion smoothness,  
and setpoint precision (given some tuning)
*/
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
     pidcontroller(PIDConstants conts, double destination);

     double calculate(double position);

     bool atSetpoint();
};


#endif
#ifndef __CATAPULT_H__ 
#define __CATAPULT_H__ 

#include "../architecture/subsystem.h" 
#include "vex.h" 
#include "../control/pidcontroller.h"

class Catapult : public Subsystem {  

   private:   
     vex::pneumatics stateSwitcher;   
     vex::pneumatics leverLid;  

     vex::motor leverActuator;   

     PIDConstants motionConsts; 
     pidcontroller* controller = nullptr;
     
     array<vex::distance, 6> spotArray; 

     static double MAXIMUM_LEVER_ANGLE_DEG; 
     static double STARTING_ANGLE_DEG;
     static double DISTANCE_THRESHOLD_CM;
     static double LAUNCH_DELAY_MS; 
     
     double calculateLaunchAngle();  

     void rotate(); 

     double calculateAngularError();

   public:  
     using Subsystem::get;  
     
     static Catapult* globalRef; 

     Catapult();

     void init() override;
     void periodic() override;
     void updateTelemetry() override;
     void stop() override;

   protected:  
     using Subsystem::set; 

}; 


#endif 
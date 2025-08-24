#ifndef __DRIVEBASE_H_ 
#define __DRIVEBASE_H_   

#include "../architecture/subsystem.h" 
#include "../architecture/command.h" 
#include "../helpers/pidcontroller.h"



class Drivebase : public Subsystem {     
    private: 
       PIDConstants powerPID; 
       PIDConstants turnPID;    
    public:     
       Drivebase();
    
       void init() override; 
       void periodic() override; 
       void updateTelemetry() override;    

       void arcadeDrive(double speed, double rotation);    
       void manualDriveForward(double speedMM); 
       void manualTurnClockwise(double turnDeg);  

       void stop(); 

       PIDConstants getTurningPID(); 

       PIDConstants getPowerPID();
    
}; 

class DriveLinear : public Command<Drivebase> {  
    
   private:  
     Drivebase& driveRef; 
     pidcontroller* control = nullptr; 

    double startingPoint[2];
    double getDistTraveled();
    
     
    public:  
     DriveLinear(Drivebase& drive, double displacement);  
     ~DriveLinear();
     
     void start() override; 
     void periodic() override; 
     bool isOver() override; 
     void end() override;

}; 

class TurnTo : public Command<Drivebase> {  
    
   private:     
     Drivebase& driveRef; 
     pidcontroller* control = nullptr;  

     double setpoint;
     double getError();

    public:  

     TurnTo(Drivebase& drive, double degrees);  
     ~TurnTo();
     void start() override; 
     void periodic() override; 
     bool isOver() override; 
     void end() override; 

};

#endif
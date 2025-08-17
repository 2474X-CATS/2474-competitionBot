#ifndef __DRIVEBASE_H_ 
#define __DRIVEBASE_H_   

#include "../architecture/subsystem.h" 
#include "../architecture/command.h"

class Drivebase : public Subsystem {     
    public:    
       Drivebase() : Subsystem( 
        "drivebase",
         { 
            (EntrySet){"Pos_X", EntryType::DOUBLE}, 
            (EntrySet){"Pos_Y",EntryType::DOUBLE}, 
            (EntrySet){"Angle_Degrees",EntryType::DOUBLE}
         }
       ){};
    
       void init() override; 
       void periodic() override; 
       void updateTelemetry() override;   
       void arcadeDrive(double speed, double rotation);  
       void stop();
    
}; 

class DriveForward : public Command<Drivebase> {  
    private:  

     double setpoint;  
     double startingPoint[2];

    public:  

     DriveForward(Drivebase* drive, double feetForward);  

     void start() override; 
     void periodic() override; 
     bool isOver() override; 
     void end() override;

};
















































#endif
#ifndef __DRIVEBASE_H_ 
#define __DRIVEBASE_H_   

#include "../architecture/subsystem.h" 
#include "../architecture/command.h" 
#include "../helpers/pidcontroller.cpp"

class Drivebase : public Subsystem {     
    private: 
       PIDConstants powerPID; 
       PIDConstants turnPID;  
    public:     
       Drivebase() :  
       Subsystem( 
        "drivebase",
         { 
            (EntrySet){"Pos_X", EntryType::DOUBLE}, 
            (EntrySet){"Pos_Y",EntryType::DOUBLE}, 
            (EntrySet){"Angle_Degrees",EntryType::DOUBLE}
         }
       ){  
         /* 
           TO-DO: Tune and set PID Values
         */
         powerPID.P = 0; 
         powerPID.I = 0; 
         powerPID.D = 0;  
         //------------------------------
         turnPID.P = 0; 
         turnPID.I = 0; 
         turnPID.D = 0; 
         
       };
    
       void init() override; 
       void periodic() override; 
       void updateTelemetry() override;    

       void arcadeDrive(double speed, double rotation);    
       void manualDriveForward(double speedMM); 
       void manualTurnClockwise(double turnDeg); 

       void stop(); 

       pidcontroller getTurningController(double setpoint); 

       pidcontroller getPowerController(double setpoint);
    
}; 

class DriveForward : public Command<Drivebase> {  
    
   private:   
     double startingPoint[2];    
   
     double getDistTraveled();

    public:  
     pidcontroller control;
     DriveForward(Drivebase* drive, double distForward);  

     void start() override; 
     void periodic() override; 
     bool isOver() override; 
     void end() override;

}; 

class TurnTo : public Command<Drivebase> {  
    
   private:   
     double startingPoint[2];    
     pidcontroller control; 

     double getDistTraveled();

    public:  

     TurnTo(Drivebase* drive, double degrees);  

     void start() override; 
     void periodic() override; 
     bool isOver() override; 
     void end() override;

};
















































#endif
#ifndef __COMMANDS_H__ 
#define __COMMANDS_H__ 

#include "subsystems/drivebase.h"  
#include "subsystems/intake.h"  
#include "subsystems/hood.h"  
#include "subsystems/matchloader.h"  
#include "subsystems/indexer.h" 
#include "subsystems/hopper.h"  

#include "architecture/command.h"  

class DriveLinear : public Command<Drivebase> { 
     private:
       Drivebase &driveRef;
       pidcontroller *control = nullptr; 

       double startingPoint[2];
       double getDistTraveled(); 

     public: 

       DriveLinear(Drivebase &drive, double displacement) :    
       Command<Drivebase>(drive),
       driveRef(drive),
       control(new pidcontroller(drive.getPowerPID(), displacement)) {}; 

       ~DriveLinear() override;

       static CommandInterface *getCommand(Drivebase &drive, double displacement)
       {
         return new DriveLinear(drive, displacement);
       }  

     protected:
       void start() override;
       void periodic() override;
       bool isOver() override;
       void end() override; 
}; 

class TurnToHeading : public Command<Drivebase> { 
    private:
     Drivebase &driveRef;
     pidcontroller *control = nullptr; 

     double startingAngle;
     bool isClockwise;
     double angularDifference;  
     
     double setpoint;

     double getDistToSpin();

    public: 

     TurnToHeading(Drivebase &drive, double degrees) : 
     Command<Drivebase>(drive), 
     driveRef(drive), 
     control(new pidcontroller(drive.getTurningPID(), 0)), 
     setpoint(degrees){}; 

     ~TurnToHeading() override;

     static CommandInterface *getCommand(Drivebase &drive, double degrees)
     {
      return new TurnToHeading(drive, degrees);
     } 

    protected:
     void start() override;
     void periodic() override;
     bool isOver() override;
     void end() override;
};

class IntakeToHopper : public Command<Intake, Indexer, Hood> { 
    private:   

      Intake& intakeRef;  
      Indexer& indexerRef;  
      Hood& hoodRef; 
      
      double startingTime;
      double timeDuration; 

    protected: 
      void start() override;
      void periodic() override;
      bool isOver() override;
      void end() override; 
    
    public: 
      static CommandInterface *getCommand(Intake& intake, Indexer& indexer, Hood& hood, double timeDuration)
      {
         return new IntakeToHopper(intake, indexer, hood, timeDuration);
      }  

      IntakeToHopper(Intake& intake, Indexer& indexer, Hood& hood, double timeDuration) : 
      Command<Intake, Indexer, Hood>(intake, indexer, hood), 
      intakeRef(intake), 
      indexerRef(indexer), 
      hoodRef(hood), 
      timeDuration(timeDuration){};  

      ~IntakeToHopper();

};

class ScoreOnGoal : public Command<Intake, Indexer, Hood, Hopper> { 
    private:   

      Intake& intakeRef;  
      Indexer& indexerRef;  
      Hood& hoodRef;  
      Hopper& hopperRef;
      
      double startingTime;
      double timeDuration;   
      int goal;
    
    public: 
      static CommandInterface *getCommand(Intake& intake, Indexer& indexer, Hood& hood, Hopper& hopper, int goal, double timeDuration)
      {
         return new ScoreOnGoal(intake, indexer, hood, hopper, goal, timeDuration);
      };

      ScoreOnGoal(Intake& intake, Indexer& indexer, Hood& hood, Hopper& hopper, int goal, double timeDuration) : 
      Command<Intake, Indexer, Hood, Hopper>(intake, indexer, hood, hopper), 
      intakeRef(intake), 
      indexerRef(indexer),  
      hoodRef(hood), 
      hopperRef(hopper),  
      timeDuration(timeDuration), 
      goal(goal){};  

      ~ScoreOnGoal();

    protected: 
      void start() override;
      void periodic() override;
      bool isOver() override;
      void end() override; 

}; 


class DeployMatchloader : Command<Matchloader> { 
    private:  
      Matchloader& matchLoaderRef;
      bool isOut;
    protected: 
      void start() override;
      void periodic() override;
      bool isOver() override;
      void end() override; 
    
    public: 
      static CommandInterface *getCommand(Matchloader& matchloader, bool out)
      {
         return new DeployMatchloader(matchloader, out);
      }  

      DeployMatchloader(Matchloader& matchloader, bool out) :  
      Command<Matchloader>(matchloader), 
      matchLoaderRef(matchloader), 
      isOut(out){};  

      ~DeployMatchloader();
};

#endif 
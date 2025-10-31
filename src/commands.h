#ifndef __COMMANDS_H__ 
#define __COMMANDS_H__ 

#include "subsystems/drivebase.h"  
#include "subsystems/intake.h"  
#include "subsystems/hood.h"  
#include "subsystems/matchloader.h"  
#include "subsystems/indexer.h" 
#include "subsystems/hopper.h"  
#include "architecture/command.h"  


typedef enum { 
   HIGH_GOAL = 1, 
   MID_GOAL = 2, 
   LOW_GOAL = 3
} Goal_Pos; 

class DriveForwardBy : public Command<Drivebase> {   
    private:   

      Drivebase &driveRef;  
      pidcontroller* control = nullptr; 

      bool goingForward; 
      double startingPoint[2]; 

      double getDistTraveled(); 

    public:
      static CommandInterface *getCommand(double displacement, bool goingForward)
      {
         return new DriveForwardBy(*Drivebase::globalRef, displacement, goingForward);
      }     

      DriveForwardBy(Drivebase &drive, double displacement, bool goingForward) : 
      Command<Drivebase>(drive), 
      driveRef(drive),   
      control(new pidcontroller(drive.getPowerPID(), displacement)),
      goingForward(goingForward){};  

      ~DriveForwardBy() override = default;

    protected:   
      void start() override; 
      void periodic() override;  
      bool isOver() override; 
      void end() override;
      
};  

class DriveForwardWhileIntaking : public Command<Drivebase, Intake, Indexer, Hood> {   
    private:   

      Drivebase &driveRef;  
      Intake &intakeRef; 
      Hood &hoodRef;  
      Indexer& indexerRef;

      pidcontroller* control = nullptr; 

      bool goingForward; 
      double startingPoint[2]; 

      double getDistTraveled(); 

    public:
      static CommandInterface *getCommand(double displacement, bool goingForward)
      {
         return new DriveForwardWhileIntaking(*Drivebase::globalRef, *Intake::globalRef, *Indexer::globalRef, *Hood::globalRef,  displacement, goingForward);
      }     

      DriveForwardWhileIntaking(Drivebase &drive, Intake& intake, Indexer& indexer, Hood& hood, double displacement, bool goingForward) : 
      Command<Drivebase, Intake, Indexer, Hood>(drive, intake, indexer, hood), 
      driveRef(drive),    
      intakeRef(intake),  
      hoodRef(hood), 
      indexerRef(indexer),
      control(new pidcontroller(drive.getPowerPID(), displacement)),
      goingForward(goingForward){};  

      ~DriveForwardWhileIntaking() override = default;

    protected:   
      void start() override; 
      void periodic() override;  
      bool isOver() override; 
      void end() override;
      
};  

class DriveForwardForTime : Command<Drivebase> { 
    private:  
      Drivebase& drivebaseRef;
      double percentage;   

      double startingTime; 

      double timeDuration; 
    protected: 
      void start() override;
      void periodic() override;
      bool isOver() override;
      void end() override; 
    
    public: 
      static CommandInterface *getCommand(double percentage, double timeDuration)
      {
         return new DriveForwardForTime(*Drivebase::globalRef, percentage, timeDuration);
      }  

      DriveForwardForTime(Drivebase& drivebase, double percentage, double timeDuration) :  
      Command<Drivebase>(drivebase), 
      drivebaseRef(drivebase),
      percentage(percentage), 
      timeDuration(timeDuration){};   

      ~DriveForwardForTime() override = default;

}; 


class TurnToHeading : public Command<Drivebase> { 
    private:  
      Drivebase &driveRef; 
      pidcontroller* control = nullptr; 

      bool isClockwise; 
      double getAngluarDifference(); 

      double angleSetpoint;

    public:
      static CommandInterface *getCommand(double heading)
      {
         return new TurnToHeading(*Drivebase::globalRef, heading);
      }     

      TurnToHeading(Drivebase &drive, double degreeHeading) : 
      Command<Drivebase>(drive), 
      driveRef(drive), 
      control(new pidcontroller(drive.getTurningPID(), 0)),
      angleSetpoint(degreeHeading){};  

      ~TurnToHeading() override = default;

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
      static CommandInterface *getCommand(double timeDuration)
      {
         return new IntakeToHopper(*Intake::globalRef, *Indexer::globalRef, *Hood::globalRef, timeDuration);
      }  

      IntakeToHopper(Intake& intake, Indexer& indexer, Hood& hood, double timeDuration) : 
      Command<Intake, Indexer, Hood>(intake, indexer, hood), 
      intakeRef(intake), 
      indexerRef(indexer), 
      hoodRef(hood), 
      timeDuration(timeDuration){};   

      ~IntakeToHopper() override = default;

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
      static CommandInterface *getCommand(int goal, double timeDuration)
      {
         return new ScoreOnGoal(*Intake::globalRef, *Indexer::globalRef, *Hood::globalRef, *Hopper::globalRef, goal, timeDuration);
      };

      ScoreOnGoal(Intake& intake, Indexer& indexer, Hood& hood, Hopper& hopper, int goal, double timeDuration) : 
      Command<Intake, Indexer, Hood, Hopper>(intake, indexer, hood, hopper), 
      intakeRef(intake), 
      indexerRef(indexer),  
      hoodRef(hood), 
      hopperRef(hopper),  
      timeDuration(timeDuration), 
      goal(goal){};   

      ~ScoreOnGoal() override = default; 

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
      static CommandInterface *getCommand(bool out)
      {
         return new DeployMatchloader(*Matchloader::globalRef, out);
      }  

      DeployMatchloader(Matchloader& matchloader, bool out) :  
      Command<Matchloader>(matchloader), 
      matchLoaderRef(matchloader), 
      isOut(out){};   

      ~DeployMatchloader() override = default;

}; 

class WaitFor : Command<DummySystem> {  
     private:   

       double timeDuration;
       double startTime; 

     public: 
      static CommandInterface *getCommand(double timeDuration)
      {
         return new WaitFor(timeDuration);
      }  

      WaitFor(double timeDuration) :  
      Command<DummySystem>(GLOBAL_DUMMY), 
      timeDuration(timeDuration){};   

      ~WaitFor() override = default; 

     protected:
      void start() override;
      void periodic() override;
      bool isOver() override;
      void end() override; 

};

CommandInterface* driveForwardByTiles(double tiles); 
CommandInterface* turnToAngle(double goalHeading);
CommandInterface* scoreOnGoal(Goal_Pos position, double timeDuration);
CommandInterface* intakeCubes(double timeDuration);
CommandInterface* holdFor(double timeDuration);
CommandInterface* extend(); 
CommandInterface* retract(); 
CommandInterface* driveAndIntakeForTiles(double tiles);  
CommandInterface* ramForwardFor(double percentage, double timeDuration);




#endif 
#ifndef __COMMAND_H__
#define __COMMAND_H__

#include "subsystem.h"
#include <vector>
#include <stdexcept>
#include <vex.h>
#include <cstdlib>
#include <atomic> 
#include <functional>

/* 
Makes a task that can be stacked on other tasks to run in the autonomous period 

Ex: 
"I want a command that can drive the robot forward a certain amount of feet, and intakes at the very end" 

class Driveforward_then_Intake : public Command<Drivebase, Intake> {   

 |->  double distForward; 
 |->  double intakeTimeout;  
 |->  Drivebase& drive;  |
 |->  Intake& intake;   _| (Recommend storing references to required subsystems directly)
 |
 |  Driveforward_then_Intake(Drivebase& drive, Intake& intake, double dist, double timeoutIntake) :  
 |   Command<Drivebase, Intake>(drive, intake),  //Extends the Command constructor NECCESARY
 ---<distForward(dist), 
 ---<intakeTimeout(timeoutIntake), 
 ---<drive(drive), 
 ---<intake(intake) [This is a fancy way of setting values at contruction]
     {} 
    
    start() override { 
      // Preparing to do the task 
    }  

    periodic() override { 
      // If not reached "distForward" drive.driveForward() otherwise intake.intakeThings()
    } Happens every loop around 

    bool isOver() override { 
      // Return true if [I have reached my destination and have intake at least for as long as intakeTimeout]
    } // Tells you if the command is finished running 
    
    end() override { 
      //Release resources and stuff like that
    } // What to do at the end
} 

Now if you had another Command called Turn which takes in a drivebase and turns to a certain heading,  
and Intake which spins the intake inwards for a certain amount of time you could make a command group... 
{ 
 {Driveforward_then_Intake(drive, intake, 50, 2)}, 
 {Turn(drive, 90)}, 
 {Turn(drive, 180), Intake(intake, 10)}
} 

  This drives forward 50 units and intakes for 2 seconds 
                        THEN 
                  Turns 90 degrees  
                        THEN 
                /Turns to 180 degrees  
                        WHILE 
            Intaking inwards for 10 seconds/
  

*/

class CommandInterface
{ // Interface made for autonomous commands that use various types of subsystems 
  public: 
    //CommandInterface(){}; 
    ~CommandInterface(){};
  protected: 
     virtual void run() = 0;
     virtual void occupySubsystem() = 0;
     virtual bool isSubsystemOccupied() = 0;
  public:
     static void runCommandGroup(std::vector<std::vector<CommandInterface*>> systems);

     static std::atomic<int> completedTasks; 

 };

template <typename...Subsystems>
class Command : protected CommandInterface
{   

  static_assert((is_base_of<Subsystem, Subsystems>::value && ...) , "Command must wrap around a Subsystem type");

public:
  Command(Subsystems&...systems) : subsystems_{std::ref(static_cast<Subsystem&>(systems))...}{};

  void run() override
  {
    this->start();
    while (!isOver()){
      this->periodic(); 
      vex::this_thread::sleep_for(20);
    } 
    this->end(); 
    for (Subsystem& sub : subsystems_){ 
        sub.inCommand = false;
    }
  };

  void occupySubsystem() override
  {
    for (Subsystem& sub : subsystems_){ 
          sub.inCommand = true;
       }
  };

  bool isSubsystemOccupied() override {
    for (Subsystem& sub : subsystems_){ 
          if (sub.inCommand){
             return false; 
          }
    }  
    return true;
  };

protected: 
  std::vector<std::reference_wrapper<Subsystem>> subsystems_; 

  virtual void start() {};
  virtual void periodic() = 0;
  virtual bool isOver() { return true; };
  virtual void end() = 0;

  virtual ~Command() = default;
};

#endif
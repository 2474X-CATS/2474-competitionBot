#ifndef __COMMAND_H__
#define __COMMAND_H__

#include "subsystem.h"
#include <vector>
#include <stdexcept>
#include <vex.h>
#include <cstdlib>
#include <atomic> 
#include <functional>


class CommandInterface
{ // Interface made for autonomous commands that use various types of subsystems 
  public: 
    CommandInterface(){};
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
  Command(Subsystems&...systems) : subsystems_{std::ref(static_cast<Subsystem&>(systems))...}, CommandInterface(){};

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
#ifndef __COMMAND_H__
#define __COMMAND_H__  

#include "./subsystem.h"  
#include <vector> 
#include <stdexcept> 
#include <iostream> 
#include <cstdlib>   
#include <atomic> 


struct ICommand { 
  virtual void run() = 0; 
  virtual ~ICommand() = default; 
  
  virtual void occupySubsystem() = 0; 
  virtual bool isSubsystemOccupied() = 0; 
  
  static void runCommandGroup(std::vector<std::vector<ICommand*>> systems); 
  
  static std::atomic<int> completedTasks;

};

template <class T>
class Command : public ICommand{  
  static_assert(std::is_base_of_v<Subsystem, T>,"Command<T> must have T derive from Subsystem");
  public:   
     Command(T* sys) : sub(sys){}
     T* sub;  

     void run() override;  
     void occupySubsystem() override; 
     bool isSubsystemOccupied() override;   
    

  protected:  
     
     virtual void start(){}; 
     virtual void periodic() = 0; 
     virtual bool isOver(){return true;}; 
     virtual void end() = 0; 

     virtual ~Command() = default;
};  

//--------------------------------------------------------------------------------- 

template <class T> 
void Command<T>::run(){  
   this->start(); 
   do { 
      this->periodic();  
      this_thread::sleep_for(20);
   } while (!this->isOver()); 
   this->end(); 
   this->sub->inCommand = false;
}; 

template <class T> 
void Command<T>::occupySubsystem(){ 
  this->sub->runningCommands = true; 
} 

template <class T> 
bool Command<T>::isSubsystemOccupied(){ 
  return this->sub->inCommand;
} 


#endif
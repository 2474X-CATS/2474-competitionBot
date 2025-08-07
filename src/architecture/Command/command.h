#ifndef __COMMAND_H__
#define __COMMAND_H__  

#include "./architecture/Subsystem/subsytem.h"  
#include <vector> 
#include <stdexcept> 
#include <iostream> 
#include <cstdlib>  
#include <thread>


struct ICommand { 
  virtual void run() = 0; 
  virtual ~ICommand() = default; 
  
  virtual void signalSubsystem() = 0; 
  virtual bool isSubsystemFull() = 0; 
  virtual void resetSubsystemCom() = 0;
  
  static void runCommandGroup(std::vector<std::vector<ICommand*>> systems); 

};

template <class T>
class Command : public ICommand{  
  static_assert(std::is_base_of_v<Subsystem, T>,"Command<T> must have T derive from Subsystem");
  public:   
     Command(T* sys) : sub(sys){}
     T* sub;  

     void run() override;  
     void signalSubsystem() override; 
     bool isSubsystemFull() override;   
     void resetSubsystemCom() override; 

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
   this->sub->runningCommands += 1;
   this->start(); 
   do { 
      this->periodic();  
      std::cout<<"Waiting"<<std::endl<<std::endl;
   } while (!this->isOver()); 
   this->end(); 
   this->sub->runningCommands = 0;
}; 

template <class T> 
void Command<T>::signalSubsystem(){ 
  this->sub->runningCommands += 1; 
} 

template <class T> 
bool Command<T>::isSubsystemFull(){ 
  return this->sub->runningCommands > 1;
} 

template <class T> 
void Command<T>::resetSubsystemCom(){ 
  this->sub->runningCommands = 0;
} 

#endif
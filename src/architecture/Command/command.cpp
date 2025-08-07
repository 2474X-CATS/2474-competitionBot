#include "./command.h" 
//#include "./threadpool.h" 
#include <functional>    
#include "taskUtils.hpp" 
#include "vex.h" 
using namespace vex;
  

std::atomic<int> ICommand::completedTasks = {0}; 

void incrementCompletedTasks(){ 
    ICommand::completedTasks ++;
}  

event commandCompletion(incrementCompletedTasks);

void ICommand::runCommandGroup(std::vector<std::vector<ICommand*>> systems) {   
    for (std::vector<ICommand*> group : systems) {
        if (group.size() == 1) {
            group[0]->run();
        } else {   
            int numTasks = group.size(); 
            completedTasks = 0;   
            auto barrier = new Barrier(numTasks);
            for (ICommand* cmd : group) { 
                cmd->signalSubsystem();
                if (cmd->isSubsystemFull()){ 
                  throw std::invalid_argument("Subsystem pointer must not already be use by a Command");   
                  std::exit(1);  
                }  
                make_task(([cmd, barrier](){   
                    barrier->wait();
                    cmd->run(); 
                    cmd->resetSubsystemCom();  
                    commandCompletion.broadcast();
                    return 0;
                }));
            }  
            while (numTasks != completedTasks.load()){ 
                this_thread::yield();
            }  
            delete barrier;
            
        } 
        
    } 
}; 



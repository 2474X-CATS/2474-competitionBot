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
    //Threadpool pool(maximum_threads);    
    for (std::vector<ICommand*> group : systems) {
        if (group.size() == 1) {
            group[0]->run();
        } else {   
            int numTasks = group.size();   
            Barrier barrier(numTasks);
            for (ICommand* cmd : group) { 
                cmd->signalSubsystem();
                if (cmd->isSubsystemFull()){ 
                  throw std::invalid_argument("Subsystem pointer must not already be use by a Command");   
                  std::exit(1);  
                }  
                make_task([cmd, barrier_ptr = &barrier](){   
                    barrier_ptr->wait();
                    cmd->run(); 
                    cmd->resetSubsystemCom();  
                    commandCompletion.broadcast();
                    return 0;
                });
            }  
            while (numTasks != completedTasks){ 
                this_thread::yield();
            }
        } 
        completedTasks = 0;
    } 
}; 



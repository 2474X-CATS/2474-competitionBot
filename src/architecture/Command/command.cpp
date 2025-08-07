#include "./command.h" 

void ICommand::runCommandGroup(std::vector<std::vector<ICommand*>> systems) {
    for (std::vector<ICommand*> group : systems) {
        if (group.size() == 1) {
            group[0]->run();
        } else {   
            std::vector<std::thread> threads;
            for (ICommand* cmd : group) { 
                cmd->signalSubsystem();
                if (cmd->isSubsystemFull()){ 
                  throw std::invalid_argument("Subsystem pointer must not already be use by a Command");   
                  std::exit(1);  
                } 
                threads.emplace_back([cmd] { 
                    cmd->run(); 
                    cmd->resetSubsystemCom();
                });
            } 
            for (auto& thr : threads){ 
               if (thr.joinable()) 
                    thr.join();
            }
        }
    }
}; 

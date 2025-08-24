#include "command.h"
#include <functional>
#include "taskUtils.hpp"



std::atomic<int> CommandInterface::completedTasks = {0};

void incrementCompletedTasks()
{
    CommandInterface::completedTasks++;
}

vex::event commandCompletion(incrementCompletedTasks);

void CommandInterface::runCommandGroup(std::vector<std::vector<CommandInterface*>> systems)
{
    for (std::vector<CommandInterface *> group : systems)
    {
        if (group.size() == 1)
        {
            group[0]->run();   
            delete group[0];
        }
        else
        {
            int numTasks = group.size();
            completedTasks = 0;
            auto barrier = new Barrier(numTasks);
            for (CommandInterface *cmd : group)
            {
                if (cmd->isSubsystemOccupied())
                {
                    __throw_invalid_argument("Subsystem pointer must not already be use by a Command");
                    std::exit(1); 
                    
                }
                cmd->occupySubsystem();
                make_task(([cmd, barrier]()
                           {   
                    barrier->wait();
                    cmd->run();   
                    commandCompletion.broadcast();
                    return 0; })); 
                delete cmd; // Don't need it after the task was made
            }
            while (numTasks != completedTasks.load())
            {
                vex::this_thread::yield();
            }
            delete barrier;
        }
    }
}; 


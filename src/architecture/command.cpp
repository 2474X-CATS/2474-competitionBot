#include "command.h"
#include <functional>
#include "taskUtils.hpp"
#include "vex.h" 


std::atomic<int> ICommand::completedTasks = {0};

void incrementCompletedTasks()
{
    ICommand::completedTasks++;
}

vex::event commandCompletion(incrementCompletedTasks);

void ICommand::runCommandGroup(std::vector<std::vector<ICommand *>> systems)
{
    for (std::vector<ICommand *> group : systems)
    {
        if (group.size() == 1)
        {
            group[0]->run();
        }
        else
        {
            int numTasks = group.size();
            completedTasks = 0;
            auto barrier = new Barrier(numTasks);
            for (ICommand *cmd : group)
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
            }
            while (numTasks != completedTasks.load())
            {
                vex::this_thread::yield();
            }
            delete barrier;
        }
    }
};

#include "command.h"
#include <functional>
#include "taskUtils.hpp"

std::atomic<int> CommandInterface::completedTasks = {0};

void completeTask()
{
    CommandInterface::completedTasks++;
}

void CommandInterface::runCommandGroup(std::vector<std::vector<CommandInterface *>> systems)
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

            CommandInterface::completedTasks = 0;

            auto barrierOwner = std::make_unique<Barrier>(numTasks);
            Barrier *barrier = barrierOwner.get();

            for (CommandInterface *cmd : group)
            {
                if (cmd->isSubsystemOccupied())
                {
                    while (true)
                    {
                        vex::this_thread::yield();
                    }
                    // throw std::runtime_error("Subsystem pointer must not already be use by a Command");
                }
                cmd->occupySubsystem();
                make_task(([cmd, barrier]()
                           {    
                    barrier->wait();
                    cmd->run();   
                    completeTask();
                    delete cmd;
                    return 0; }));
            }
            while (numTasks != CommandInterface::completedTasks.load())
            {
                vex::this_thread::yield();
            }
        }
    }
};

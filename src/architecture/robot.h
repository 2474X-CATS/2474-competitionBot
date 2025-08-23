#ifndef __ROBOT_H__
#define __ROBOT_H__

#include <vector>
#include "vex.h"

class CommandInterface;

class Robot
{

private:
   void registerSystemSubtable();
   void updateSystemSubtable(); 
   std::vector<std::vector<CommandInterface*>> autonomousCommand;

public: 

   void initialize();
   void driverControl();
   void autonControl();
   void runTelemetry(bool showGraphics);    
   void setAutonomousCommand(std::vector<std::vector<CommandInterface*>> comm);
   
};

#endif
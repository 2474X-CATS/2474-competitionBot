#ifndef __ROBOT_H__
#define __ROBOT_H__

#include <vector>
#include "vex.h"
/* 
  The robot brings it all together  

  initialize() -> Calls Subsystems.initSystems() and [registerSystemSubtable() for miscellaneous telemetry] 
  
  driverControl() -> Constructs a loop of Subsystem.updateSystems() that runs every 20ms  

  setAutonomousCommand() -> Sets the commandGroup that is going to run in the autonomous period
  autonControl() -> Runs the autonomousCommand using CommandInterface::runCommandGroup()  
  
  runTelemetryThread() -> Constructs a loop of Subsystem.updateTelemetry() and updateSystemSubtable() while every  
  thing is happening
   
*/
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
   void runTelemetryThread(bool showGraphics);    
   void setAutonomousCommand(std::vector<std::vector<CommandInterface*>> comm);
   
};

#endif
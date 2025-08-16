#ifndef __ROBOT_H__
#define __ROBOT_H__

#include <vector>
#include "vex.h"

struct ICommand;

class Robot
{

private:
   void registerSystemSubtable();
   void updateSystemSubtable(); 
   static std::vector<std::vector<ICommand*>> autonomousCommand;

public:
   void initialize();
   void driverControl();
   void autonControl();
   void runTelemetry();    
   void setAutonomousCommand();
   
   
   
   
};

#endif
#include "vex.h"
#include "architecture/robot.h"
#include <iostream>
#include "subsystems/drivebase.h" 
#include "architecture/taskUtils.hpp"
using namespace vex;

competition Competition;
Robot robot;


void runTelemetry(){ 
   robot.runTelemetryThread(true);
}

void start()
{ 
  robot.initialize(); 
  Competition.drivercontrol([]()
                            { robot.driverControl(); });
  Competition.autonomous([]()
                         { robot.autonControl(); }); 
  robot.runTelemetryThread(false);
}

int main()
{
  vexcodeInit();   
  
  Drivebase drive = Drivebase(0, 0);  // Always assumes that the robot starts at angle 0 (May change)
  robot.initialize();  

  start();
}

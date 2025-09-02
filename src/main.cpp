#include "vex.h"
#include "architecture/robot.h"
#include <iostream>
#include "subsystems/drivebase.h" 
#include "architecture/taskUtils.hpp"
using namespace vex;

competition Competition;
Robot robot;


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
  //Initialize subsystems
  Drivebase drive = Drivebase(0, 0);  // Always assumes that the robot starts at angle 0 (May change) 
  //Set the autonomous command 

  //--------
  robot.initialize();   
  start();
}

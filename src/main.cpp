#include "vex.h"
#include "architecture/robot.h"
#include <iostream>
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
  
  //Set the autonomous command 

  //--------
  start();
}
#include "vex.h"
#include "architecture/robot.h"
#include <iostream> 
#include "architecture/taskUtils.hpp" 
#include "subsystems/drivebase.h" 
#include "subsystems/indexer.h" 

using namespace vex;

competition Competition;
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
  Drivebase drive; 
  Indexer indexer;
  //Set the autonomous command 
  
  //-------- 
  start();
}
#include "vex.h" 
#include "architecture/robot.h" 
#include <iostream>
#include "architecture/telemetry.h" 
#include "subsystems/drivebase.h"
using namespace vex;

competition Competition;  
Robot robot;


void start(bool isFieldControlled){   
  robot.initialize();
  if (isFieldControlled){ 
    Competition.drivercontrol([](){robot.driverControl();}); 
    Competition.autonomous([](){robot.autonControl();}); 
    robot.runTelemetryThread(false);
  } else { 
    robot.autonControl(); 
    robot.driverControl();   
    thread([](){robot.runTelemetryThread(false);});
  }
} 

int main() {      
  vexcodeInit();  
  //------------
 
  //-------------

  start(false);
}

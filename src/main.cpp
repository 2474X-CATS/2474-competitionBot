
#include "vex.h" 
#include "architecture/robot.h" 
#include <iostream>
#include "architecture/telemetry.h" 
#include "architecture/robotConfig.h"
using namespace vex;

// A global instance of competition
competition Competition;  
Robot robot;


void driverControl(){ 
  robot.driverControl();
} 

void autonControl(){ 
  robot.autonControl();
} 


int main() {     
  //Competition.autonomous(autonControl); 
  //Competition.drivercontrol(driverControl); 
  robot.initialize();   
  while (true){   
    robot.runTelemetry(true);  
    vex::this_thread::sleep_for(10); 
  }
}

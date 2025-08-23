
#include "vex.h" 
#include "architecture/robot.h" 
#include <iostream>
#include "architecture/telemetry.h" 
#include "architecture/robotConfig.h" 
#include "subsystems/Drivebase.h"
using namespace vex;

competition Competition;  
Robot robot;

void driverControl(){ 
  robot.driverControl();
} 

void autonControl(){ 
  robot.autonControl();
} 

int main() {     
 vexcodeInit();  
}

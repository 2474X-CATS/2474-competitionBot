#include "vex.h" 
#include "architecture/robot.h" 
#include <iostream>
#include "architecture/telemetry.h" 

using namespace vex;

competition Competition;  
Robot robot;

void driverControl(){ 
  robot.driverControl();
} 

void autonControl(){ 
  robot.autonControl();
}   

void setCallbacks(){ 
  Competition.drivercontrol(driverControl); 
  Competition.autonomous(autonControl);
}

int main() {      
 vexcodeInit();    
 /* Do everything here   
     - Declare subsystem classes
     - Set an autonomous routine  
 */  
 robot.initialize();
 setCallbacks(); //Auton-control and Drivercontrol are called in a different thread 
 robot.runTelemetryThread(false); // Main thread runs so the program doesn't exit  
 //(Might as well use to log telemetry) [Set bool value to true if you want to see graphics on the brain]
}

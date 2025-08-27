#include "vex.h" 
#include "architecture/robot.h" 
#include <iostream>
#include "architecture/telemetry.h" 
#include "subsystems/drivebase.h"
using namespace vex;

competition Competition;  
Robot robot;

void driverControl(){ 
  robot.driverControl();
} 

void autonControl(){ 
  robot.autonControl();
}    

void updateTelemetry(){ 
  robot.runTelemetryThread(false); 
} 

void initialize(){ 
   vexcodeInit();  
   vector<vector<CommandInterface*>> commandGroup;
   Drivebase drive;   
   commandGroup = {{DriveLinear::getCommand(drive, 20)}}; 
   robot.setAutonomousCommand(commandGroup);
} 

void start(bool isFieldControlled){  
  if (isFieldControlled){ 
    Competition.drivercontrol(driverControl); 
    Competition.autonomous(autonControl); 
    updateTelemetry(); 
  } else { 
    autonControl(); 
    driverControl();   
    thread(updateTelemetry);
  }
} 

int main() {      
  initialize(); 
  start(false);
}

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       talon-robotics                                            */
/*    Created:      7/14/2025, 12:27:36 PM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "robot.h"
using namespace vex;

// A global instance of competition
competition Competition;  
Robot robot; 
//Call set "setAutonomousCommand(...)" on robot to initialize auotnomous command

void driverControl(){ 
  robot.driverControl();
} 

void autonControl(){ 
  robot.autonControl();
}

int main() {
   
  Competition.drivercontrol(driverControl);
  Competition.autonomous(autonControl);
  // Run the pre-autonomous function.
  robot.initialize(); 
  // Prevent main from exiting with an infinite loop, and updates telemetry in a seperate thread.
  robot.runTelemetry();
}

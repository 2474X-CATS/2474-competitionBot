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
  
  Drivebase drive = Drivebase(0, 0);  
  //drive.init();
  robot.initialize();  
  /*
  robot.setAutonomousCommand( 
    { 
     {DriveLinear::getCommand(drive,500)},
     {TurnTo::getCommand(drive, 90)}, 
     {DriveLinear::getCommand(drive, 250)}
    } 
  );  
  */
  thread telem = thread(runTelemetry); 
  DriveLinear::getCommand(drive,500)->run(); 
  TurnTo::getCommand(drive, 90)->run(); 
  DriveLinear::getCommand(drive, 250)->run();
  robot.driverControl();  
  /*
  while (true){   
    if (Controller.ButtonA.pressing()){ 
      drive.manualDriveForward(-90);
    } else if (Controller.ButtonB.pressing()) {  
      drive.manualTurnClockwise(-60);
    } else { 
      drive.stop();
    } 
    Brain.Screen.print(driveGyro.heading()); 
    Brain.Screen.newLine();
    wait(20, msec);
  }  
  */
  //-------------

  //start();
}

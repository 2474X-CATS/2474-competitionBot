#include "vex.h"
#include "architecture/robot.h"
#include <iostream> 

#include "subsystems/drivebase.h"
#include "subsystems/indexer.h" 
#include "subsystems/hood.h" 
#include "subsystems/hopper.h" 
#include "subsystems/intake.h"  
#include "subsystems/matchloader.h"

using namespace vex;

competition Competition;
Robot robot; 

void runTelemetry()
{
  robot.runTelemetryThread(true);
}

void freeDrive()
{
  robot.initialize();
  thread telemetryThread = thread(runTelemetry);
  robot.driverControl(false);
} 


int main()
{

  vexcodeInit(); 
  // Initialize subsystems
  /*
    1: Configure auton
    2: Test auton
    3: Configure coding skills run
    4: Test coding skills run
    5: Run match [ Competitive | Driver-skills | Auton-skills ]
    6: Drive competition auton routine (recommended for test) 
    7: Start competition match with commands as auton
    8: Free drive
  */  

  Drivebase drive = Drivebase(0, 0);   
  Intake intake;  
  Matchloader matchloader;   
  Indexer indexer;  
  Hood hood; 
  Hopper hopper;  
   
  thread telemetry = thread(runTelemetry);  
  robot.initialize(); 
  robot.initializeMirror(MirrorMode::REFLECT, "skills/test.skil");  
  robot.driverControl(true);   
  robot.detachInput(); 

 /*
  //runTelemetry(); 
  long timestamp = Brain.Timer.time();
  while (true){  
      if (Controller.ButtonA.pressing()) 
        break; 
      drive.manualTurnClockwise(30); 
  } 
  drive.stop();

  Brain.Screen.printAt(15, 130, "%ld", (Brain.Timer.time() - timestamp)); 
  */
  
}

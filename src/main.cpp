#include "vex.h"
#include "architecture/robot.h"
#include <iostream> 

#include "subsystems/drivebase.h" 
#include "subsystems/indexer.h" 
#include "subsystems/hood.h" 
#include "subsystems/hopper.h" 
#include "subsystems/intake.h"  
#include "subsystems/matchloader.h" 
#include "commands.h" 

using namespace vex;

competition Competition;
Robot robot; 

typedef enum
{
  CODING_SKILLS,
  DRIVER_SKILLS,
  COMPETITIVE
} MatchType;

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

/*
void mirrorMobilize(MirrorMode mode, string filename)
{
  switch (mode)
  {
  case REFLECT:
    robot.initializeMirror(MirrorMode::REFLECT, filename);
    break;
  case ABSORB:
    robot.initializeMirror(MirrorMode::ABSORB, filename);
    break;
  default:
    return;
  }
  robot.initialize();
  thread telem = thread(runTelemetry);
  robot.driverControl(true); 
  robot.detachInput();
}

void startMatch(MatchType type, string auton, string auton_skills)
{
  switch (type)
  {
  case CODING_SKILLS:
    robot.initializeMirror(MirrorMode::REFLECT, auton_skills);
    break;
  default:
    robot.initializeMirror(MirrorMode::REFLECT, auton);
    break;
  }
  robot.initialize();
  Competition.drivercontrol([]()
                            { robot.driverControl(false); });
  Competition.autonomous([]()
                         { robot.driverControl(true); }); 
  while (!Competition.isEnabled()) 
     this_thread::yield();
  robot.runTelemetryThread(true);
}
*/ 

void startCommandMatch(std::vector<CommandInterface*> commandGroup){  
  robot.initialize();
  robot.setAutonomousCommand(commandGroup);
  Competition.autonomous([](){robot.autonControl();}); 
  Competition.drivercontrol([](){robot.driverControl(false);});  
  while (!Competition.isEnabled()) 
     this_thread::yield();
  robot.runTelemetryThread(true);
}  

void driveCommandMatch(std::vector<CommandInterface*> commandGroup){  
  robot.initialize();
  robot.setAutonomousCommand(commandGroup);  
  thread telemThread = thread(runTelemetry);
  robot.autonControl(); 
  robot.detachInput();  
  robot.stopEverything(); 
  telemThread.join();
} 
/*
void declareLocations(){ 
  Location nativeBallCluster = Location(
    "ballClusterNative",
    0,
    300,
    200,
    180,
    179);  
} 
*/

int main()
{

  vexcodeInit(); 
  //declareLocations(); 
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

  
  Drivebase drive = Drivebase(1,1); //Tile location right 1 up 1    
  Intake intake;  
  Matchloader matchloader;   
  Indexer indexer;  
  Hood hood; 
  Hopper hopper;     
   
  robot.initialize(); 

  thread telemThread = thread(runTelemetry);
  CommandInterface* comm = WaitFor::getCommand(1000);  
  comm->run();  
  Brain.Screen.print("Ended safely");
  delete comm;    
  robot.driverControl(false);
 
  
}

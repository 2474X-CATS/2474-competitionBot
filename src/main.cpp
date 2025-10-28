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

void startCommandMatch(std::vector<CommandInterface*> commandGroup){ 
  robot.setAutonomousCommand(commandGroup);
  Competition.autonomous([](){robot.autonControl();}); 
  Competition.drivercontrol([](){robot.driverControl(false);});  
  while (!Competition.isEnabled()) 
     this_thread::yield();
  robot.runTelemetryThread(true);
}  

void driveCommandMatch(std::vector<CommandInterface*> commandGroup){ 
  robot.setAutonomousCommand(commandGroup);  
  thread telemThread = thread(runTelemetry);
  robot.autonControl(); 
  robot.detachInput();
} 

void declareLocations(){ 
  Location nativeBallCluster = Location(
    "ballClusterNative",
    0,
    300,
    200,
    180,
    179);  
} 



/*
void driveForward(Drivebase driveRef, double forwardDisplacement){ 
  pidcontroller controller = pidcontroller(driveRef.getPowerPID(), forwardDisplacement);   
  double startingPoint[2]; 
  startingPoint[0] = driveRef.get<double>("Pos_X");
  startingPoint[1] = driveRef.get<double>("Pos_Y");
  controller.setLastTimestamp(Brain.Timer.time(vex::timeUnits::msec)); 
  while (!controller.atSetpoint() && !Controller.ButtonA.pressing()){   
     double currentPoint[2] = {driveRef.get<double>("Pos_X"), driveRef.get<double>("Pos_Y")}; 
     double distTraveled = hypot(currentPoint[0] - startingPoint[0], currentPoint[1] - startingPoint[1]);
     driveRef.manualDriveForward(30);//controller.calculate(distTraveled, Brain.Timer.time(vex::timeUnits::msec))); 
  }   
  driveRef.stop();
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

  
  Drivebase drive = Drivebase(1, 1); //Tile location right 1 up 1    
  Intake intake;  
  Matchloader matchloader;   
  Indexer indexer;  
  Hood hood; 
  Hopper hopper;    
  freeDrive();
 //driveForward(drive, 500);
  
}

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
  thread telemThread = thread(runTelemetry); //Start data logging
  robot.setAutonomousCommand(commandGroup); //Registers the autonomous routine
  robot.autonControl(); //Runs the autonomous command
  Controller.rumble("--"); //Signals that the auton is finished
  robot.driverControl(false); //Free drive
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

vector<CommandInterface*> AUTO_SHORT_ORIGIN(){ 
    return { 
      turnToAngle(330), 
      driveAndIntakeForTiles(1.2),  
      turnToAngle(45), 
      driveForwardByTiles(1), 
      scoreOnGoal(Goal_Pos::MID_GOAL, 2000), 
      driveForwardByTiles(-1), 
      turnToAngle(90), 
      driveAndIntakeForTiles(2), 
      turnToAngle(315), 
      driveForwardByTiles(0.6666), 
      scoreOnGoal(Goal_Pos::LOW_GOAL, 2000),
    };
};  

vector<CommandInterface*> AUTO_SHORT_INVERTED(){ 
    return { 
      turnToAngle(360 - 330), 
      driveAndIntakeForTiles(1.2),  
      turnToAngle(360 - 45), 
      driveForwardByTiles(1), 
      scoreOnGoal(Goal_Pos::LOW_GOAL, 2000), 
      driveForwardByTiles(-1), 
      turnToAngle(360 - 90), 
      driveAndIntakeForTiles(2), 
      turnToAngle(360 - 315), 
      driveForwardByTiles(0.6666), 
      scoreOnGoal(Goal_Pos::MID_GOAL, 2000),
    };
};  

vector<CommandInterface*> AUTO_CLOSED_SIDE_ORIGIN(){ 
    return { 
      turnToAngle(270), 
      driveForwardByTiles(1.6666), 
      turnToAngle(180), 
      extend(), 
      ramForwardFor(0.60, 3000), 
      intakeCubes(3000),  
      retract(), 
      driveForwardByTiles(-0.75),  
      turnToAngle(0), 
      scoreOnGoal(Goal_Pos::HIGH_GOAL, 3000), 
      driveForwardByTiles(-0.125), 
      turnToAngle(75), 
      driveAndIntakeForTiles(1),  
      driveForwardByTiles(1), 
      scoreOnGoal(Goal_Pos::MID_GOAL, 3000)
    };
};  

vector<CommandInterface*> AUTO_CLOSED_SIDE_INVERTED(){ 
    return { 
      turnToAngle(360 - 270), 
      driveForwardByTiles(1.6666), 
      turnToAngle(180), 
      extend(), 
      ramForwardFor(0.60, 3000), 
      intakeCubes(3000),  
      retract(), 
      driveForwardByTiles(-0.75),  
      turnToAngle(0), 
      scoreOnGoal(Goal_Pos::HIGH_GOAL, 3000), 
      driveForwardByTiles(-0.125), 
      turnToAngle(360 - 75), 
      driveAndIntakeForTiles(1),  
      driveForwardByTiles(1), 
      scoreOnGoal(Goal_Pos::LOW_GOAL, 3000)
    };
};  

vector<CommandInterface*> AUTO_SELF_SUFFICIENT_ORIGIN(){ 
    return { 
      turnToAngle(270), 
      driveForwardByTiles(1.6666), 
      turnToAngle(180), 
      extend(), 
      ramForwardFor(0.60, 3000), 
      intakeCubes(3000),  
      retract(), 
      driveForwardByTiles(-0.75),  
      turnToAngle(0), 
      scoreOnGoal(Goal_Pos::HIGH_GOAL, 3000), 
      driveForwardByTiles(-0.125), 
      turnToAngle(75), 
      driveAndIntakeForTiles(1),  
      driveForwardByTiles(1), 
      scoreOnGoal(Goal_Pos::MID_GOAL, 2000), 
      driveForwardByTiles(-1), 
      turnToAngle(90),
      driveAndIntakeForTiles(2), 
      turnToAngle(315), 
      driveForwardByTiles(0.6666), 
      scoreOnGoal(Goal_Pos::LOW_GOAL, 2000)
    };
};  

vector<CommandInterface*> AUTO_SELF_SUFFICIENT_INVERTED(){ 
    return { 
      turnToAngle(360 - 270), 
      driveForwardByTiles(1.6666), 
      turnToAngle(180), 
      extend(), 
      ramForwardFor(0.60, 3000), 
      intakeCubes(3000),  
      retract(), 
      driveForwardByTiles(-0.75),  
      turnToAngle(0), 
      scoreOnGoal(Goal_Pos::HIGH_GOAL, 3000), 
      driveForwardByTiles(-0.125), 
      turnToAngle(360 - 75), 
      driveAndIntakeForTiles(1),  
      driveForwardByTiles(1), 
      scoreOnGoal(Goal_Pos::LOW_GOAL, 2000), 
      driveForwardByTiles(-1), 
      turnToAngle(360 - 90),
      driveAndIntakeForTiles(2), 
      turnToAngle(360 - 315), 
      driveForwardByTiles(0.6666), 
      scoreOnGoal(Goal_Pos::MID_GOAL, 2000)
    };
};  

vector<CommandInterface*> PROGRAMMING_SKILLS(){ 
    return { 
      driveForwardByTiles(0.6), 
      turnToAngle(323), 
      driveAndIntakeForTiles(0.5), 
      turnToAngle(225), 
      driveForwardByTiles(1.6), 
      turnToAngle(11.5), 
      driveForwardByTiles(0.6), 
      scoreOnGoal(Goal_Pos::HIGH_GOAL, 4500)
    };
};


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

  
  Drivebase drive = Drivebase(1,1); //Tile location right 1 up 1    
  Intake intake;  
  Matchloader matchloader;   
  Indexer indexer;  
  Hood hood; 
  Hopper hopper;     
   
  driveCommandMatch(AUTO_SHORT_ORIGIN());  

}

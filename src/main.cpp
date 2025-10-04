#include "vex.h"
#include "architecture/robot.h"
#include <iostream>
#include "architecture/taskUtils.hpp"   
/*
#include "subsystems/drivebase.h" 
#include "subsystems/indexer.h" 
*/

using namespace vex;

competition Competition; 

Robot robot; //Writing inputs to trial1.auto

typedef enum { 
   CODING_SKILLS, 
   DRIVER_SKILLS, 
   COMPETITIVE
} MatchType; 

void runTelemetry(){ 
  robot.runTelemetryThread(true);
} 

void freeDrive(){ 
 robot.initialize(); 
 thread telemetryThread = thread(runTelemetry); 
 robot.driverControl(false); 
} 

void mirrorMobilize(MirrorMode mode, string filename)
{  
  switch (mode){ 
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
}  

void startMatch(MatchType type, string auton, string auton_skills){ 
    switch (type){ 
      case CODING_SKILLS:   
        robot.initializeMirror(MirrorMode::REFLECT, auton_skills); 
        break;
      case COMPETITIVE: 
        robot.initializeMirror(MirrorMode::REFLECT, auton); 
        break;
      default: 
        break;
    } 
    robot.initialize();
    Competition.drivercontrol([]()
                            { robot.driverControl(false);});
    Competition.autonomous([]()
                         { robot.driverControl(true);});
    robot.runTelemetryThread(false);
}


int main()
{

  vexcodeInit();
  // Initialize subsystems  
  mirrorMobilize(MirrorMode::REFLECT, "test1.auto"); 
}
#pragma once 
using namespace vex; 

extern brain Brain; 

extern controller Controller; 

/* 
 TO-DO: 
   o- Initialize all vex devices here (motors/sensors/pneumatics/etc) 
   o- Initialize constants
*/  

//------- 

// Constants: PLACE HERE [using extern]
extern double ABSOLUTE_INDEXER_SPEED; 
// Devices: PLACE HERE [using extern]
extern motor indexerMotor;  
extern pneumatics hoodPiston;
//------- 

void vexcodeInit();
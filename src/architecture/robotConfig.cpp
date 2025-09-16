#include "vex.h"

brain Brain; 

controller Controller = controller(controllerType::primary);  

/* 
 TO-DO: 
   o- Initialize all vex devices here (motors/sensors/pneumatics/etc) 
   o- Initialize constants
*/  

//------- 

// Constants: PLACE HERE [regularly]
double ABSOLUTE_INDEXER_SPEED = 1;
// Devices: PLACE HERE [regularly]
motor indexerMotor = motor(PORT14); 
pneumatics hoodPiston = pneumatics(Brain.ThreeWirePort.G);
//-------

void vexcodeInit(){ 

};



#include "vex.h"
#include "math.h" 
using namespace vex;  

brain Brain; 

controller Controller = controller(controllerType::primary);  

/* 
 TO-DO: 
   o- Initialize all vex devices here (motors/sensors/pneumatics/etc) 
   o- Initialize constants
*/  

//------- 

// Constants: PLACE HERE [regularly] 

double DRIVE_WHEEL_RADIUS_MM = 30; 
double TRACK_WIDTH_MM = 30;
double WHEEL_BASE_MM = 30;
double EXTERNAL_GEAR_RATIO = 30;

// Devices: PLACE HERE [regularly] 

inertial driveGyro = inertial(PORT20); 
motor driveFrontLeft = motor(PORT1, ratio18_1, true); 
motor driveFrontRight = motor(PORT10, ratio18_1, true);  

motor driveMidLeft = motor(PORT2, ratio18_1, true); 
motor driveMidRight = motor(PORT9, ratio18_1, true);   

motor driveBackLeft = motor(PORT3, ratio18_1); 
motor driveBackRight = motor(PORT8, ratio18_1); 


motor_group leftDriveMotors = motor_group(driveFrontLeft, driveBackLeft, driveMidLeft); 
motor_group rightDriveMotors = motor_group(driveFrontRight, driveBackRight, driveMidRight); 

//encoder driveRotationEncoder = encoder(Brain.ThreeWirePort.C);  
//encoder driveForwardEncoder = encoder(Brain.ThreeWirePort.A);

smartdrive driveMotors = smartdrive( 
  leftDriveMotors,  
  rightDriveMotors,  
  driveGyro,  
  (DRIVE_WHEEL_RADIUS_MM * 2 * M_PI), 
  TRACK_WIDTH_MM, 
  WHEEL_BASE_MM, 
  vex::distanceUnits::mm, 
  EXTERNAL_GEAR_RATIO
);

//-------

void vexcodeInit(){ 

};



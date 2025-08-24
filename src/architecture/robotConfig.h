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

extern double ROBOT_RADIUS_MM; 
extern double ENCODER_WHEEL_RADIUS_MM; 
extern double DRIVE_WHEEL_RADIUS_MM; 
extern double ROT_ENCODER_DIST_FROM_CENTER_MM; 

// Devices: PLACE HERE [using extern] 

extern motor driveFrontLeft; 
extern motor driveFrontRight; 
extern motor driveBackLeft; 
extern motor driveBackRight; 
extern motor driveMidLeft; 
extern motor driveMidRight;  

extern encoder driveRotationEncoder; 
extern encoder drivePowerEncoder;

extern drivetrain driveMotors; // Drivetrain  

//------- 

void vexcodeInit();
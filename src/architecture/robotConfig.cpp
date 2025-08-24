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

double ROBOT_RADIUS_MM = 1; 
double ENCODER_WHEEL_RADIUS_MM = 3; 
double DRIVE_WHEEL_RADIUS_MM = 5; 
double ROT_ENCODER_DIST_FROM_CENTER_MM = 3;  

// Devices: PLACE HERE [regularly] 

double ROBOT_RADIUS_MM = 1; 
double ENCODER_WHEEL_RADIUS_MM = 3; 
double DRIVE_WHEEL_RADIUS_MM = 5; 
double ROT_ENCODER_DIST_FROM_CENTER_MM = 3; 

motor driveFrontLeft = motor(PORT1, ratio18_1, true); 
motor driveFrontRight = motor(PORT10, ratio18_1, true);  

motor driveMidLeft = motor(PORT2, ratio18_1, true); 
motor driveMidRight = motor(PORT9, ratio18_1, true);   

motor driveBackLeft = motor(PORT3, ratio18_1); 
motor driveBackRight = motor(PORT8, ratio18_1); 


motor_group leftDriveMotors = motor_group(driveFrontLeft, driveBackLeft, driveMidLeft); 
motor_group rightDriveMotors = motor_group(driveFrontRight, driveBackRight, driveMidRight); 

encoder driveRotationEncoder = encoder(Brain.ThreeWirePort.C);  
encoder driveForwardEncoder = encoder(Brain.ThreeWirePort.A);

drivetrain driveMotors = drivetrain(leftDriveMotors, rightDriveMotors);

//-------

void vexcodeInit(){ 

};



#include "vex.h"

brain Brain; 

controller Controller = controller(controllerType::primary); 
/* 
 TO-DO: 
   o- Correctly set the all of the device ports
*/ 

// Constants 
double ROBOT_RADIUS_MM = 1; 
double ENCODER_WHEEL_RADIUS_MM = 3; 
double DRIVE_WHEEL_RADIUS_MM = 5; 
double ROT_ENCODER_DIST_FROM_CENTER_MM = 3;

//-----Channel
//motor channelMotor1 = motor(PORT1); 
//motor channelMotor2 = motor(PORT1);   
//motor channelMotor3 = motor(PORT1); 
//pneumatics channelPneumatics = pneumatics(Brain.ThreeWirePort.A);
//-----Drivebase 
motor driveFrontLeft = motor(PORT1, ratio18_1, true); 
motor driveFrontRight = motor(PORT10, ratio18_1, true);  

motor driveMidLeft = motor(PORT2, ratio18_1, true); 
motor driveMidRight = motor(PORT9, ratio18_1, true);   

motor driveBackLeft = motor(PORT3, ratio18_1); 
motor driveBackRight = motor(PORT8, ratio18_1); 


motor_group leftDriveMotors = motor_group(driveFrontLeft, driveBackLeft, driveMidLeft); 
motor_group rightDriveMotors = motor_group(driveFrontRight, driveBackRight, driveMidRight); 

//encoder driveRotationEncoder = encoder(Brain.ThreeWirePort.C); 

drivetrain driveMotors = drivetrain(leftDriveMotors, rightDriveMotors);

void vexcodeInit(){ 

};



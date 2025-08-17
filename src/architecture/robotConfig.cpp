#include "vex.h"

brain Brain; 

controller Controller = controller(controllerType::primary); 
/* 
 TO-DO: 
   o- Correctly set the all of the device ports
*/ 

// Constants

//-----Channel
motor channelMotor1 = motor(PORT1); 
motor channelMotor2 = motor(PORT1);   
motor channelMotor3 = motor(PORT1); 
pneumatics channelPneumatics = pneumatics(Brain.ThreeWirePort.A);
//-----Drivebase 
motor driveFrontLeft = motor(PORT1); 
motor driveFrontRight = motor(PORT1); 
motor driveBackLeft = motor(PORT1); 
motor driveBackRight = motor(PORT1); 
motor driveMidLeft = motor(PORT1); 
motor driveMidRight = motor(PORT1); 

motor_group leftDriveMotors = motor_group(driveFrontLeft, driveBackLeft, driveMidLeft); 
motor_group rightDriveMotors = motor_group(driveBackRight, driveMidRight, driveFrontRight); 

encoder driveRotationEncoder = encoder(Brain.ThreeWirePort.C); 

drivetrain driveMotors = drivetrain(leftDriveMotors, rightDriveMotors);




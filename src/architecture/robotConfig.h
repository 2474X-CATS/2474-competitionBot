#pragma once 
using namespace vex; 

extern brain Brain; 

extern controller Controller; 


//Constants 
extern double ROBOT_RADIUS_MM; 
extern double ENCODER_WHEEL_RADIUS_MM; 
extern double DRIVE_WHEEL_RADIUS_MM; 
extern double ROT_ENCODER_DIST_FROM_CENTER_MM;
// Subsystems 

//-----Channel
extern motor channelMotor1; 
extern motor channelMotor2;   
extern motor channelMotor3; 
extern pneumatics channelPneumatics;
//-----Drivebase 
extern motor driveFrontLeft; 
extern motor driveFrontRight; 
extern motor driveBackLeft; 
extern motor driveBackRight; 
extern motor driveMidLeft; 
extern motor driveMidRight;  

extern encoder driveRotationEncoder; 
extern encoder drivePowerEncoder;

extern drivetrain driveMotors; // Drivetrain
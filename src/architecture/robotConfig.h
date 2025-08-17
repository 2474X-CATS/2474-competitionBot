#pragma once 
using namespace vex; 

extern brain Brain; 

extern controller Controller; 

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
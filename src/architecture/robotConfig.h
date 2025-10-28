#pragma once

#include "vex.h" 

extern vex::brain Brain;

extern vex::controller Controller;

/*
 TO-DO:
   o- Initialize all vex devices here (motors/sensors/pneumatics/etc)
   o- Initialize constants
*/

//-------

// Constants: PLACE HERE [using extern]

extern double ABSOLUTE_INDEXER_SPEED;

extern double DRIVE_WHEEL_RADIUS_MM;

extern double ROBOT_WIDTH_MM; 
extern double ROBOT_LENGTH_MM; 

extern double TILE_SIZE_MM; 
// Devices: PLACE HERE [using extern]
extern vex::inertial driveGyro; 

extern vex::motor driveFrontLeft;
extern vex::motor driveMidLeft;
extern vex::motor driveBackLeft; 

extern vex::motor driveBackRight;
extern vex::motor driveFrontRight;
extern vex::motor driveMidRight;

extern vex::motor_group leftDriveMotors;
extern vex::motor_group rightDriveMotors;

//Hopper System
extern vex::motor hopperMotor; // Motor that moves discs inside robot

//MatchLoader System
extern vex::pneumatics matchloaderPiston; // Piston that loads discs

extern vex::motor intakeMotor; 

extern vex::motor indexerMotor;
extern vex::pneumatics hoodPiston;


// extern encoder driveRotationEncoder;
// extern encoder drivePowerEncoder;

// extern vex::smartdrive driveMotors; // Drivetrain

//-------

void vexcodeInit(); 

void stopEverything();
#pragma once

extern vex::brain Brain;

extern vex::controller Controller;

/*
 TO-DO:
   o- Initialize all vex devices here (motors/sensors/pneumatics/etc)
   o- Initialize constants
*/

//-------

// Constants: PLACE HERE [using extern]

extern double DRIVE_WHEEL_RADIUS_MM;
extern double TRACK_WIDTH_MM;      // Dist between the center point of the right and left wheel groups
extern double WHEEL_BASE_MM;       // Dist between the center point of the front and rear wheels
extern double EXTERNAL_GEAR_RATIO; // Final result of doing the gear ratio calculation on the drive gear train

// Devices: PLACE HERE [using extern]
extern vex::inertial driveGyro;
extern vex::motor driveFrontLeft;
extern vex::motor driveFrontRight;
extern vex::motor driveBackLeft;
extern vex::motor driveBackRight;
extern vex::motor driveMidLeft;
extern vex::motor driveMidRight;

extern vex::motor_group leftDriveMotors; 
extern vex::motor_group rightDriveMotors; 

extern double ABSOLUTE_INDEXER_SPEED; 

extern vex::motor indexerMotor;  
extern vex::pneumatics hoodPiston; 

// extern encoder driveRotationEncoder;
// extern encoder drivePowerEncoder;

//extern vex::smartdrive driveMotors; // Drivetrain

//------- 

void vexcodeInit();
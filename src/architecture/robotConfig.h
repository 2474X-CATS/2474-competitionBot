#pragma once 

extern brain Brain; 

extern controller Controller; 

/* 
 TO-DO: 
   o- Initialize all vex devices here (motors/sensors/pneumatics/etc) 
   o- Initialize constants
*/  

//------- 

// Constants: PLACE HERE [using extern]

extern double DRIVE_WHEEL_RADIUS_MM; 
extern double TRACK_WIDTH_MM; //Dist between the center point of the right and left wheel groups
extern double WHEEL_BASE_MM; // Dist between the center point of the front and rear wheels 
extern double EXTERNAL_GEAR_RATIO; //Final result of doing the gear ratio calculation on the drive gear train

// Devices: PLACE HERE [using extern] 
extern inertial driveGyro;
extern motor driveFrontLeft; 
extern motor driveFrontRight; 
extern motor driveBackLeft; 
extern motor driveBackRight; 
extern motor driveMidLeft; 
extern motor driveMidRight;  

//extern encoder driveRotationEncoder; 
//extern encoder drivePowerEncoder;

extern smartdrive driveMotors; // Drivetrain  

//------- 

void vexcodeInit();
#include "vex.h"

vex::brain Brain;

vex::controller Controller = vex::controller(vex::controllerType::primary);

/*
 TO-DO:
   o- Initialize all vex devices here (motors/sensors/pneumatics/etc)
   o- Initialize constants
*/

//------- 
// Constants: PLACE HERE [regularly]
double ABSOLUTE_INDEXER_SPEED = 200; 
double DRIVE_WHEEL_RADIUS_MM = 76.2;
double TRACK_WIDTH_MM = 381;
double WHEEL_BASE_MM = 203.2;
double EXTERNAL_GEAR_RATIO = 0.6;

// Devices: PLACE HERE [regularly]

vex::inertial driveGyro = vex::inertial(vex::PORT20); 

vex::motor driveFrontLeft = vex::motor(vex::PORT1, vex::ratio18_1, true); 
vex::motor driveMidLeft = vex::motor(vex::PORT2, vex::ratio18_1, true); 
vex::motor driveBackLeft = vex::motor(vex::PORT3, vex::ratio18_1); 

vex::motor driveFrontRight = vex::motor(vex::PORT10, vex::ratio18_1, true);
vex::motor driveMidRight = vex::motor(vex::PORT9, vex::ratio18_1, true);
vex::motor driveBackRight = vex::motor(vex::PORT8, vex::ratio18_1);

vex::motor_group leftDriveMotors = vex::motor_group(driveFrontLeft, driveBackLeft, driveMidLeft);
vex::motor_group rightDriveMotors = vex::motor_group(driveFrontRight, driveBackRight, driveMidRight);

vex::motor indexerMotor = vex::motor(vex::PORT19); 
vex::pneumatics hoodPiston = vex::pneumatics(Brain.ThreeWirePort.G);  

vex::motor intakeMotor = vex::motor(vex::Port#, vex ::gearSetting::ratio, false); //motor


//vex::motor hopperMotor = vex::motor(vex::PORT19);

//vex::motor intake = vex::motor(vex::PORT16);
//-------

void vexcodeInit() {

};

#include "vex.h"
#include "math.h"

vex::brain Brain;

vex::controller Controller = vex::controller(vex::controllerType::primary);

/*
 TO-DO:
   o- Initialize all vex devices here (motors/sensors/pneumatics/etc)
   o- Initialize constants
*/

//-------

// Constants: PLACE HERE [regularly]

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

// encoder driveRotationEncoder = encoder(Brain.ThreeWirePort.C);
// encoder driveForwardEncoder = encoder(Brain.ThreeWirePort.A);
/*
vex::smartdrive driveMotors = vex::smartdrive(
    leftDriveMotors,
    rightDriveMotors,
    driveGyro,
    (DRIVE_WHEEL_RADIUS_MM * 2 * M_PI),
    TRACK_WIDTH_MM,
    WHEEL_BASE_MM,
    vex::distanceUnits::mm,
    EXTERNAL_GEAR_RATIO); 
*/

//-------

void vexcodeInit() {

};

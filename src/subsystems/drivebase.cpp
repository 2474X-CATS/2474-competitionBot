#include "drivebase.h"
#include "math.h"
#include "../architecture/telemetry.h"
#include <algorithm>

//---Drivebase: SUBSYSTEM

void Drivebase::init()
{
   leftDriveMotors.setStopping(vex::brakeType::brake);
   rightDriveMotors.setStopping(vex::brakeType::brake);

   driveGyro.calibrate();
   while (driveGyro.isCalibrating())
   {
      vex::this_thread::yield();
   }

   driveGyro.setHeading(0, vex::rotationUnits::deg);

   powerPID.P = 0.5;
   powerPID.I = 0.001;
   powerPID.D = 0;
   powerPID.errorTolerance = 10;
   //------------------------------
   turnPID.P = 1;
   turnPID.I = 0.01;
   turnPID.D = 0;
   turnPID.errorTolerance = 5;

   set<double>("Pos_X", startX + ROBOT_WIDTH_MM / 2);
   set<double>("Pos_Y", startY + ROBOT_LENGTH_MM / 2);
   set<string>("Current_Location", "NONE");
};

void Drivebase::periodic()
{ 
   arcadeDrive((double)getFromInputs<int>("Controller/Axis-Vert-Left"), (double)getFromInputs<int>("Controller/Axis-Hori-Right"));
};

void Drivebase::updateTelemetry()
{
   double x = get<double>("Pos_X");
   double y = get<double>("Pos_Y");  
   set<double>("Angle_Degrees", driveGyro.heading()); 

   double rpmToDist = (DRIVE_WHEEL_RADIUS_MM * 2 * M_PI) * 0.02;
   double hypotenuse = ((leftDriveMotors.velocity(vex::velocityUnits::rpm) - rightDriveMotors.velocity(vex::velocityUnits::rpm)) / 2) / 60 * rpmToDist; // Times 0.02 because that is the time interval

   double angleRadians = get<double>("Angle_Degrees") * M_PI / 180.0;

   x += hypotenuse * cos(angleRadians);
   y += hypotenuse * sin(angleRadians);

   set<double>("Pos_X", x);
   set<double>("Pos_Y", y);   
}; 

/*
void Drivebase::updateLocations()
{ 

}
*/

void Drivebase::arcadeDrive(double speed, double rotation)
{ 
   speed = speed > 100 ? 100 : (speed < -100 ? -100 : speed); 
   rotation = rotation > 100 ? 100 : (rotation < -100 ? -100 : rotation);  
   leftDriveMotors.setVelocity((speed + rotation) * speedFactor, vex::percentUnits::pct);
   leftDriveMotors.spin(vex::directionType::fwd);
   rightDriveMotors.setVelocity((speed - rotation) * speedFactor, vex::percentUnits::pct);
   rightDriveMotors.spin(vex::directionType::rev);
};

void Drivebase::manualDriveForward(double speedMM)
{
   double netSpeed = speedMM / (DRIVE_WHEEL_RADIUS_MM * 2 * M_PI) * 60;
   leftDriveMotors.setVelocity(netSpeed, vex::velocityUnits::rpm);
   rightDriveMotors.setVelocity(-netSpeed, vex::velocityUnits::rpm);
   leftDriveMotors.spin(vex::directionType::fwd);
   rightDriveMotors.spin(vex::directionType::fwd);
};

void Drivebase::manualTurnClockwise(double turnDeg)
{
   turnDeg += 3;
   turnDeg *= 2.79999;
   leftDriveMotors.setVelocity(turnDeg, vex::velocityUnits::dps);
   rightDriveMotors.setVelocity(turnDeg, vex::velocityUnits::dps);
   leftDriveMotors.spin(vex::directionType::fwd);
   rightDriveMotors.spin(vex::directionType::fwd);
};

void Drivebase::stop()
{
   leftDriveMotors.setVelocity(0, vex::percentUnits::pct);
   rightDriveMotors.setVelocity(0, vex::percentUnits::pct);
};

/*
void Drivebase::updateTileCoordinates()
{   
 
}
*/
PIDConstants Drivebase::getPowerPID()
{
   return this->powerPID;
};

PIDConstants Drivebase::getTurningPID()
{
   return this->turnPID;
};

void Drivebase::setSpeedFactor(double speedFactor){ 
   this->speedFactor = speedFactor;
}
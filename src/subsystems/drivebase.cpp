#include "vex.h"
#include "drivebase.h"
#include "math.h"
#include "../architecture/telemetry.h"

//---Drivebase: SUBSYSTEM

void Drivebase::init()
{
   leftDriveMotors.setStopping(vex::brakeType::brake);
   rightDriveMotors.setStopping(vex::brakeType::brake);  

   driveGyro.calibrate(); 
   while (driveGyro.isCalibrating()){ 
    vex::this_thread::yield();
   } 
   
   powerPID.P = 0.4;
   powerPID.I = 0.001;
   powerPID.D = 0;
   powerPID.errorTolerance = 2;
   //------------------------------
   turnPID.P = 1;
   turnPID.I = 0.01;
   turnPID.D = 0;
   turnPID.errorTolerance = 2;
   

   set<double>("Pos_X", startX);
   set<double>("Pos_Y", startY);
};

void Drivebase::periodic()
{
   arcadeDrive(getFromInputs<int>("Controller/Axis-Vert-Left") * speedFactor, getFromInputs<int>("Controller/Axis-Hori-Right") * speedFactor);
};
// TO-DO: FIX
void Drivebase::updateTelemetry()
{
   set<double>("Angle_Degrees", driveGyro.heading());

   double x = get<double>("Pos_X");
   double y = get<double>("Pos_Y");

   double rpmToDist = (DRIVE_WHEEL_RADIUS_MM * 2 * M_PI) * 0.02;
   double hypotenuse = ((leftDriveMotors.velocity(vex::velocityUnits::rpm) - rightDriveMotors.velocity(vex::velocityUnits::rpm)) / 2) / 60 * rpmToDist; // Times 0.02 because that is the time interval

   double angleRadians = get<double>("Angle_Degrees") * M_PI / 180.0;

   x += hypotenuse * cos(angleRadians);
   y += hypotenuse * sin(angleRadians);

   set<double>("Pos_X", x);
   set<double>("Pos_Y", y);  
};

void Drivebase::arcadeDrive(double speed, double rotation)
{
   leftDriveMotors.setVelocity((speed + rotation), vex::percentUnits::pct);
   leftDriveMotors.spin(vex::directionType::fwd);
   rightDriveMotors.setVelocity((speed - rotation), vex::percentUnits::pct);
   rightDriveMotors.spin(vex::directionType::rev);
};

void Drivebase::manualDriveForward(double speedMM)
{
   double netSpeed = speedMM / (DRIVE_WHEEL_RADIUS_MM * 2 * M_PI) * 60;
   leftDriveMotors.setVelocity(netSpeed, vex::velocityUnits::rpm);
   rightDriveMotors.setVelocity(netSpeed, vex::velocityUnits::rpm);
   leftDriveMotors.spin(vex::directionType::fwd);
   rightDriveMotors.spin(vex::directionType::rev);
};

void Drivebase::manualTurnClockwise(double turnDeg)
{
   leftDriveMotors.setVelocity(turnDeg, vex::velocityUnits::dps);
   rightDriveMotors.setVelocity(turnDeg, vex::velocityUnits::dps);
   leftDriveMotors.spin(vex::directionType::fwd);
   rightDriveMotors.spin(vex::directionType::fwd);
};

void Drivebase::stop()
{
   leftDriveMotors.stop();
   rightDriveMotors.stop();
};

PIDConstants Drivebase::getPowerPID()
{
   return this->powerPID;
};

PIDConstants Drivebase::getTurningPID()
{
   return this->turnPID;
};

//---Drive Linear: COMMAND

DriveLinear::DriveLinear(Drivebase &drive, double displacement) : Command<Drivebase>(drive),
                                                                  driveRef(drive)
{
   control = new pidcontroller(driveRef.getPowerPID(), displacement);
};

void DriveLinear::start()
{
   startingPoint[0] = driveRef.get<double>("Pos_X");
   startingPoint[1] = driveRef.get<double>("Pos_Y");
   control->setLastTimestamp(Brain.Timer.time(vex::timeUnits::msec));
};

void DriveLinear::periodic()
{
   driveRef.manualDriveForward(control->calculate(getDistTraveled(), Brain.Timer.time(vex::timeUnits::msec)));
};

bool DriveLinear::isOver()
{
   return control->atSetpoint() || Controller.ButtonA.pressing();
};

void DriveLinear::end()
{
   driveRef.stop();
};

DriveLinear::~DriveLinear()
{
   delete control;
};

double DriveLinear::getDistTraveled()
{
   double currentPoint[2] = {driveRef.get<double>("Pos_X"), driveRef.get<double>("Pos_Y")};
   double xDiff = currentPoint[0] - startingPoint[0];
   double yDiff = currentPoint[1] - startingPoint[1];
   return sqrt(((xDiff * xDiff) + (yDiff * yDiff)));
};

//---Turn to Heading: COMMAND

TurnTo::TurnTo(Drivebase &drive, double degrees) : Command<Drivebase>(drive),
                                                   driveRef(drive)
{
   setpoint =  degrees;//fmod((degrees + 180),360);
   control = new pidcontroller(driveRef.getTurningPID(), 0);
};

void TurnTo::start()
{
   control->setLastTimestamp(Brain.Timer.time(vex::timeUnits::msec));
};

void TurnTo::periodic()
{
   driveRef.manualTurnClockwise(control->calculate(getError(), Brain.Timer.time(vex::timeUnits::msec)));
};

bool TurnTo::isOver()
{
   return control->atSetpoint() || Controller.ButtonA.pressing() ;
};

void TurnTo::end()
{
   driveRef.stop();
};

TurnTo::~TurnTo()
{
   delete control;
};

double TurnTo::getError()
{
   double error = fmod(setpoint - driveRef.get<double>("Angle_Degrees"), 360.0);
   if (error > 180.0)  error -= 360.0;
   if (error < -180.0) error += 360.0;
   return -error;
};

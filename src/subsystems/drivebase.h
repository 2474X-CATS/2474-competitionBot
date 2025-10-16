#ifndef __DRIVEBASE_H_
#define __DRIVEBASE_H_

#include "../architecture/subsystem.h"
#include "../architecture/command.cpp"
#include "../helpers/pidcontroller.h"

class Drivebase : public Subsystem
{
private:
  
  PIDConstants powerPID;
  PIDConstants turnPID;
  
  double startX, startY;
  double speedFactor = (1 - 0.15);

protected:
  using Subsystem::set;

public:
  using Subsystem::get;
  using Subsystem::getFromInputs;
  Drivebase(double startX, double startY) : Subsystem::Subsystem(
                                                "drivebase",
                                                {(EntrySet){"Pos_X", EntryType::DOUBLE},
                                                 (EntrySet){"Pos_Y", EntryType::DOUBLE},
                                                 (EntrySet){"Angle_Degrees", EntryType::DOUBLE}}),
                                            startX(startX), startY(startY) {};

  void init() override;
  void periodic() override;
  void updateTelemetry() override;

  void arcadeDrive(double speed, double rotation);
  void manualDriveForward(double speedMM);
  void manualTurnClockwise(double turnDeg);

  void stop();

  PIDConstants getTurningPID();

  PIDConstants getPowerPID();
};

class DriveLinear : public Command<Drivebase>
{

private:
  Drivebase &driveRef;
  pidcontroller *control = nullptr;

  double startingPoint[2];
  double getDistTraveled();

public:
  DriveLinear(Drivebase &drive, double displacement);
  ~DriveLinear() override;

  static CommandInterface *getCommand(Drivebase &drive, double displacement)
  {
    return new DriveLinear(drive, displacement);
  }

  void start() override;
  void periodic() override;
  bool isOver() override;
  void end() override;
};



class TurnTo : public Command<Drivebase>
{

private:
  Drivebase &driveRef;
  pidcontroller *control = nullptr;

  double setpoint;
  double getError();

public:
  TurnTo(Drivebase &drive, double degrees);
  ~TurnTo() override;

  static CommandInterface *getCommand(Drivebase &drive, double degrees)
  {
    return new TurnTo(drive, degrees);
  }

  void start() override;
  void periodic() override;
  bool isOver() override;
  void end() override;
};

#endif
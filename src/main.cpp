#include "vex.h"
#include "architecture/robot.h"
#include <iostream>
#include "subsystems/drivebase.h"
using namespace vex;

competition Competition;
Robot robot;

void start()
{
  robot.initialize();
  Competition.drivercontrol([]()
                            { robot.driverControl(); });
  Competition.autonomous([]()
                         { robot.autonControl(); });
  robot.runTelemetryThread(false);
}

int main()
{
  vexcodeInit();
  //------------
  Drivebase drive = Drivebase(0, 0);

  robot.setAutonomousCommand(
      {{DriveLinear::getCommand(drive, 100)}});
  //-------------

  start();
}

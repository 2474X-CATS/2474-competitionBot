#ifndef __ROBOT_H__
#define __ROBOT_H__

#include <vector>
#include "vex.h"
#include "mirror.h"
using namespace vex;
/*
  The robot brings it all together

  initialize() -> Calls Subsystems.initSystems() and [registerSystemSubtable() for miscellaneous telemetry]

  driverControl() -> Constructs a loop of Subsystem.updateSystems() that runs every 20ms

  setAutonomousCommand() -> Sets the commandGroup that is going to run in the autonomous period
  autonControl() -> Runs the autonomousCommand using CommandInterface::runCommandGroup()

  runTelemetryThread() -> Constructs a loop of Subsystem.updateTelemetry() and updateSystemSubtable() while every
  thing is happening

*/
class CommandInterface;

class Robot
{

private:
   void registerSystemSubtable();
   void updateSystemSubtable();
   //
   std::vector<CommandInterface *> autonomousCommand;
   //
   bool isActive();

   void saveFrame();
   void artificialLog();
   void rawLog();

   AbsorbtiveMirror *inputTracker = nullptr;
   ReflectiveMirror *outputLogger = nullptr;

public:
   Robot();

   void initialize();

   void driverControl(bool mirrorControlled);

   void initializeMirror(MirrorMode mode, string filename);

   void autonControl();

   void runTelemetryThread(bool showGraphics);

   void setAutonomousCommand(std::vector<CommandInterface *> comm);
};

#endif
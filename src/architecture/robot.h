#ifndef __ROBOT_H__
#define __ROBOT_H__

#include <vector> 
using std::vector; 


#include "mirror.h"


class CommandInterface;

class Robot
{

private:
   void registerSystemSubtable(); // Sets up the system data table (handling input values such as axises and buttons from both controllers)
   void updateSystemSubtable(); // Function that actually logs data to the telemetry table no matter what state it is currently in
   //
   vector<CommandInterface *> autonomousCommand;
   //
   bool isActive();

   void saveFrame(); //Logs a frame of input data to a file
   void artificialLog(); // Projects data from an input file to the telemetry table
   void rawLog(); //Projects data from the controllers to the telemetry table
   void hollowLog(); //Projects "nothing" data 0s and falses. (The robot stops) 

   void absorb(); // Logic behind 
   void reflect(); 
   void logRegular();

   AbsorbtiveMirror *inputTracker = nullptr; //Both are used ----------|  Absorbing data
   AbsorbtiveMirror *inverseInputTracker = nullptr; //At the same time--  to a file using a write stream
   
   ReflectiveMirror *outputLogger = nullptr;  // Reflect data from an input file onto the robot using a readStream
   
   bool isAttached = true; //Checks whether the robot is still listening to controller input | NOT UNDER MIRROR CONTROL

public:
   Robot();

   void initialize(); //All subsysytems in the subsystem list as a result of their instantiation are initialized here (Motor prep / sensor calibration)

   void driverControl(bool mirrorControlled); // Drive the robot using input: (Controller || File || Neither)

   void initializeMirror(MirrorMode mode, std::string filename); // Sets up input loggin or output projecting for an autonomous routine

   void autonControl(); //Runs a series of commands that have been prior set by the "setAutonomusCommand" method
   
   void stopEverything();

   void detachInput(); //Cuts off robots ability to be controlled. Only used in testing and making autos, never in real matches.

   void runTelemetryThread(bool showGraphics); //A constant loop of information logging fom the subsystems (drivebase, intake, etc),  
                                               //and the system (controller axises, buttons) happening on a different thread

   void setAutonomousCommand(vector<CommandInterface *> comm); //Sets up the autonomous command that is to be ran in autoncontrol:  
                                                                    //Like building blocks (Put one command on top of the other)
};

#endif
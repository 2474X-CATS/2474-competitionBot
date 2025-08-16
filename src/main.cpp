
#include "vex.h" 
#include "architecture/robot.h" 
#include <iostream>
#include "architecture/telemetry.h" 
#include "architecture/robotConfig.cpp"
using namespace vex;

// A global instance of competition
competition Competition;  
Robot robot;


void driverControl(){ 
  robot.driverControl();
} 

void autonControl(){ 
  robot.autonControl();
} 

//----------------For displaying telemetry data 
void displayGraphicalData(){  
  //
   //Brain.Screen.drawRectangle(0,0,100,100);
}

int main() {     
  //Competition.autonomous(autonControl); 
  //Competition.drivercontrol(driverControl);
  robot.initialize(); 
  while (true){  
    displayGraphicalData();
    robot.runTelemetry();  
    
  }
}

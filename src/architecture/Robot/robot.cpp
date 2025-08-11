#include "./robot.h" 
#include "subsystem.h" 
#include "vex.h"   
#include "telemetry.h"
using namespace vex;


void Robot::driverControl(){
    Subsystem::initSystems(); 
    while (true){ 
        Subsystem::updateSystems(this->controller); 
        this_thread::sleep_for(20);
    }
};

void Robot::telemetryUpdate(){
    Telemetry::inst.registerSubtable( 
       "system", 
       { 
        (EntrySet){"Temperature",EntryType.DOUBLE}, 
        
       }
    );
    while (true){ 
        Subsystem::refreshTelemetry();
    }
};
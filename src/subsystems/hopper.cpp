#include "vex.h"
#include "hopper.h"
// this function runs once when robot starts 

Hopper* Hopper::globalRef = nullptr; 

void Hopper::init()
{
    hopperMotor.setStopping(vex::brakeType::brake);     // makes motor hold still when stopped
    hopperMotor.setVelocity(0, vex::percentUnits::pct); // start off stopped
    set<bool>("isOn", true);                            // says the hopper is ready to go
}

// if you had a dashboard you could send data from here
void Hopper::updateTelemetry()
{
    return;
}

void Hopper::periodic()
{
    if (shouldDispenseCubes()) // Checks if you should outtake cubes from the hopper
    {
        dispenseCubes();
    }
    else if (shouldMixHopper())
    { // Checks if you should run hopper motor away from outtake
        mixHopper();
    }
    else
    {
        stop(); // Checks if you should stop the hopper motor
    }
   
}

void Hopper::dispenseCubes(){ 
    hopperMotor.setVelocity(-100, vex::percentUnits::pct); 
    hopperMotor.spin(vex::directionType::fwd);
} 

void Hopper::mixHopper(){ 
    hopperMotor.setVelocity(100, vex::percentUnits::pct); 
    hopperMotor.spin(vex::directionType::fwd);
}  

void Hopper::stop(){ 
    hopperMotor.setVelocity(0, vex::percentUnits::pct); 
    hopperMotor.spin(vex::directionType::fwd);
}


bool Hopper::shouldDispenseCubes()
{
    return getFromInputs<bool>("Controller/Button_R1") ||
           getFromInputs<bool>("Controller/Button_R2") ||
           getFromInputs<bool>("Controller/Button_RIGHT");
           //getFromInputs<bool>("Controller/Button_B");
}

bool Hopper::shouldMixHopper()
{
    return getFromInputs<bool>("Controller/Button_DOWN");
}

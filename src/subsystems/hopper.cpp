#include "vex.h"
#include "hopper.h"
// this function runs once when robot starts
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
        hopperMotor.setVelocity(-100, vex::percentUnits::pct);
    }
    else if (shouldMixHopper())
    { // Checks if you should run hopper motor away from outtake
        hopperMotor.setVelocity(100, vex::percentUnits::pct);
    }
    else
    {
        hopperMotor.setVelocity(0, vex::percentUnits::pct); // Checks if you should stop the hopper motor
    }
    hopperMotor.spin(vex::directionType::fwd);
}

bool Hopper::shouldDispenseCubes()
{
    return getFromInputs<bool>("Controller/Button_R1") ||
           getFromInputs<bool>("Controller/Button_R2") ||
           getFromInputs<bool>("Controller/Button_DOWN");
}

bool Hopper::shouldMixHopper()
{
    return getFromInputs<bool>("Controller/Button_RIGHT");
}

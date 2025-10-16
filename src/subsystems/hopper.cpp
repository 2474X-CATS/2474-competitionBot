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
    switch (getMode())
    { // checks what the driver wants to do
    case LOAD:
        // Spin the hopper forward to suck discs in
        hopperMotor.setVelocity(100, vex::percentUnits::pct);
        break;
    case UNLOAD:
        hopperMotor.setVelocity(-100, vex::percentUnits::pct); 
        break;
    case STOP:
    default:
        // stop the hopper motor when no buttons are pressed 
        hopperMotor.setVelocity(0, vex::percentUnits::pct);
        break;
    } 
    hopperMotor.spin(vex::directionType::fwd);
}

// this looks at the controller buttons and chooses the mode

HopperMode Hopper::getMode()
{
    HopperMode mode;

    // R1 button = LOAD mode
    // R2 button = UNLOAD mode
    if (getFromInputs<bool>("Controller/Button_X") || getFromInputs<bool>("Controller/Button_A") || getFromInputs<bool>("Controller/Button_B"))
    {
        mode = UNLOAD;
    } else if (getFromInputs<bool>("Controller/Button_L2")){ 
        mode = LOAD;
    } else // If no button is pressed, STOP mode
    {
        mode = STOP;
    }

    return mode;
}

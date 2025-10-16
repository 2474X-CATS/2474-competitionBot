#include "vex.h"
#include "hood.h"

void Hood::init()
{    
     // cureent hood angle to normal
    set<bool>("isOn", true); // changes entry in telmetry system (updates telemetry)
}

// if up which direction hood goes to the angle then angle chnages to that button pressed.
void Hood::periodic()
{
    if (getFromInputs<bool>("Controller/Button_X"))
    {
        currentAngle = OUT;
    }
    else if (getFromInputs<bool>("Controller/Button_L1"))
    {                      //
        currentAngle = IN; // storage aka in
    }

    switch (currentAngle)
    {
    case IN:
        // hoodMotor.setVelocity(30, vex::percentUnits::pct);
        hoodPiston.open(); // piston in
        break;
    case OUT:
        // hoodMotor.setVelocity(30, vex::percentUnits::pct);
        hoodPiston.close(); // piston out
        break; 
    case NORMAL: 
    default: 
        break;
    }
}

void Hood::updateTelemetry()
{
    return;
}

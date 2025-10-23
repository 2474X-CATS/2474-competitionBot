#include "intake.h"
#include "vex.h"

void Intake::init()
{
    set<bool>("isOn", true);
};

void Intake::periodic()
{
    if (shouldIntake())
    { // Checks if you should intake inwards
        intakeMotor.setVelocity(-100, vex::percentUnits::pct);
    }
    else if (getFromInputs<bool>("Controller/Button_Y") || getFromInputs<bool>("Controller/Button_DOWN"))
    { // Checks if you should outtake outwards
        intakeMotor.setVelocity(100, vex::percentUnits::pct);
    }
    else
    {
        intakeMotor.setVelocity(0, vex::percentUnits::pct);
    }
    intakeMotor.spin(vex::directionType::fwd);
};

void Intake::updateTelemetry()
{
    return;
}

bool Intake::shouldIntake()
{
    return getFromInputs<bool>("Controller/Button_B") ||
           getFromInputs<bool>("Controller/Button_R1") ||
           getFromInputs<bool>("Controller/Button_R2");
}

bool Intake::shouldOuttake()
{
    return getFromInputs<bool>("Controller/Button_Y") ||  
           getFromInputs<bool>("Controller/Button_DOWN");
}

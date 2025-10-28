#include "intake.h"
#include "vex.h"

void Intake::init()
{
    set<bool>("isOn", true);
};

void Intake::periodic()
{
    if (shouldIntake())
    { 
        intake();
    }
    else if (shouldOuttake())
    {
        outtake();
    }
    else
    {
        stop();
    }
    
};

void Intake::updateTelemetry()
{
    return;
}

bool Intake::shouldIntake()
{
    return getFromInputs<bool>("Controller/Button_Y") ||
           getFromInputs<bool>("Controller/Button_R1") ||
           getFromInputs<bool>("Controller/Button_R2");
}

bool Intake::shouldOuttake()
{
    return getFromInputs<bool>("Controller/Button_B") ||  
           getFromInputs<bool>("Controller/Button_RIGHT");
} 

void Intake::intake(){ 
    intakeMotor.setVelocity(-100, vex::percentUnits::pct); 
    intakeMotor.spin(vex::directionType::fwd);
}  

void Intake::outtake(){ 
    intakeMotor.setVelocity(100, vex::percentUnits::pct); 
    intakeMotor.spin(vex::directionType::fwd);
}  

void Intake::stop(){ 
    intakeMotor.setVelocity(0, vex::percentUnits::pct); 
    intakeMotor.spin(vex::directionType::fwd);
} 



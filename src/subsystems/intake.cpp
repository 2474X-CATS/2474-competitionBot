#include "intake.h"
#include "vex.h"


void Intake::init(){
    currentValue = HALT;
    set<bool>("isOn", true);
};

void Intake::periodic() {
    if (getFromInputs<bool>("Controller/Button_B") || getFromInputs<bool>("Controller/Button_R1") || getFromInputs<bool>("Controller/Button_R2")) {
        currentValue = INTAKE;
    } else if (getFromInputs<bool>("Controller/Button_DOWN")) {
        currentValue = OUTTAKE;
    } else {
        currentValue = HALT;
    }
    switch(currentValue) {
        case INTAKE: 
            intakeMotor.setVelocity(-100, vex::percentUnits::pct);
            intakeMotor.spin(vex::directionType::fwd);
            break;
        case OUTTAKE: 
            intakeMotor.setVelocity(100, vex::percentUnits::pct);
            intakeMotor.spin(vex::directionType::fwd);
            break;
        case HALT: 
            intakeMotor.stop();
            break;
        }
};

void Intake::updateTelemetry() {
    return;
}


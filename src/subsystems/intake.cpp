#include "intake.h"
#include "vex.h"


void Intake::init(){
    currentValue = HALT;
    set<bool>("isOn", true);
};

void Intake::periodic() {
    if (getFromInputs<bool>("Controller/Button_L1") || getFromInputs<bool>("Controller/Button_X") || getFromInputs<bool>("Controller/Button_A")) {
        currentValue = INTAKE;
    } else if (getFromInputs<bool>("Controller/Button_B")) {
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


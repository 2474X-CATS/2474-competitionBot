#include "intake.h"
#include "vex.h"


void Intake::init(){
    currentValue = STOP;
    set<bool>("isOn", true);
};

void Intake::periodic() {
    if (getFromInputs<bool>("Controller/Button_R1")) {
        currentValue = INTAKE;
    } else if (getFromInputs<bool>("Controller/Button_R2")) {
        currentValue = OUTTAKE;
    } else {
        currentValue = STOP;
    }
    switch(currentValue) {
        case INTAKE: 
            intakeMotor.setVelocity(100, vex::percentUnits::pct);
            intakeMotor.spin(vex::directionType::fwd);
            break;
        case OUTTAKE: 
            intakeMotor.setVelocity(-100, vex::percentUnits::pct);
            intakeMotor.spin(vex::directionType::fwd);
            break;
        case STOP: 
            intakeMotor.stop();
            break;
        }
};

void Intake::updateTelemetry() {
    return;
}


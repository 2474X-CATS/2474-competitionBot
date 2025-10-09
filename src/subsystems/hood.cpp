#include "vex.h"
#include "intake.h"

void Hood::init() {
    currentAngle = NORMAL; //cureent hood angle to normal
    set<bool>("isOn", true); // changes entry in telmetry system (updates telemetry)
    hoodMotor.stop(vex::brakeType::hold); //stops hood motor and holds its position
}

//if up which direction hood goes to the angle then angle chnages to that button pressed. 
void Hood::periodic() {
    if(getFromInputs<bool>("Controller/Button_Up")) {
        currentAngle = HIGH;
    } else if (getFromInputs<bool>("Controller/Button_Right")){ //
        currentAngle = IN;//storage aka in 
    } else if (getFromInputs<bool>("Controller/Button_Left")) {
        currentAngle = OUT; //score aka out
    }

    switch(currentAngle) {
        case IN:
            //hoodMotor.setVelocity(30, vex::percentUnits::pct);
            hoodPiston.close(); //piston in
            break;
        case OUT:
            //hoodMotor.setVelocity(30, vex::percentUnits::pct);
            hoodPiston.open(); //piston out
            break;
    }

    void Hood::updateTelemetry() {
    return;
}
}




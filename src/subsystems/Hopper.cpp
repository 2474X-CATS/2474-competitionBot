#include "vex.h"
#include "Hopper.h"
// this function runs once when robot starts
void Hopper::init() {
    hopperMotor.setStopping(vex::brake::hold); //makes motor hold still when stopped
    hopperMotor.setVelocity(0, vex::percentUnits::pct); //start off stopped
    set<bool>("isOn", true); //says the hopper is ready to go
} 

//if you had a dashboard you could send data from here
void Hopper::updateTelemetry(){
    return;
}

void Hopper::periodic(){
    switch (getMode()) {// checks what the driver wants to do
    case LOAD:
    //Spin the hopper forward to suck discs in
    hopperMotor.setVelocity(100,vex::percentUnits::pct);
    hopperMotor.spin(vex::directionType::rev);
    break;

    default
    //stop the hopper motor when no buttons are pressed
    hopperMotor.stop()
    break;
 }
}

//this looks at the controller buttons and chooses the mode
HopperMode Hopper::getMode() {
    HopperMode;
//R1 button = LOAD mode

if(getFromInputs<bool>("Controller/Button_R1")) {
    mode = LOAD;
}
//R2 button = UNLOAD mode
else if (getFromInputs<bool>("Controller/Button_R2")) {
    mode = UNLOAD;
}
// If no button is pressed, STOP mode
else {
    mode = STOP;
}

return mode;

}


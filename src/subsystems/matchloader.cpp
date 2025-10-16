#include "vex.h"
#include "matchloader.h"

// this runs once at the start of the program
void Matchloader::init() {
    matchloaderPiston.close(); //make sure the piston starts closed
    set<bool>("isOn", true); //marks it as active
}

//used if you want to send the piston data somewhere
void Matchloader::updateTelemetry(){
    return;
}

void Matchloader::periodic(){
    switch (getMode()) {
        case LOAD_DISC:
        // push the disc into the robot using the piston
        matchloaderPiston.open();
        break;

    case RELEASE_DISC:
    //pull the piston back so its ready for next time
    matchloaderPiston.close();
    break;

    default:
    //Do nothing if no button is pressed
    break;
 }
}

// this looks at the controller buttons to see what to do
MatchloaderMode Matchloader::getMode() {
    MatchloaderMode mode;

    // X buttin = push disc (extend piston)
    if (getFromInputs<bool>("Controller/Button_R2")){
        mode = LOAD_DISC;
    } else { // Y button = pull piston back (retract)
        mode = RELEASE_DISC;
    }

    return mode;
}
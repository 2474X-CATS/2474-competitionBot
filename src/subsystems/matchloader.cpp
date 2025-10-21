#include "vex.h"
#include "matchloader.h"


void Matchloader::init() {
    matchloaderPiston.close();
    set<bool>("isOn", true); 
}


void Matchloader::updateTelemetry(){
    return;
}

void Matchloader::periodic(){
    if (getFromInputs<bool>("Controller/Button_L2")){ //Checks if the matchloader should open
       matchloaderPiston.open();
    } else { 
       matchloaderPiston.close();
    }
}


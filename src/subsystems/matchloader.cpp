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
    if (shouldDeploy()){ 
       deploy();
    } else { 
       retract();
    }
} 

bool Matchloader::shouldDeploy(){ 
    return getFromInputs<bool>("Controller/Button_L2");
} 

void Matchloader::deploy(){ 
    matchloaderPiston.open();
} 

void Matchloader::retract(){ 
    matchloaderPiston.close();
} 

void Matchloader::stop(){ 
    retract();
}


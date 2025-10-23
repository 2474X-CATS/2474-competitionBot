#include "vex.h"
#include "hood.h"

void Hood::init()
{    
    set<bool>("isOn", true);
}

void Hood::periodic()
{   
    if (getFromInputs<bool>("Controller/Button_L1")){  
      holding = true;
    } else { 
      if (holding){ 
        if (hoodPiston.value() == 1) 
         hoodPiston.close();   
        else { 
         hoodPiston.open();
        } 
        holding = false; 
        return;
       } 
    } 
    if (getFromInputs<bool>("Controller/Button_B")){ 
      hoodPiston.close();
    } else if (getFromInputs<bool>("Controller/Button_R1") || getFromInputs<bool>("Controller/Button_R2")) //Checks if the hood should close towards the hopper side 
    { 
      hoodPiston.open(); 
    }
}

void Hood::updateTelemetry()
{
    return;
}

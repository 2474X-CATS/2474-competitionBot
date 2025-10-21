#include "vex.h"
#include "hood.h"

void Hood::init()
{    
    set<bool>("isOn", true);
}

void Hood::periodic()
{ 
    if (getFromInputs<bool>("Controller/Button_R1")){ //Checks if the hood should open to the scoring side
       hoodPiston.open(); 
       return;
    }  
    if (getFromInputs<bool>("Controller/Button_L1")) //Checks if the hood should close towards the hopper side 
    {  
        holding = true;
    } else { 
       if (holding){ 
          if (hoodPiston.value() == 0)  //Uses toggle logic and button *pressing* instead of *holding* 
            hoodPiston.open(); 
          else {
            hoodPiston.close();
          }  
          holding = false;
       } 
    }
}

void Hood::updateTelemetry()
{
    return;
}

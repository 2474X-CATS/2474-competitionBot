#include "vex.h"
#include "hood.h"

void Hood::init()
{    
    set<bool>("isOn", true);
}

void Hood::periodic()
{   
    if (isHolding()){  
      holding = true;
    } else {   
      if (holding){ 
        if (shouldToggleClose())
         hoodPiston.close();   
        if (shouldToggleOpen())
         hoodPiston.open(); 
        return;
      }
    }
    if (shouldClose()){ 
      hoodPiston.close();
    } else if (shouldOpen()) //Checks if the hood should close towards the hopper side 
    { 
      hoodPiston.open(); 
    }
}

bool Hood::isHolding(){ 
  return getFromInputs<bool>("Controller/Button_L1");
} 

bool Hood::shouldOpen(){ 
  return getFromInputs<bool>("Controller/Button_R1") || getFromInputs<bool>("Controller/Button_R2");
} 

bool Hood::shouldClose(){ 
  return getFromInputs<bool>("Controller/Button_B");
} 

bool Hood::shouldToggleOpen(){ 
  if (hoodPiston.value() == 0)  
    holding = false;
    return true; 
  return false;
} 

bool Hood::shouldToggleClose(){ 
  if (hoodPiston.value() == 1) 
    holding = false; 
    return true;  
  return false;
}

void Hood::updateTelemetry()
{
    return;
}

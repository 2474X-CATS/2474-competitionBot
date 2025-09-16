#include "vex.h"
#include "indexer.h"   
#include "../architecture/telemetry.h"

void Indexer::init(){  
  hoodPiston.close(); 
  set<bool>("isOn",true); 
};  

void Indexer::updateTelemetry(){ 
  return;
}; 

void Indexer::periodic(){ 
  switch (getScoringMode()){ 
     case CIRCULATE: 
       indexerMotor.setVelocity(-ABSOLUTE_INDEXER_SPEED, vex::velocityUnits::rpm); 
       hoodPiston.close();
       break; 
     case STORAGE: 
       indexerMotor.setVelocity(ABSOLUTE_INDEXER_SPEED, vex::velocityUnits::rpm);  
       hoodPiston.open(); 
       break; 
     default:   
       indexerMotor.setVelocity(0, vex::percentUnits::pct);
       break;
  }; 
  indexerMotor.spin(vex::directionType::fwd);
};

Feed Indexer::getScoringMode(){  
    /* 
      This is just to test... 
      In reality the Indexer relies on the telemetry to get when it should spin a certain way 
      Like if the channel had a mode in its telemetry that had a string value on which goal it should outtake to  
    */ 
    Feed goal; 
    if (getFromInputs<bool>("Controller/Button_A")){ 
        goal = Feed::CIRCULATE; 
    } else if (getFromInputs<bool>("Controller/Button_B")){ 
        goal = Feed::STORAGE; 
    } else { 
        goal = Feed::NONE; 
    };
    return goal;
};
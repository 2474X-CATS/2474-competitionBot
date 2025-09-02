#include "vex.h"
#include "indexer.h"   
#include "../architecture/telemetry.h"

void Indexer::init(){ 
  set<bool>("isOn",true); 
};  

void Indexer::periodic(){ 
  return;
}; 

void Indexer::updateTelemetry(){ 
  return;
}; 

void Indexer::periodic(){ 
  switch (getScoringMode()){ 
     case TOP: 
       indexerMotor.setVelocity(ABSOLUTE_INDEXER_SPEED, vex::velocityUnits::rpm);
       break; 
     case MID: 
       indexerMotor.setVelocity(ABSOLUTE_INDEXER_SPEED, vex::velocityUnits::rpm);
       break; 
     case NONE: 
       indexerMotor.setVelocity(0, vex::percentUnits::pct);
       break; 
     default:   
       indexerMotor.setVelocity(0, vex::percentUnits::pct);
       break;
  }; 
  indexerMotor.spin(vex::directionType::fwd);
};

TopGoal Indexer::getScoringMode(){  
    /* 
      This is just to test... 
      In reality the Indexer relies on the telemetry to get when it should spin a certain way 
      Like if the channel had a mode in its telemetry that had a string value on which goal it should outtake to  
    */ 
    TopGoal goal; 
    if (Controller.ButtonUp.pressing()){ 
        goal = TopGoal::TOP; 
    } else if (Controller.ButtonDown.pressing()){ 
        goal = TopGoal::MID; 
    } else { 
        goal = TopGoal::NONE; 
    };
    return goal;
};
#include "vex.h"
#include "indexer.h"   
//#include "../architecture/telemetry.h"

void Indexer::init(){  
  hoodPiston.close(); 
  set<bool>("isOn",true); 
};  

void Indexer::updateTelemetry(){ 
  return;
}; 

void Indexer::periodic(){ 
  switch (getScoringMode()){ 
     case HIGH: 
       indexerMotor.setVelocity(-ABSOLUTE_INDEXER_SPEED, vex::velocityUnits::rpm); // Indexer spins outwards toward goal
       hoodPiston.close();  
       break; 
     case MID: 
       indexerMotor.setVelocity(ABSOLUTE_INDEXER_SPEED, vex::velocityUnits::rpm);  // Indexer spins inwards from goal
       hoodPiston.open();   
       break;   
     case STORAGE: 
       indexerMotor.setVelocity(ABSOLUTE_INDEXER_SPEED, vex::velocityUnits::rpm);  // Indexer spins inwards from goal
       hoodPiston.open();   
       break;
     default:    
       indexerMotor.setVelocity(0, vex::percentUnits::pct); 
       break;
  }; 
  indexerMotor.spin(vex::directionType::fwd); 
};



Feed Indexer::getScoringMode(){  
    Feed goal; 
    if (getFromInputs<bool>("Controller/Button_A")){ 
        goal = Feed::HIGH; 
    } else if (getFromInputs<bool>("Controller/Button_B")){ 
        goal = Feed::MID; 
    } else if (getFromInputs<bool>("Controller/Button_L2")) {  
        goal = Feed::STORAGE;
    } else { 
        goal = Feed::NONE; 
    };
    return goal;
};
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
     case HIGH: 
       indexerMotor.setVelocity(-ABSOLUTE_INDEXER_SPEED, vex::velocityUnits::rpm); // Indexer spins outwards toward goal
       
       intake.setVelocity(-50 * 60, vex::velocityUnits::rpm);
       
       hoodPiston.open();  

       hopperMotor.setVelocity(50, vex::velocityUnits::rpm);
       break; 
     case MID: 
       indexerMotor.setVelocity(ABSOLUTE_INDEXER_SPEED, vex::velocityUnits::rpm);  // Indexer spins inwards from goal
       
       intake.setVelocity(-50 * 60, vex::velocityUnits::rpm);
       
       hoodPiston.close();   

       hopperMotor.setVelocity(50, vex::velocityUnits::rpm);
       break;  
     case STORAGE: 
       indexerMotor.setVelocity(-ABSOLUTE_INDEXER_SPEED, vex::velocityUnits::rpm); // Indexer spins inward from the goal 
       
       intake.setVelocity(-50 * 60, vex::velocityUnits::rpm); 
       
       hoodPiston.close();  

       hopperMotor.setVelocity(50, vex::velocityUnits::rpm);
       break;
     default:    
       // Stop everything
       indexerMotor.setVelocity(0, vex::percentUnits::pct); 

       intake.setVelocity(0, vex::velocityUnits::pct);  

       hopperMotor.setVelocity(0, vex::velocityUnits::pct);
       break;
  }; 
  indexerMotor.spin(vex::directionType::fwd); 
  intake.spin(vex::directionType::fwd);
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
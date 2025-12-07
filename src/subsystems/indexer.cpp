#include "vex.h"
#include "indexer.h"   
//#include "../architecture/telemetry.h"

void Indexer::init(){  
  hoodPiston.close(); 
  set<bool>("isOn",true); 

  colorSensor.setLight(vex::ledState::on);
};  

void Indexer::updateTelemetry(){ 
  return;
}; 

void Indexer::colorLogic(){
  if(!colorSensor.isNearObject()){
    indexerMotor.stop();  //add brake type if needed? like vex::brakeType::hold
    return;
  }

  vex::color detectedColor = colorSensor.color();

  if(detectedColor == neededColor){
    indexerMotor.setVelocity(ABSOLUTE_INDEXER_SPEED, vex::velocityUnits::rpm);  
    indexerMotor.spin(vex::directionType::fwd); 
  } else {
    indexerMotor.setVelocity(ABSOLUTE_INDEXER_SPEED, vex::velocityUnits::rpm);  
    indexerMotor.spin(vex::directionType::rev); 
  }
}

void Indexer::periodic(){ 
  switch (getScoringMode()){ 
     case HIGH: 
       indexerMotor.setVelocity(-ABSOLUTE_INDEXER_SPEED, vex::velocityUnits::rpm); // Indexer spins outwards toward goal
       hoodPiston.close();  
       indexerMotor.spin(vex::directionType::fwd);
       break; 
     case MID: 
       indexerMotor.setVelocity(ABSOLUTE_INDEXER_SPEED, vex::velocityUnits::rpm);  // Indexer spins inwards from goal
       hoodPiston.open();   
       indexerMotor.spin(vex::directionType::fwd);
       break;   
     case STORAGE: 
       indexerMotor.setVelocity(ABSOLUTE_INDEXER_SPEED, vex::velocityUnits::rpm);  // Indexer spins inwards from goal
       hoodPiston.open();  
       colorLogic();
       return;
     default:    
       indexerMotor.setVelocity(0, vex::percentUnits::pct); 
       indexerMotor.spin(vex::directionType::fwd);
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
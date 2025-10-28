#include "vex.h"
#include "indexer.h"

void Indexer::init()
{
  set<bool>("isOn", true);
};

void Indexer::updateTelemetry()
{
  return;
};

void Indexer::periodic()
{
  if (shouldSpinOver())
  {
    spinOver();
  }
  else if (shouldSpinUnder()) 
  {
    spinUnder(); 
  }
  else 
  {
    stop();
  }
  indexerMotor.spin(vex::directionType::fwd);
}; 

bool Indexer::shouldSpinOver(){ 
  return getFromInputs<bool>("Controller/Button_R2") || getFromInputs<bool>("Controller/Button_Y");
}

bool Indexer::shouldSpinUnder(){ 
  return getFromInputs<bool>("Controller/Button_R1");
} 

void Indexer::spinOver(){ 
  indexerMotor.setVelocity(-ABSOLUTE_INDEXER_SPEED, vex::velocityUnits::rpm);
} 

void Indexer::spinUnder(){ 
  indexerMotor.setVelocity(ABSOLUTE_INDEXER_SPEED, vex::velocityUnits::rpm);
} 

void Indexer::stop(){ 
  indexerMotor.setVelocity(0, vex::percentUnits::pct);
}

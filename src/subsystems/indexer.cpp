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
  if (shouldSpinOver()) // Checks if the indexer spins outwards toward goal
  {
    indexerMotor.setVelocity(-ABSOLUTE_INDEXER_SPEED, vex::velocityUnits::rpm);  
  }
  else if (shouldSpinUnder()) // Checks if the indexer spins inwards from goal
  {
    indexerMotor.setVelocity(ABSOLUTE_INDEXER_SPEED, vex::velocityUnits::rpm); 
  }
  else // Indexer stops
  {
    indexerMotor.setVelocity(0, vex::percentUnits::pct);
  }
  indexerMotor.spin(vex::directionType::fwd);
}; 

bool Indexer::shouldSpinOver(){ 
  return getFromInputs<bool>("Controller/Button_R2") || getFromInputs<bool>("Controller/Button_B");
}

bool Indexer::shouldSpinUnder(){ 
  return getFromInputs<bool>("Controller/Button_R1");
}

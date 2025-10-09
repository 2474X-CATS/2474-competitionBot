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
  switch (getScoringMode())
  {
  case HIGH:
    indexerMotor.setVelocity(-ABSOLUTE_INDEXER_SPEED, vex::velocityUnits::rpm); // Indexer spins outwards toward goal
    break;
  case MID_OR_STORAGE:
    indexerMotor.setVelocity(ABSOLUTE_INDEXER_SPEED, vex::velocityUnits::rpm); // Indexer spins inwards from goal
    break;
  case NIL_IND:
  default:
    indexerMotor.setVelocity(0, vex::percentUnits::pct);
    break;
  };
  indexerMotor.spin(vex::directionType::fwd);
};

Feed Indexer::getScoringMode()
{
  Feed goal;
  if (getFromInputs<bool>("Controller/Button_X"))
  {
    goal = Feed::HIGH;
  }
  else if (getFromInputs<bool>("Controller/Button_B"))
  {
    goal = Feed::MID_OR_STORAGE;
  }
  else
  {
    goal = Feed::NIL_IND;
  };
  return goal;
};
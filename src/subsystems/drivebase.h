#ifndef __DRIVEBASE_H_
#define __DRIVEBASE_H_

#include "../architecture/subsystem.h" 
#include "../helpers/pidcontroller.h"
#include <set>  
#include "vex.h"
//#include "../helpers/location.h"


class Drivebase : public Subsystem
{
private:
  
  PIDConstants powerPID;
  PIDConstants turnPID;
  
  double startX, startY;
  double speedFactor = 0.85;  

  bool startingFromLeft = true;

  //Location* currentLocation = nullptr; 

  

protected:
  using Subsystem::set;

public:
  using Subsystem::get;
  using Subsystem::getFromInputs;
  Drivebase(double tileX, double tileY) : Subsystem(
                                       "drivebase",
                                        {(EntrySet){"Pos_X", EntryType::DOUBLE},
                                         (EntrySet){"Pos_Y", EntryType::DOUBLE},
                                         (EntrySet){"Angle_Degrees", EntryType::DOUBLE}, 
                                         (EntrySet){"Current_Location", EntryType::STRING}
                                        }
                                    ),
                startX((tileX - 1) * TILE_SIZE_MM),  
                startY((tileY - 1) * TILE_SIZE_MM) {};

  void init() override;
  void periodic() override;
  void updateTelemetry() override;
  void stop() override;  

  void arcadeDrive(double speed, double rotation);
  void manualDriveForward(double speedMM);
  void manualTurnClockwise(double turnDeg); 
  
  void setSpeedFactor(double speedFactor); 
  
  //void updateTileCoordinates();
   
  //void updateLocations();
  
  PIDConstants getTurningPID();

  PIDConstants getPowerPID();
};

#endif
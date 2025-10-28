#ifndef __DRIVEBASE_H_
#define __DRIVEBASE_H_

#include "../architecture/subsystem.h" 
#include "../helpers/pidcontroller.h"
#include <set>  
#include "vex.h"
#include "../helpers/location.h"
/*
class Location { 
   public: 
     Location(string name, double centerX, double centerY, double zoneRadius, double perfectEntranceAngle, double angleTolerance);
     
     string getName(); 
     
     static vector<Location*>& getLocations();  
     bool isRobotVisiting(); //Is the robot facing the locations and is its heading within the angle threshold and if the two are touching
  
   
   private: 
     double centerX; 
     double centerY; 
     double zoneRadius; 
     double perfectEntranceAngle; 
     double angleTolerance;    

     string locationName;
     
     static vector<Location*>& locations; 

     
};  
*/

class Drivebase : public Subsystem
{
private:
  
  PIDConstants powerPID;
  PIDConstants turnPID;
  
  double startX, startY;
  double speedFactor = (1 - 0.15); 

  Location* currentLocation = nullptr;

  

protected:
  using Subsystem::set;

public:
  using Subsystem::get;
  using Subsystem::getFromInputs;
  Drivebase(int tileX, int tileY) : Subsystem::Subsystem(
                                                "drivebase",
                                                {(EntrySet){"Pos_X", EntryType::DOUBLE},
                                                 (EntrySet){"Pos_Y", EntryType::DOUBLE},
                                                 (EntrySet){"Angle_Degrees", EntryType::DOUBLE}, 
                                                 (EntrySet){"Current_Location", EntryType::STRING}
                                                 }
                                                ),
                                            startX((tileX - 1) * TILE_SIZE_MM), startY((tileY - 1) * TILE_SIZE_MM) {};

  void init() override;
  void periodic() override;
  void updateTelemetry() override;
  void stop() override;  

  void arcadeDrive(double speed, double rotation);
  void manualDriveForward(double speedMM);
  void manualTurnClockwise(double turnDeg);  

  void updateTileCoordinates();
   
  void updateLocations();
  
  PIDConstants getTurningPID();

  PIDConstants getPowerPID();
};

#endif
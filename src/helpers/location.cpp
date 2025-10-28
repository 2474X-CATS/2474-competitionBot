#include "location.h" 
#include "../architecture/robotConfig.h"
#include "math.h"


vector<Location *> locationsRef;
vector<Location *>& Location::locations = locationsRef;

Location::Location(string name, double centerX, double centerY, double zoneRadius, double perfectEntranceAngle, double angleTolerance) : centerX(centerX), centerY(centerY), zoneRadius(zoneRadius), perfectEntranceAngle(perfectEntranceAngle), angleTolerance(angleTolerance),
                                                                                                                                         locationName(name)
{
   Location::locations.push_back(this);
}

vector<Location *> &Location::getLocations()
{
   return locations;
}

bool Location::isRobotVisiting()
{
   double robotHeading = 90 - Telemetry::inst.getValueAt<double>("drivebase", "Angle_Degrees");
   double robotX = Telemetry::inst.getValueAt<double>("drivebase", "Pos_X");
   double robotY = Telemetry::inst.getValueAt<double>("drivebase", "Pos_Y");
   double robotToMe = (atan2((centerY - robotY), (centerX - robotX)) / M_PI * 180.0); 

   if (robotHeading < 0) 
      robotHeading += 360; 
   if (robotToMe < 0) 
      robotToMe += 360;
   
   double diff = fabs(robotToMe - robotHeading); 
   double entryDiff = fabs(robotToMe - perfectEntranceAngle); 

   if (diff > 180)
      diff = 360 - diff; 
   
   if (entryDiff > 180) 
      entryDiff = 360 - entryDiff;

   double dist = hypot(centerX - robotX, centerY - robotY);
   double derivedAngleTolerance = ((zoneRadius * M_PI) / (dist * 2 * M_PI)) * 360.0;  
   if (derivedAngleTolerance > 180) 
     derivedAngleTolerance = 180; 

   return (diff <= derivedAngleTolerance) && (entryDiff <= angleTolerance) && (dist - zoneRadius < (hypot(ROBOT_LENGTH_MM, ROBOT_WIDTH_MM) / 2));
};

string Location::getName()
{
   return locationName;
}

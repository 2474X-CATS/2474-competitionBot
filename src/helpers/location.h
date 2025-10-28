#ifndef __LOCATION_H__ 
#define __LOCATION_H__ 

#include "../architecture/telemetry.h" 

#include <string> 
using std::string; 

#include <vector> 
using std::vector; 


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

#endif
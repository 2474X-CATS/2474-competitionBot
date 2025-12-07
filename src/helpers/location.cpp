/*
#include "location.h" 
#include "../architecture/robotConfig.h"
#include "math.h"

bool Location::isRobotVisiting()
{ 

   double robotHeading = Telemetry::inst.getValueAt<double>("drivebase", "Angle_Degrees_CCW");
   double robotX = Telemetry::inst.getValueAt<double>("drivebase", "Pos_X");
   double robotY = Telemetry::inst.getValueAt<double>("drivebase", "Pos_Y");   
   
   return isRobotClose(robotX, robotY) && isRobotFacing(robotX, robotY, robotHeading) && isRobotInBounds(robotX, robotY);

};  

double Location::getX(){ 
   return centerX;
}; 

double Location::getY(){ 
   return centerY;
}; 

double Location::getRadius(){ 
   return zoneRadius;
}

bool Location::isRobotFacing(double robotX, double robotY, double robotHeading){  
   double dist = hypot(centerX - robotX, centerY - robotY); 
   double projectedX = robotX + (cos(degreesToRadians(robotHeading)) * dist);  
   double projectedY = robotY + (sin(degreesToRadians(robotHeading)) * dist); 
   return hypot(centerX - projectedX, centerY - projectedY) <= zoneRadius;
} 

bool Location::isRobotInBounds(double robotX, double robotY){ 
   double robotToMe = normalizeTrigOutput(atan2((centerX - robotX), (centerY - robotY)));  
   double minBoundRequiredAngle =  getAngleDiff(perfectEntranceAngle, (angleTolerance / 2));  
   return getAngleDiff(robotToMe, minBoundRequiredAngle) <= angleTolerance;
} 

bool Location::isRobotClose(double robotX, double robotY){ 
   return hypot(centerX - robotX, centerY - robotY) <= zoneRadius + (hypot(ROBOT_LENGTH_MM, ROBOT_WIDTH_MM) / 2);
}  

array<double, 2> Location::getProjectedSetpoint(double distFrom){  
   array<double, 2> res;  
   res[0] = centerX - cos(degreesToRadians(perfectEntranceAngle)) * distFrom;  
   res[1] = centerY - sin(degreesToRadians(perfectEntranceAngle)) * distFrom; 
   return res;
}
 
vector<double> Location::getEuclideanAlignmentPath(double distFrom){ 
  // First turn to angle 
  // Then drive to the distance  
  // repeat   

  array<double, 2> setpoint;
  setpoint = getProjectedSetpoint(distFrom);   

  double robotX = Telemetry::inst.getValueAt<double>("Drivebase","Pos_X"); 
  double robotY = Telemetry::inst.getValueAt<double>("Drivebase","Pos_Y");  
  
  double dist = hypot(robotX - setpoint[0], robotY - setpoint[1]); 
  double angle = normalizeTrigOutput(atan2(setpoint[1] - robotY, setpoint[0] - robotX));    
  double finalAngle =  getAngleSum(perfectEntranceAngle, 180); 
  
  return {angle, dist, finalAngle};

}  

vector<double> Location::getTaxicabAlignmentPath(double distFrom, bool xFirst){  
  
  array<double, 2> setpoint; 
  setpoint = getProjectedSetpoint(distFrom);

  double robotX = Telemetry::inst.getValueAt<double>("Drivebase","Pos_X"); 
  double robotY = Telemetry::inst.getValueAt<double>("Drivebase","Pos_Y");   

  double xDist = setpoint[0] - robotX; 
  double yDist = setpoint[1] - robotY; 

  double horiAngle = fmod((xDist > 0 ? 0 : 180) + 360, 360);
  double vertAngle = fmod((yDist > 0 ? 90 : 270) + 360, 360); 

  if (xFirst){   
   return {horiAngle, fabs(xDist), vertAngle, fabs(yDist)};
  } else { 
   return {vertAngle, fabs(yDist), horiAngle, fabs(xDist)}; 
  }

} 

double Location::getAngleDiff(double angle1, double angle2){ 
   double initialDiff = fabs(angle1 - angle2); 
   if (initialDiff > 180)  
      initialDiff = 360 - initialDiff; 
   return initialDiff; 
}   

double Location::getAngleSum(double angle1, double angle2){ 
   return fmod(angle1 + angle2, 360); 
}

double Location::normalizeTrigOutput(double radians){ 
   return ((radians / M_PI) * 180 + 180);
}; 

double Location::degreesToRadians(double angle){ 
    return angle / 360 * (M_PI * 2); 
}; 


string Location::getName()
{
   return locationName;
} 
*/

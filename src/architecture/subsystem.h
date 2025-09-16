#ifndef __SUBSYSTEM_H__
#define __SUBSYSTEM_H__

#include <vector>
#include <string> 
#include "telemetry.h"

/* 
//Generalizes the creation of subsystem logic 

//Ex: (You want a subsystem that handles everything "drivebase") 

class Drivebase : public Subsystem { 
   public Drivebase() : Subsystem( 
     "drivebase", 
     {  
      (EntrySet){"Pos_X", EntryType::DOUBLE}, 
      (EntrySet){"Pos_Y", EntryType::DOUBLE}, 
      (EntrySet){"Angle_Degrees", EntryType::Double}
     } 
   ) {...} 
   //This section basically creates a telemetry subtable for setting and  
   //getting of subsystem values using a descriptive name, and declaring names and  
   //types for each entry [Reference "telemetry.h"]--
   
   public void init() override { 
     //Prep drive motors, set them to brake mode
   }
   public void periodic() override{ 
     //Drive around the field using the controller
   }  
   
   public void updateTelemetry() override {  
     // Use set<T>(entryName, val) [T being a certain type (int, double, bool,...)] to 
     // update the subtable at: ["drivebase", entryName] so that it is val
   }

   //A static container for every subsystem and static methods are used to enable abstraction 

   //initSystems() -> Calls every subsystems' "init" method 
   //updateSystems() -> Calls every subsystems' "periodic" method 
   //refreshTelemetry() -> Calls every subsystems' "updateTelemetry" method 

   //Don't have to worry about those though
}

*/

class Subsystem
{
protected:
   std::string label;

   template <typename T>
   void Subsystem::set(string entryName, T val)
   {
     Telemetry::inst.placeValueAt<T>(val, this->label, entryName);
   };  


public: 
   template <typename T>
   T Subsystem::get(string entryName)
   {
     return Telemetry::inst.getValueAt<T>(this->label, entryName);
   }; 

   template <typename T>
   T Subsystem::getFromInputs(string entryName)
   {
     return Telemetry::inst.getValueAt<T>("system", entryName);
   };  
   
   static std::vector<Subsystem*> systems;

   static void initSystems();

   static void updateSystems();

   static void refreshTelemetry();

   Subsystem(std::string tableLabel, std::vector<EntrySet> entryNames);

   virtual void init() = 0;
   virtual void periodic() = 0;
   virtual void updateTelemetry() = 0;

   bool inCommand = false;
};

#endif
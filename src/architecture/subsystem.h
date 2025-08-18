#ifndef __SUBSYSTEM_H__
#define __SUBSYSTEM_H__

#include <vector>
#include <string> 
#include "telemetry.h"


class Subsystem
{
protected:
   std::string label;

   template <typename T>
   void set(std::string entryName, T val); 


public: 
   template<typename T> 
   T get(std::string entryName); 
   
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
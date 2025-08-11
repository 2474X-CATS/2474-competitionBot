#ifndef __SUBSYSTEM_H__
#define __SUBSYSTEM_H__

#include <vector>
#include <string>
#include "telemetry.h"
#include "vex.h"

class Subsystem
{
protected:
   std::string label;

   template <typename T>
   void set(std::string entryName, T val);

public:
   inline static std::vector<Subsystem *> systems;

   static void initSystems()
   {
      for (Subsystem *system : systems)
      {
         system->init();
      }
   }

   static void updateSystems(vex::controller &control)
   {
      for (Subsystem *system : systems)
      {
         system->periodic(control);
      }
   }

   static void refreshTelemetry()
   {
      for (Subsystem *system : systems)
      {
         system->updateTelemetry();
      }
   }

   Subsystem(std::string tableLabel, std::vector<EntrySet> entryNames);

   virtual void init() = 0;
   virtual void periodic(vex::controller &control) = 0;
   virtual void updateTelemetry() = 0;

   bool inCommand = false;
};

#endif
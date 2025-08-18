#include "subsystem.h"

std::vector<Subsystem*> Subsystem::systems; 

Subsystem::Subsystem(string tableLabel, vector<EntrySet> entryNames) : label(tableLabel)
{
   Subsystem::systems.push_back(this);
   Telemetry::inst.registerSubtable(this->label, entryNames);
};

template <typename T>
void Subsystem::set(string entryName, T val)
{
   Telemetry::inst.placeValueAt<T>(val, this->label, entryName);
};  

template <typename T>
T Subsystem::get(string entryName)
{
   return Telemetry::inst.getValueAt<T>(this->label, entryName);
}; 



void Subsystem::updateSystems()
{
   for (Subsystem* system : systems)
   {
      system->periodic();
   }
};

void Subsystem::initSystems()
{
   for (Subsystem* system : systems)
   {
      system->init();
   }
};

void Subsystem::refreshTelemetry()
{
   for (Subsystem* system : systems)
   {
      system->updateTelemetry();
   }
};

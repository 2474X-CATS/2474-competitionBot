#include "./subsystem.h" 

Subsystem::Subsystem(string tableLabel, vector<EntrySet> entryNames) : label(tableLabel) {  
   Subsystem::systems.push_back(this);    
   Telemetry::inst.registerSubtable(this->label, entryNames);
};

template <typename T> 
void Subsystem::set(string entryName, T val){ 
  Telemetry::inst.placeValueAt<T>(val, this->label, entryName);
};

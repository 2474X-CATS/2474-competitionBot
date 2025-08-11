#ifndef __SUBSYSTEM_H__
#define __SUBSYSTEM_H__ 

#include <vector>   
#include <string> 
#include "telemetry.h"
#include "vex.h"

class Subsystem {  
      
   public:  
     inline static std::vector<Subsystem*> systems; 

     static void initSystems(vex::controller control){ 
         for (Subsystem* system : systems){ 
            system->init(control);
         }
     }  

     static void updateSystems(vex::controller control){ 
         for (Subsystem* system : systems){ 
            system->periodic(control);
         }
     } 

     static void shutdown(){ 
         for (Subsystem* system : systems){ 
            system->disable();
         }
     }

     Subsystem(std::string tableLabel, std::vector<EntrySet> entryNames);
   
     virtual void init(vex::controller control) = 0; 
     virtual void periodic(vex::controller control) = 0; 
     virtual void disable() = 0;  
     virtual void updateTelemetry() = 0; 
     
     template<typename T>
     void set(std::string entryName, T val);
     
     bool inCommand = false;

};  


#endif
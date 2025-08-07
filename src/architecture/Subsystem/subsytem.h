#ifndef __SUBSYSTEM_H__
#define __SUBSYSTEM_H__ 

#include <vector> 

class Subsystem {  
      
   public:  
     inline static std::vector<Subsystem*> systems; 

     inline static void initSystems(){ 
         for (Subsystem* system : systems){ 
            system->init();
         }
     }  

     inline static void updateSystemsPeriodically(){ 
         for (Subsystem* system : systems){ 
            system->periodic();
         }
     } 

     inline static void shutdown(){ 
         for (Subsystem* system : systems){ 
            system->disable();
         }
     }

     Subsystem();
   
     virtual void init() = 0; 
     virtual void periodic() = 0; 
     virtual void disable() = 0;   
     
     int runningCommands = 0;

};  


#endif
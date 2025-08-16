#ifndef __CHANNEL_H_ 
#define __CHANNEL_H_  

#include "../architecture/subsystem.h"    

typedef enum { 
    HIGH, 
    LOW_HIGH, 
    LOW_LOW 
} ScoringLevel; 

class Channel : public Subsystem {    
    public:    
       Channel() : Subsystem( 
        "channel",
         { 
            (EntrySet){"Outtake_Position", EntryType::STRING}
         }
       ){};

       void outtake(ScoringLevel level);     

       void intake();

       void init() override; 

       void periodic() override; 

       void updateTelemetry() override; 
    
};

















































#endif
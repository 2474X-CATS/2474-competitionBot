#ifndef __HOPPER_H__
#define __HOPPER_H__

#include "../architecture/subsystem.h"

class Hopper : public Subsystem
{
public:
    using Subsystem ::get;
    using Subsystem ::getFromInputs;
   
    Hopper() : Subsystem(
                   "hopper",
                   {(EntrySet){"isOn", EntryType::BOOL}} 
               )
    {
    }
   
    void init() override;           
    void periodic() override;       
    void updateTelemetry() override; 
    void stop() override;

    void dispenseCubes(); 
    void mixHopper();  

private:  
    bool shouldDispenseCubes();  
    bool shouldMixHopper();  

    // this figures out what the driver wants the hopper to do
   
};

#endif

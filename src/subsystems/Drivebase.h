#ifndef __DRIVEBASE_H_ 
#define __DRIVEBASE_H_   

#include "../architecture/subsystem.h"

class Drivebase : public Subsystem {     
    public:    
       Drivebase() : Subsystem( 
        "drivebase",
         { 
            (EntrySet){"Pos_X", EntryType::DOUBLE}, 
            (EntrySet){"Pos_Y",EntryType::DOUBLE}
         }
       ){};
    
       void init() override; 

       void periodic() override; 

       void updateTelemetry() override;  

       void arcadeDrive(double speed, double rotation); 

    
};
















































#endif
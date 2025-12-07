#ifndef __INDEXER_H__
#define __INDEXER_H__

#include "../architecture/subsystem.h"
#include "../architecture/command.h"
#include "vex.h"

typedef enum { 
   HIGH, 
   MID,  
   STORAGE,
   NONE
} Feed; 

class Indexer : public Subsystem
{ 
public: 
    using Subsystem::get;  
    using Subsystem::getFromInputs;

    Indexer() : Subsystem(
                    "indexer",
                    {(EntrySet){"isOn", EntryType::BOOL}
                    }) {}  
    void init() override; 
    void periodic() override; 
    void updateTelemetry() override;  

protected: 
   using Subsystem::set;
    
private:   
   Feed getScoringMode();

   vex::optical colorSensor{vex::PORT##}; // add port number
   vex:color neededColor = vex::color::COLOR; // add color name
   void colorLogic(); // helper function 
};

#endif
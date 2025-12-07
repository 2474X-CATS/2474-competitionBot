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
   
   static Indexer* globalRef; 

   Indexer() : Subsystem(
                   "indexer",
                   {(EntrySet){"isOn", EntryType::BOOL}}) { 
                     globalRef = this;
                   }
   void init() override;
   void periodic() override;
   void updateTelemetry() override; 
   void stop() override; 

   void spinOver(); 
   void spinUnder();

protected:
   using Subsystem::set; 
private: 
   bool shouldSpinOver(); 
   bool shouldSpinUnder(); 

protected: 
   using Subsystem::set;
    
private:   
   Feed getScoringMode();

   vex::optical colorSensor{vex::PORT##}; // add port number
   vex:color neededColor = vex::color::COLOR; // add color name
   void colorLogic(); // helper function 
};

#endif
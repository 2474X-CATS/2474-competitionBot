#ifndef __INDEXER_H__
#define __INDEXER_H__

#include "../architecture/subsystem.h"
#include "../architecture/command.h"

typedef enum { 
   STORAGE, 
   CIRCULATE, 
   NONE
} Feed;

class Indexer : public Subsystem
{ 
public: 
    using Subsystem::get; 

    Indexer() : Subsystem(
                    "indexer",
                    {(EntrySet){"isOn", EntryType::BOOL}}) {}  
    void init() override; 
    void periodic() override; 
    void updateTelemetry() override;  

protected: 
   using Subsystem::set;
    
private:   
   Feed getScoringMode();
};

#endif
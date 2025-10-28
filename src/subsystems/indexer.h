#ifndef __INDEXER_H__
#define __INDEXER_H__

#include "../architecture/subsystem.h"


class Indexer : public Subsystem
{
public:
   using Subsystem::get;
   using Subsystem::getFromInputs;

   Indexer() : Subsystem(
                   "indexer",
                   {(EntrySet){"isOn", EntryType::BOOL}}) {}
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

};

#endif
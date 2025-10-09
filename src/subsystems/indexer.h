#ifndef __INDEXER_H__
#define __INDEXER_H__

#include "../architecture/subsystem.h"
// #include "../architecture/command.h"

typedef enum
{
   HIGH,
   MID_OR_STORAGE,
   NIL_IND
} Feed;

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

protected:
   using Subsystem::set;

private:
   Feed getScoringMode();
};

#endif
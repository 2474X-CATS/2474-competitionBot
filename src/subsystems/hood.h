#ifndef _HOOD_H_
#define _HOOD_H_

#include "../architecture/subsystem.h"
#include "../architecture/command.cpp"
#include "vex.h"

// hood positions
typedef enum
{
    NORMAL,
    OUT,
    IN
} HoodAngle;

class Hood : public Subsystem
{
public:
    using Subsystem::get;
    using Subsystem::getFromInputs;
    

    Hood() : Subsystem(
                 "hood",
                 {(EntrySet){"isOn", EntryType::BOOL}}) {} 

    void init() override;
    void periodic() override;
    void updateTelemetry() override;
protected: 
    using Subsystem::set;
private: 
    HoodAngle currentAngle = IN; //default position
};

#endif
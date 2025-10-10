#ifndef _HOOD_H_
#define _HOOD_H_

#include "../architecture/subsystem.h"
#include "../architecture/command.h"
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
    using Subsystem::set;

    Hood() : Subsystem(
                 "hood",
                 {(EntrySet){"isOn", EntryType::BOOL}}) {}
    void init() override;
    void periodic() override;
    void updateTelemetry() override;

private:
    HoodAngle currentAngle = IN; //default position
};

#endif
#define _HOOD_H_

#include "../architecture/subsystem.h"
#include "../architecture/command.h"
#include "vex.h"

//hood positions
typedef enum{
    NORMAL,
    LOW,
    MID,
    HIGH
} HoodAngle;

class Hood : public Subsystem {
public:
    using Subsystem::get;
    using Subsystem::set;
    using Subsystem::getFromInputs;

    Hood() : Subsystem(
                    "hood",
                    {(EntrySet){"isOn", EntryType::BOOL}
                    }) {}
    void init() override;
    void periodic() override;
    void updateTelemetry() override;
    
private:
    HoodAngle currentAngle = NORMAL; //defult position 
};

#endif
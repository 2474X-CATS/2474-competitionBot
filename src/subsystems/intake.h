#define _INTAKE_H_
#include "../architecture/subsystem.h"
#include "../architecture/command.h"
#include "vex.h"

//options for intake movements
typedef enum { 
   INTAKE, 
   OUTTAKE,  
   STOP,
} IntakeValue;

class Intake : public Subsystem {
public: 
    using Subsystem::get;  
    using Subsystem::getFromInputs;

    Intake() : Subsystem(
                    "intake",
                    {(EntrySet){"isOn", EntryType::BOOL}
                    }) {}  
    void init() override; 
    void periodic() override; 
    void updateTelemetry() override;

private:
    IntakeValue currentValue; //defult position

    //include port number and gear ratio
    vex::motor intakeMotor = vex::motor(vex::PORT18, false);
};

#endif

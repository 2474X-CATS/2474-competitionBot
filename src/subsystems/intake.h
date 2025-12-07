#ifndef _INTAKE_H_
#define _INTAKE_H_
#include "../architecture/subsystem.h"

#include "vex.h"


class Intake : public Subsystem {
public: 
    using Subsystem::get;  
    using Subsystem::getFromInputs; 

    static Intake* globalRef; 

    Intake() : Subsystem(
                    "intake",
                    {(EntrySet){"isOn", EntryType::BOOL}
                    }) { 
                        globalRef = this;
                    }  
    void init() override; 
    void periodic() override; 
    void updateTelemetry() override;
    void stop() override; 

    void intake(); 
    void outtake();  

private: 
    bool shouldIntake(); 
    bool shouldOuttake();   
    
};

#endif

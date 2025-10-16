#ifndef __HOPPER_H__
#define __HOPPER_H__

#include "../architecture/subsystem.h"
#include "../architecture/command.cpp"

// These are different things the hopper can do

typedef enum
{
    LOAD,   // hopper takes discs into robot
    UNLOAD, // hopper pushes discs out
    STOP,   // hopper does nothing
} HopperMode;

// the hopper class controls the hopper motor

class Hopper : public Subsystem
{
public:
    using Subsystem ::get;
    using Subsystem ::getFromInputs;
    // thia creates a new "hopper" subsystem that we can use in code
    Hopper() : Subsystem(
                   "hopper",
                   {(EntrySet){"isOn", EntryType::BOOL}} // keeps track if hopper is on or off
               )
    {
    }
    // these three functions are called during the robot program
    void init() override;            // runs one time wehn the program starts
    void periodic() override;        // runs over and over during driver control or autonomous
    void updateTelemetry() override; // used if you want to send info to a dashboard

private:
    // this figures out what the driver wants the hopper to do
    HopperMode getMode();
};

#endif

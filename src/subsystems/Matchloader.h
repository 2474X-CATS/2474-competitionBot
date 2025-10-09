#ifndef __MATCHLOADER_H__
#define __MATCHLOADER_H__


#include "../architecture/subsystem.h"
#include "../architecture/command.h"

//These are the different modes the match loader can be in
typedef enum {
    LOAD_DISC, // pushed a disc into robot
    RELEASE_DISC, //Pulls the prison back in
    IDLE //Does nothing
} MatchloaderMode;

// The matchloader class controls the piston that loads discs
class Matchloader : public Subsystem {
public:
    using Subsystem::get;
    using Subsystem:: getFromInputs;

    Matchloader() : Subsystem(
        "matchloader".
        {(EntrySet){"isOn", EntryType::BOOL}}
    ) {}

    void init() override; //Sets up the matchloader
    void periodic() override; //Runs repeatedly while robot is on
    void updateTelemetry() override;//Sends info to dashboard

private:
    using Subsystem::set;
    MatchloaderMode getMode(); //cehcks what button the driver pressed
};

#endif
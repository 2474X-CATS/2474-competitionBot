#include "robot.h"
#include "subsystem.h"
#include "vex.h"
#include "telemetry.h"
#include "command.h"  
#include "robotConfig.cpp"


void Robot::driverControl()
{
    Subsystem::initSystems();
    while (true)
    { 
        Subsystem::updateSystems();
        vex::this_thread::sleep_for(20);
    }
};

void Robot::initialize()
{
    registerSystemSubtable();
    Subsystem::initSystems();
};


void Robot::autonControl()
{
    ICommand::runCommandGroup(Robot::autonomousCommand); 
};

void Robot::registerSystemSubtable()
{ 
    Telemetry::inst.registerSubtable(
        "system",
        {
            //(EntrySet){"Battery/Temperature", EntryType::DOUBLE},
            //(EntrySet){"Battery/Voltage", EntryType::DOUBLE},
            //(EntrySet){"Battery/Current", EntryType::DOUBLE},
            (EntrySet){"Controller/Axis-Vert-Left", EntryType::INT},
            (EntrySet){"Controller/Axis-Hori-Left", EntryType::INT},
            (EntrySet){"Controller/Axis-Vert-Right", EntryType::INT},
            (EntrySet){"Controller/Axis-Hori-Right", EntryType::INT},
            (EntrySet){"Controller/Button_A", EntryType::BOOL},
            (EntrySet){"Controller/Button_B", EntryType::BOOL},
            (EntrySet){"Controller/Button_X", EntryType::BOOL},
            (EntrySet){"Controller/Button_Y", EntryType::BOOL},
            (EntrySet){"Controller/Button_DOWN", EntryType::BOOL},
            (EntrySet){"Controller/Button_UP", EntryType::BOOL},
            (EntrySet){"Controller/Button_LEFT", EntryType::BOOL},
            (EntrySet){"Controller/Button_RIGHT", EntryType::BOOL},
            (EntrySet){"Controller/Button_L1", EntryType::BOOL},
            (EntrySet){"Controller/Button_L2", EntryType::BOOL},
            (EntrySet){"Controller/Button_R1", EntryType::BOOL},
            (EntrySet){"Controller/Button_R2", EntryType::BOOL},
        });
};

void Robot::updateSystemSubtable()
{ 
    //Telemetry::inst.placeValueAt<double>(Brain.Battery.temperature(), "system", "Battery/Temperature");
    //Telemetry::inst.placeValueAt<double>(Brain.Battery.voltage(), "system", "Battery/Voltage");
    //Telemetry::inst.placeValueAt<double>(Brain.Battery.current(), "system", "Battery/Current");
    Telemetry::inst.placeValueAt<int>(Controller.Axis3.position(), "system", "Controller/Axis-Vert-Left");
    Telemetry::inst.placeValueAt<int>(Controller.Axis4.position(), "system", "Controller/Axis-Hori-Left");
    Telemetry::inst.placeValueAt<int>(Controller.Axis2.position(), "system", "Controller/Axis-Vert-Right");
    Telemetry::inst.placeValueAt<int>(Controller.Axis1.position(), "system", "Controller/Axis-Hori-Right");
    Telemetry::inst.placeValueAt<bool>(Controller.ButtonA.pressing(), "system", "Controller/Button_A");
    Telemetry::inst.placeValueAt<bool>(Controller.ButtonB.pressing(), "system", "Controller/Button_B");
    Telemetry::inst.placeValueAt<bool>(Controller.ButtonX.pressing(), "system", "Controller/Button_X");
    Telemetry::inst.placeValueAt<bool>(Controller.ButtonY.pressing(), "system", "Controller/Button_Y");
    Telemetry::inst.placeValueAt<bool>(Controller.ButtonDown.pressing(), "system", "Controller/Button_DOWN");
    Telemetry::inst.placeValueAt<bool>(Controller.ButtonUp.pressing(), "system", "Controller/Button_UP");
    Telemetry::inst.placeValueAt<bool>(Controller.ButtonLeft.pressing(), "system", "Controller/Button_LEFT");
    Telemetry::inst.placeValueAt<bool>(Controller.ButtonRight.pressing(), "system", "Controller/Button_RIGHT");
    Telemetry::inst.placeValueAt<bool>(Controller.ButtonL1.pressing(), "system", "Controller/Button_L1");
    Telemetry::inst.placeValueAt<bool>(Controller.ButtonL2.pressing(), "system", "Controller/Button_L2");
    Telemetry::inst.placeValueAt<bool>(Controller.ButtonR1.pressing(), "system", "Controller/Button_R1");
    Telemetry::inst.placeValueAt<bool>(Controller.ButtonR2.pressing(), "system", "Controller/Button_R2");
};


void Robot::runTelemetry()
{
    while (true)
    {
        updateSystemSubtable();
        Subsystem::refreshTelemetry();
        vex::this_thread::sleep_for(20);
    }
};
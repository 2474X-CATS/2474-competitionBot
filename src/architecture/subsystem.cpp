#include "subsystem.h"
#include "vex.h"

vector<Subsystem *> Subsystem::systems;

Subsystem::Subsystem(string tableLabel, vector<EntrySet> entryNames) : label(tableLabel)
{
   Subsystem::systems.push_back(this);
   Telemetry::inst.registerSubtable(this->label, entryNames);
};

void Subsystem::updateSystems()
{
   for (Subsystem *system : systems)
   {
      system->periodic();
   }
};

void Subsystem::initSystems()
{
   for (Subsystem *system : systems)
   {
      system->init();
   }
};

void Subsystem::refreshTelemetry()
{
   for (Subsystem *system : systems)
   {
      system->updateTelemetry();
   }
};

void Subsystem::stopAll()
{
   for (Subsystem *system : systems)
   {
      system->stop();
   }
};

Subsystem *Subsystem::getSubsystem(int index)
{
   return systems.at(index);
}

//----------------------------------------------------------------------

vex::controller Controller = vex::controller(vex::controllerType::primary);

bool RobotState::axisesEnabled = false;
ControlType RobotState::mode = ControlType::INITIALIZATION; 

string RobotState::vibrationCode = ":)";  

void RobotState::updateState()
{
   switch (mode)
   {
   case DRIVER:
      updateRegular();
      break;
   case STOPPED:
      updateStopped();
      break;  
   case INITIALIZATION: 
      updateInitializing(); 
      break;
   case MANUAL:
   default:
      break;
   }
};

void RobotState::initializeState()
{
   Telemetry::inst.registerSubtable(
       "robot_state",
       {    
        (EntrySet){"is_team_color_blue", EntryType::BOOL},  
        (EntrySet){"color_sensitive", EntryType::BOOL},   
        (EntrySet){"ready", EntryType::BOOL},  
        (EntrySet){"in_autonomous", EntryType::BOOL},  
        (EntrySet){"is_counterclockwise", EntryType::BOOL},   
        (EntrySet){"in_skills", EntryType::BOOL},  
        
        (EntrySet){"calibrating", EntryType::BOOL},  
        (EntrySet){"k_calibrating", EntryType::BOOL},

        (EntrySet){"scoring_high", EntryType::BOOL},
        (EntrySet){"scoring_mid", EntryType::BOOL},
        (EntrySet){"scoring_low", EntryType::BOOL},  
        (EntrySet){"matchloader_out", EntryType::BOOL},
        (EntrySet){"descore_in", EntryType::BOOL},   
        (EntrySet){"outtaking", EntryType::BOOL},
        (EntrySet){"intaking", EntryType::BOOL},  
      
        (EntrySet){"launch_trigger", EntryType::BOOL}, 
        
        (EntrySet){"k_lowered", EntryType::BOOL}, 
        (EntrySet){"lowered", EntryType::BOOL},

        (EntrySet){"k_inversion_held", EntryType::BOOL},
        (EntrySet){"is_drive_inverted", EntryType::BOOL}, 
      });
}

void RobotState::updateRegular()
{    
   manuallyModifyState("scoring_high", Controller.ButtonR2.pressing()); 
   manuallyModifyState("scoring_mid", Controller.ButtonR1.pressing());
   manuallyModifyState("scoring_low", Controller.ButtonRight.pressing());  

   manuallyModifyState("intaking", Controller.ButtonY.pressing()); 
   
   if (Controller.ButtonUp.pressing()){ 
      manuallyModifyState("k_inversion_held", true);  
   } else { 
      if (getStateOf("k_inversion_held")){ 
         manuallyModifyState("k_inversion_held", false); 
         manuallyModifyState("is_drive_inverted", !getStateOf("is_drive_inverted")); 
      }
   } 
   
   if (Controller.ButtonLeft.pressing()){ 
      manuallyModifyState("k_lowered", true);  
   } else { 
      if (getStateOf("k_lowered")){ 
         manuallyModifyState("k_lowered", false); 
         manuallyModifyState("lowered", !getStateOf("lowered"));
      }
   }

   
   manuallyModifyState("launch_trigger", Controller.ButtonR2.pressing() && (!getExternalState("catapult","active")));

   manuallyModifyState("outtaking", Controller.ButtonDown.pressing()); 
   manuallyModifyState("descore_in", Controller.ButtonL1.pressing()); 
   manuallyModifyState("matchloader_out", Controller.ButtonL2.pressing());    
  
    
}

void RobotState::updateStopped()
{    

   manuallyModifyState("scoring_high", false); 
   manuallyModifyState("scoring_mid", false);
   manuallyModifyState("scoring_low", false);  
   manuallyModifyState("matchloader_out", false); 
   manuallyModifyState("k_inversion_held", false);    
   manuallyModifyState("descore_in", false); 
   manuallyModifyState("intaking", false);   
   manuallyModifyState("outtaking", false); 
   manuallyModifyState("launch_trigger", false);

}; 

void RobotState::updateInitializing(){ 
   return;
}

bool RobotState::getStateOf(string key)
{
   return Telemetry::inst.getValueAt<bool>("robot_state", key);
};

bool RobotState::getExternalState(string subtable, string key){ 
   return Telemetry::inst.getValueAt<bool>(subtable, key);
};

void RobotState::vibrate(){  
   if (vibrationCode != ":)")
      Controller.rumble(vibrationCode.c_str());
}; 

void RobotState::setVibrationCode(string code){ 
   vibrationCode = code;
}; 

void RobotState::disableVibrations(){ 
   vibrationCode = ":)";
}

int RobotState::getAxisState(AxisType axisType)
{
   int axisVal = 0;
   if (axisesEnabled)
   {
      switch (axisType)
      {
      case LEFT_HORIZONTAL:
         axisVal = Controller.Axis4.position();
         break;
      case LEFT_VERTICAL:
         axisVal = Controller.Axis3.position();
         break;
      case RIGHT_HORIZONTAL:
         axisVal = Controller.Axis1.position();
         break;
      case RIGHT_VERTICAL:
         axisVal = Controller.Axis2.position();
         break;
      }
   }
   return axisVal;
};

void RobotState::setMode(ControlType mod)
{
   mode = mod;
   updateStopped();
   if (mode == ControlType::DRIVER)
      axisesEnabled = true;
   else
   {
      axisesEnabled = false;
   };
};

void RobotState::manuallyModifyState(string key, bool val)
{
   Telemetry::inst.placeValueAt<bool>(val, "robot_state", key);
};

DummySystem GLOBAL_DUMMY;

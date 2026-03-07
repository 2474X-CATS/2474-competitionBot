#include "catapult.h" 

Catapult *Catapult::globalRef = nullptr; 

double Catapult::MAXIMUM_LEVER_ANGLE_DEG = 180; 
double Catapult::STARTING_ANGLE_DEG = 0; 
double Catapult::DISTANCE_THRESHOLD_CM = 3;
double Catapult::LAUNCH_DELAY_MS = 250; 

Catapult::Catapult() : Subsystem(  
                            "catapult", {  
                                (EntrySet){"lowered", EntryType::BOOL},
                                (EntrySet){"queued_blocks", EntryType::INT}, //How many blocks do we outtake
                                (EntrySet){"highest_sensed_block", EntryType::INT}, //How far up the closest block is
                                (EntrySet){"lever_angle", EntryType::DOUBLE}, //Current angle of the lever
                                (EntrySet){"elevated", EntryType::BOOL}, //Is the lever not idle
                                (EntrySet){"active", EntryType::BOOL}, //Is the lever currently moving
                                (EntrySet){"reference_angle", EntryType::DOUBLE}, //The angle we want to go to  
                                (EntrySet){"last_triggered", EntryType::DOUBLE} //When the launch was requested 
                            }
                       ){ 
      globalRef = this;  
      
      leverActuator = vex::motor(vex::PORT3);   
      leverActuator.setBrake(vex::brakeType::hold);

      spotArray[0] = vex::distance(vex::PORT16);  
      spotArray[1] = vex::distance(vex::PORT17);  
      spotArray[2] = vex::distance(vex::PORT18);  
      spotArray[3] = vex::distance(vex::PORT19);  
      spotArray[4] = vex::distance(vex::PORT15);  
      spotArray[5] = vex::distance(vex::PORT13);   

      stateSwitcher = vex::pneumatics(Brain.ThreeWirePort.G);  
      leverLid = vex::pneumatics(Brain.ThreeWirePort.D);

      motionConsts.P = 0.1; 
      motionConsts.I = 0; 
      motionConsts.D = 0; 
      motionConsts.errorTolerance = 1;   

      controller = new pidcontroller(motionConsts, 0); 

      set<double>("last_triggered", -1);
}

void Catapult::init(){ 
   set<bool>("is_on", true);     
   stop(); 
}  

void Catapult::periodic(){  
   if (get<bool>("active")){  
      leverLid.open();  //The lid automatically opens 

      if (Brain.Timer.time() - get<double>("last_triggered") > LAUNCH_DELAY_MS){ 
         rotate();//Have to wait to rotate so we make sure the lid is opened all the way
      } 

   } else {  

      leverActuator.stop(); //Have the lever holds its position
      leverLid.close(); //Close the lid immediately after scoring
      
      if ((!get<bool>("elevated"))){ //Only modify the lowered state when we aren't active for safety
         if (RobotState::getStateOf("lowered")){ 
            stateSwitcher.close();
         } else { 
            stateSwitcher.open();
         }
      } 
      
   }   

} 

void Catapult::updateTelemetry(){   

   set<double>("lever_angle", leverActuator.position(vex::rotationUnits::deg));   

   for (int i = 5; i >= 0; i --){ 
      if (spotArray[i].objectDistance(vex::distanceUnits::cm) <= DISTANCE_THRESHOLD_CM){ 
         set<int>("highest_sensed_block", i + 1); 
         break;
      }
   } 

   set<bool>("elevated", get<bool>("active") || get<double>("reference_angle") != STARTING_ANGLE_DEG); 
   
   if (get<bool>("active")){  

      if (controller->atSetpoint(calculateAngularError())){    

         if (get<double>("reference_angle") == MAXIMUM_LEVER_ANGLE_DEG){  

            set<double>("reference_angle", STARTING_ANGLE_DEG); 
            controller->reset();   
            controller->setLastTimestamp(Brain.Timer.time()); 

         } else {  

            set<bool>("active", false);  

         }
      }

   } else if (RobotState::getStateOf("launch_trigger")){  

      double projectedAngle = calculateLaunchAngle();  

      set<double>("reference_angle", projectedAngle); 
      controller->reset();  
      controller->setLastTimestamp(Brain.Timer.time());

      set<bool>("active", true);  

      RobotState::manuallyModifyState("launch_trigger", false);
      
      set<double>("last_triggered", Brain.Timer.time());
   }  

} 

double Catapult::calculateLaunchAngle(){ 
    return 0.0; 
} 

void Catapult::rotate(){ 
    leverActuator.setVelocity(controller->calculate(calculateAngularError())/50, vex::velocityUnits::dps); 
}  

double Catapult::calculateAngularError(){  

    double currentAngle = get<double>("lever_angle");   
    double angleSetpoint = get<double>("reference_angle"); 
    double dist = angleSetpoint - currentAngle;  

    if (dist > 180){  
        dist = -(360 - dist);
    } else if (dist < -180){ 
        dist = (360 + dist);
    } 

    return dist;
}

void Catapult::stop(){  
   //The catapult only reacts if it is active so if the lever isn't active it will stop on its own
   return;
}
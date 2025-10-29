#include "commands.h" 

//////////////////////////////////////////////////////////// 
void DriveForwardBy::start(){  
    driveRef.setSpeedFactor(1);
    startingPoint[0] = driveRef.get<double>("Pos_X"); 
    startingPoint[1] = driveRef.get<double>("Pos_Y");  
    control->setLastTimestamp(Brain.Timer.time());  
};

void DriveForwardBy::periodic(){ 
    double output = control->calculate(getDistTraveled(), Brain.Timer.time()); 
    output = goingForward ? output : -output; 
    driveRef.manualDriveForward(output); 
}; 

bool DriveForwardBy::isOver(){ 
    return control->atSetpoint();
};

void DriveForwardBy::end(){ 
    driveRef.stop(); 
    driveRef.setSpeedFactor(0.85); 
}; 

double DriveForwardBy::getDistTraveled(){ 
    return hypot(driveRef.get<double>("Pos_X") - startingPoint[0], driveRef.get<double>("Pos_Y") - startingPoint[1]); 
};

//////////////////////////////////////////////////////////// 

void TurnToHeading::start(){ 
   double angularDifference = fabs(angleSetpoint - driveRef.get<double>("Angle_Degrees"));  
   isClockwise = true;
   if (angularDifference > 180) 
       isClockwise = false; 
   control->setLastTimestamp(Brain.Timer.time());
};

void TurnToHeading::periodic(){ 
    double output = control->calculate(getAngluarDifference(), Brain.Timer.time()); 
    output = isClockwise ? output : -output; 
    driveRef.manualTurnClockwise(output);
};

bool TurnToHeading::isOver(){ 
    return control->atSetpoint();
}; 

void TurnToHeading::end(){ 
    driveRef.stop();  
};

double TurnToHeading::getAngluarDifference(){ 
   double dist = fabs(angleSetpoint - driveRef.get<double>("Angle_Degrees")); 
   if (dist > 180) 
     dist = 360 - dist; 
   return dist;
};

////////////////////////////////////////////////////////////  

void IntakeToHopper::start(){ 
   hoodRef.close(); 
   startingTime = Brain.Timer.time(vex::msec); 
};  

void IntakeToHopper::periodic(){ 
  intakeRef.intake(); 
  indexerRef.spinOver();
};  

bool IntakeToHopper::isOver(){ 
    return Brain.Timer.time(vex::msec) - startingTime >= timeDuration;
} 

void IntakeToHopper::end(){ 
    intakeRef.stop(); 
    indexerRef.stop(); 
    hoodRef.stop();
} 


////////////////////////////////////////////////////////////  

void ScoreOnGoal::start(){ 
   //Top: 1 
   //Mid: 2 
   //Low: 3 
   if (goal == 1)  
     hoodRef.open();  
   hopperRef.dispenseCubes();
   startingTime = Brain.Timer.time(); 
} 

void ScoreOnGoal::periodic(){   
    hopperRef.dispenseCubes(); 
    if (goal != 3){ 
        intakeRef.intake(); 
        if (goal == 1) 
            indexerRef.spinOver();
        else { 
            indexerRef.spinUnder();
        }
    } else { 
        intakeRef.outtake();
    } 
} 

bool ScoreOnGoal::isOver(){ 
    return Brain.Timer.time() - startingTime >= timeDuration; 
} 

void ScoreOnGoal::end(){ 
    intakeRef.stop(); 
    indexerRef.stop(); 
    hopperMotor.stop();  
    Brain.Screen.print("Ending"); 
    Brain.Screen.newLine();
} 



////////////////////////////////////////////////////////////   

void DeployMatchloader::start(){  
    if (isOut) 
       matchLoaderRef.deploy();
    else { 
       matchLoaderRef.retract();
    }
} 

void DeployMatchloader::periodic(){
    return;
} 

bool DeployMatchloader::isOver(){ 
    return true; 
}

void DeployMatchloader::end(){ 
    return;
}   

////////////////////////////////////////////////////////////    

void WaitFor::start(){ 
    startTime = Brain.Timer.time(); 
} 

void WaitFor::periodic(){ 
    return;
} 

bool WaitFor::isOver(){ 
    return Brain.Timer.time() - startTime >= timeDuration;
} 

void WaitFor::end(){ 
    return;
}



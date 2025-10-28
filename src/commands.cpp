#include "commands.h" 

//////////////////////////////////////////////////////////// 

void DriveLinear::start(){ 
   startingPoint[0] = driveRef.get<double>("Pos_X");
   startingPoint[1] = driveRef.get<double>("Pos_Y");
   control->setLastTimestamp(Brain.Timer.time(vex::timeUnits::msec));
}; 

void DriveLinear::periodic(){ 
   driveRef.manualDriveForward(control->calculate(getDistTraveled(), Brain.Timer.time(vex::timeUnits::msec)));
}; 

bool DriveLinear::isOver(){ 
   return control->atSetpoint(); 
};

void DriveLinear::end(){ 
   driveRef.stop();
}; 

double DriveLinear::getDistTraveled(){ 
   double currentPoint[2] = {driveRef.get<double>("Pos_X"), driveRef.get<double>("Pos_Y")};
   return hypot(currentPoint[0] - startingPoint[0], currentPoint[1] - startingPoint[1]);
};

DriveLinear::~DriveLinear(){ 
    delete control;
}

//////////////////////////////////////////////////////////// 

void TurnToHeading::start(){ 
   isClockwise = true;
   angularDifference = fabs(setpoint - driveRef.get<double>("Angle_Degrees"));
   if (angularDifference > 180)
   {
      angularDifference = 360 - angularDifference;
      isClockwise = false;
   }  
   control->setLastTimestamp(Brain.Timer.time(vex::timeUnits::msec));
   startingAngle = driveRef.get<double>("Angle_Degrees");
}; 

void TurnToHeading::periodic(){ 
   double output = control->calculate(getDistToSpin(), Brain.Timer.time(vex::timeUnits::msec));
   output = !isClockwise ? output * -1 : output; 
   driveRef.manualTurnClockwise(output);   
}; 

bool TurnToHeading::isOver(){ 
   return control->atSetpoint();
};  

void TurnToHeading::end(){ 
    driveRef.stop();
};  

double TurnToHeading::getDistToSpin(){ 
    return fabs(driveRef.get<double>("Angle_Degrees") - startingAngle) - angularDifference;
};

TurnToHeading::~TurnToHeading(){ 
    delete control;
}

////////////////////////////////////////////////////////////  

void IntakeToHopper::start(){ 
   hoodRef.close(); 
   startingTime = Brain.Timer.time(vex::msec); 
};  

void IntakeToHopper::periodic(){ 
  intakeRef.intake(); 
  indexerRef.spinUnder();
};  

bool IntakeToHopper::isOver(){ 
    return Brain.Timer.time(vex::msec) - startingTime >= timeDuration;
} 

void IntakeToHopper::end(){ 
    intakeRef.stop(); 
    indexerRef.stop(); 
    hoodRef.stop();
} 

IntakeToHopper::~IntakeToHopper(){ 
    return;
} 

////////////////////////////////////////////////////////////  

void ScoreOnGoal::start(){ 
   //Top: 1 
   //Mid: 2 
   //Low: 3 
   if (goal == 1) 
     hoodRef.open();
       
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
} 

ScoreOnGoal::~ScoreOnGoal(){ 
    return;
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

void end(){ 
    return;
}  

DeployMatchloader::~DeployMatchloader(){ 
    return;
}



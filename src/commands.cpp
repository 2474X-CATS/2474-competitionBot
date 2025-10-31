#include "commands.h" 

//////////////////////////////////////////////////////////// 
void DriveForwardBy::start(){  
    driveRef.setSpeedFactor(1);
    startingPoint[0] = driveRef.get<double>("Pos_X"); 
    startingPoint[1] = driveRef.get<double>("Pos_Y");  
    control->setLastTimestamp(Brain.Timer.time());   
    Brain.Screen.print("Made it to the start");
};

void DriveForwardBy::periodic(){ 
    double output = control->calculate(getDistTraveled(), Brain.Timer.time()) * 2.5;  
    if (!goingForward) 
        output = -output;
    driveRef.manualDriveForward(output);
}; 

bool DriveForwardBy::isOver(){ 
    return control->atSetpoint(getDistTraveled());
};

void DriveForwardBy::end(){ 
    driveRef.stop();  
    driveRef.setSpeedFactor(0.85); 
}; 

double DriveForwardBy::getDistTraveled(){ 
    return hypot(driveRef.get<double>("Pos_X") - startingPoint[0], driveRef.get<double>("Pos_Y") - startingPoint[1]); 
}; 

////////////////////////////////////////////////////////////  

void DriveForwardWhileIntaking::start(){  
    hoodRef.close();
    startingPoint[0] = driveRef.get<double>("Pos_X"); 
    startingPoint[1] = driveRef.get<double>("Pos_Y");  
    control->setLastTimestamp(Brain.Timer.time());   
};

void DriveForwardWhileIntaking::periodic(){ 
    double output = control->calculate(getDistTraveled(), Brain.Timer.time()) * 1.5;  
    if (!goingForward) 
        output = -output; 
    intakeRef.intake(); 
    indexerRef.spinOver();
    driveRef.manualDriveForward(output);  
}; 

bool DriveForwardWhileIntaking::isOver(){ 
    return control->atSetpoint(getDistTraveled());
};

void DriveForwardWhileIntaking::end(){ 
    driveRef.stop();   
    intakeRef.stop();   
    indexerRef.stop();
}; 

double DriveForwardWhileIntaking::getDistTraveled(){ 
    return hypot(driveRef.get<double>("Pos_X") - startingPoint[0], driveRef.get<double>("Pos_Y") - startingPoint[1]); 
};
////////////////////////////////////////////////////////////

void DriveForwardForTime::start(){ 
    drivebaseRef.setSpeedFactor(1); 
    startingTime = Brain.Timer.time(); 
}; 

void DriveForwardForTime::periodic(){ 
    drivebaseRef.arcadeDrive(percentage * 100, 0); 
};

bool DriveForwardForTime::isOver(){ 
    return Brain.Timer.time() - startingTime >= timeDuration;
} 

void DriveForwardForTime::end(){ 
    drivebaseRef.stop(); 
    drivebaseRef.setSpeedFactor(0.85);
}
//////////////////////////////////////////////////////////// 

void TurnToHeading::start(){   
  double startAngle = driveRef.get<double>("Angle_Degrees");
  double clockwiseDist = startAngle > angleSetpoint ? (360 - startAngle) + angleSetpoint : angleSetpoint - startAngle; 
  double counterClockwiseDist = 360 - clockwiseDist; 
  isClockwise = (clockwiseDist < counterClockwiseDist);
  control->setLastTimestamp(Brain.Timer.time());
};

void TurnToHeading::periodic(){ 
    double output = control->calculate(getAngluarDifference(), Brain.Timer.time()) * 1.5; 
    output = isClockwise ? -output : output; 
    driveRef.manualTurnClockwise(output);
};

bool TurnToHeading::isOver(){ 
    return control->atSetpoint(getAngluarDifference());
}; 

void TurnToHeading::end(){ 
    driveRef.stop();  
};

double TurnToHeading::getAngluarDifference(){  
    double currentAngle = driveRef.get<double>("Angle_Degrees"); 
    double dist = currentAngle > angleSetpoint ? (360 - currentAngle) + angleSetpoint : angleSetpoint - currentAngle; 
    if (!isClockwise){ 
        dist = 360 - dist;
    } 
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























CommandInterface* driveForwardByTiles(double tiles){ 
    return DriveForwardBy::getCommand(fabs(tiles * TILE_SIZE_MM), tiles > 0);
}; 

CommandInterface* turnToAngle(double goalHeading){ 
    return TurnToHeading::getCommand(goalHeading);
}; 

CommandInterface* scoreOnGoal(Goal_Pos position, double timeDuration){ 
    return ScoreOnGoal::getCommand(static_cast<int>(position), timeDuration);
}; 

CommandInterface* intakeCubes(double timeDuration){ 
    return IntakeToHopper::getCommand(timeDuration); 
}; 

CommandInterface* holdFor(double timeDuration){ 
    return WaitFor::getCommand(timeDuration);
}; 

CommandInterface* extend(){ 
    return DeployMatchloader::getCommand(true);
};

CommandInterface* retract(){ 
    return DeployMatchloader::getCommand(false);
};  

CommandInterface* driveAndIntakeForTiles(double tiles){ 
    return DriveForwardWhileIntaking::getCommand(fabs(tiles * TILE_SIZE_MM), tiles > 0); 
}; 

CommandInterface* ramForwardFor(double percentage, double timeDuration){ 
    return DriveForwardForTime::getCommand(percentage, timeDuration);
}



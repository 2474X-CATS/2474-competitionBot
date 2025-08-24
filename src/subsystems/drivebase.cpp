#include "vex.h" 
#include "drivebase.h"   
#include "math.h" 

//---Drivebase: SUBSYSTEM 

Drivebase::Drivebase() :  
   Subsystem ( 
      "drivebase",
      { 
         (EntrySet){"Pos_X", EntryType::DOUBLE}, 
         (EntrySet){"Pos_Y",EntryType::DOUBLE}, 
         (EntrySet){"Angle_Degrees",EntryType::DOUBLE}
      }){  
         powerPID.P = 1; 
         powerPID.I = 0.1; 
         powerPID.D = 0;   
         powerPID.errorTolerance = 2;
         //------------------------------
         turnPID.P = 0; 
         turnPID.I = 0; 
         turnPID.D = 0;  
         turnPID.errorTolerance = 2;
         
};  

void Drivebase::init(){ 
    driveMotors.setStopping(brakeType::brake);  
    drivePowerEncoder.resetRotation(); 
    driveRotationEncoder.resetRotation(); 
};  

void Drivebase::periodic(){ 
    driveMotors.arcade(Controller.Axis1.position(), Controller.Axis3.position()); 
};   

void Drivebase::updateTelemetry(){   
    double distTurned = driveRotationEncoder.rotation(rotationUnits::rev) * (ENCODER_WHEEL_RADIUS_MM * 2) * M_PI; 
    double angle = fmod(distTurned / ROT_ENCODER_DIST_FROM_CENTER_MM, 360);
    if (angle < 0) 
      angle += 360;  
    
    double forwardPower = drivePowerEncoder.velocity(velocityUnits::rpm) * (DRIVE_WHEEL_RADIUS_MM * 2 * M_PI) / (60 * 50); 
    
    double x = get<double>("Pos_X"); 
    double y = get<double>("Pos_Y"); 
    
    x += cos(angle / 360 * M_PI * 2) * forwardPower;  
    y += sin(angle / 360 * M_PI * 2) * forwardPower; 

    set<double>("Pos_X",x); 
    set<double>("Pos_Y",y); 
    set<double>("Angle_Degrees",angle);     
};  

void Drivebase::arcadeDrive(double speed, double rotation){ 
    driveMotors.arcade(speed, rotation);
};    

void Drivebase::manualDriveForward(double speedMM){   
    double absSpeedMM = fabs(speedMM);  
    absSpeedMM /= (ROBOT_RADIUS_MM * 2 * M_PI);  
    absSpeedMM *= 60; 
    if (speedMM < 0){
       driveMotors.turn(turnType::left, absSpeedMM, rpm); 
    } else { 
       driveMotors.turn(turnType::right, absSpeedMM, rpm);
    }
}; 

void Drivebase::manualTurnClockwise(double turnDeg){ 
    double absTurnDeg = fabs(turnDeg);   
    if (turnDeg < 0){ 
       driveMotors.drive(directionType::rev, absTurnDeg,velocityUnits::dps);
    } else { 
       driveMotors.drive(directionType::fwd,absTurnDeg,velocityUnits::dps);
    }
    
};

void Drivebase::stop(){ 
    driveMotors.stop();
};  

PIDConstants Drivebase::getPowerPID(){ 
   return this->powerPID;
}; 

PIDConstants Drivebase::getTurningPID(){ 
   return this->turnPID;
};

//---Drive Linear: COMMAND

DriveLinear::DriveLinear(Drivebase& drive, double displacement) :  
Command<Drivebase>(drive),   
driveRef(drive){ 
   control = new pidcontroller(driveRef.getPowerPID(), displacement);
}; 

void DriveLinear::start(){  
   
    startingPoint[0] = driveRef.get<double>("Pos_X"); 
    startingPoint[1] = driveRef.get<double>("Pos_Y");  
   
}; 

void DriveLinear::periodic(){  
   driveRef.manualDriveForward(control->calculate(getDistTraveled()));   
}; 

bool DriveLinear::isOver(){  
   return control->atSetpoint();
};   

void DriveLinear::end(){ 
   driveRef.stop();
}; 

DriveLinear::~DriveLinear(){ 
   delete control;
}; 

double DriveLinear::getDistTraveled(){  
    double currentPoint[2] = {driveRef.get<double>("Pos_X"), driveRef.get<double>("Pos_Y")}; 
    double xDiff = currentPoint[0] - startingPoint[0]; 
    double yDiff = currentPoint[1] - startingPoint[1]; 
    return sqrt(((xDiff * xDiff) + (yDiff + yDiff)));  
}; 

//---Turn to Heading: COMMAND

TurnTo::TurnTo(Drivebase& drive, double degrees) :  
Command<Drivebase>(drive),
driveRef(drive){ 
  setpoint = degrees;  
  control = new pidcontroller(driveRef.getTurningPID(), 0);
};

void TurnTo::start(){ 
  return;
};  

void TurnTo::periodic(){ 
  driveRef.manualTurnClockwise(control->calculate(getError())); 
}; 

bool TurnTo::isOver(){ 
  return control->atSetpoint();
}; 

void TurnTo::end(){ 
  driveRef.stop();
}; 

TurnTo::~TurnTo(){ 
   delete control;
}; 

double TurnTo::getError(){ 
   return -(fmod(((driveRef.get<double>("Angle_Degrees") - setpoint) + 540), 360) - 180);
};
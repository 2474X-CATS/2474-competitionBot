#include "vex.h" 
#include "drivebase.h"   
#include "math.h"  
#include "../architecture/telemetry.h"

//---Drivebase: SUBSYSTEM 

double Drivebase::getPositionX(){ 
   return Telemetry::inst.getValueAt<double>(this->label, "Pos_X"); 
};  

double Drivebase::getPositionY(){ 
   return Telemetry::inst.getValueAt<double>(this->label, "Pos_Y");
};  

double Drivebase::getAngleDegrees(){ 
   return Telemetry::inst.getValueAt<double>(this->label, "Angle_Degrees");
}; 

void Drivebase::init(){ 
    driveMotors.setStopping(vex::brakeType::brake);  
    driveGyro.calibrate(); 
    powerPID.P = 1; 
    powerPID.I = 0.1; 
    powerPID.D = 0;   
    powerPID.errorTolerance = 2;
         //------------------------------
    turnPID.P = 0; 
    turnPID.I = 0; 
    turnPID.D = 0;  
    turnPID.errorTolerance = 2; 

    set<double>("Pos_X", startX); 
    set<double>("Pos_Y", startY); 
};  

void Drivebase::periodic(){ 
    driveMotors.arcade(Controller.Axis1.position(), Controller.Axis3.position()); 
};   

void Drivebase::updateTelemetry(){   
    this->set<double>("Angle_Degrees", driveMotors.heading()); 
    double x = getPositionX(); 
    double y = getPositionY();   
    x += (driveMotors.velocity(vex::velocityUnits::rpm) / 60 / 50) * cos(this->get<double>("Angle_Degrees") / 360 * (M_PI * 2)); 
    y += (driveMotors.velocity(vex::velocityUnits::rpm) / 60 / 50) * sin(this->get<double>("Angle_Degrees") / 360 * (M_PI * 2));  
    this->set<double>("Pos_X", x); 
    this->set<double>("Pos_Y", y);  
   
};  

void Drivebase::arcadeDrive(double speed, double rotation){ 
    driveMotors.arcade(speed, rotation);
};    

void Drivebase::manualDriveForward(double speedMM){   
    double absSpeedMM = fabs(speedMM);  
    absSpeedMM /= (DRIVE_WHEEL_RADIUS_MM * 2 * M_PI); // Converting to rotations per second  
    absSpeedMM *= 60; // Converting to rotations per minute 
    if (speedMM < 0){
       driveMotors.turn(vex::turnType::left, absSpeedMM, vex::rpm); 
    } else { 
       driveMotors.turn(vex::turnType::right, absSpeedMM, vex::rpm);
    }
}; 

void Drivebase::manualTurnClockwise(double turnDeg){ 
    double absTurnDeg = fabs(turnDeg);   
    if (turnDeg < 0){ 
       driveMotors.drive(vex::directionType::rev, absTurnDeg, vex::velocityUnits::dps);
    } else { 
       driveMotors.drive(vex::directionType::fwd,absTurnDeg, vex::velocityUnits::dps);
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
   //Brain.Screen.print(control->calculate(getDistTraveled())); 
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
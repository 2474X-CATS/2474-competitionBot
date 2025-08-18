#include "vex.h" 
#include "Drivebase.h"   
#include "math.h"

void Drivebase::arcadeDrive(double speed, double rotation){ 
    driveMotors.arcade(speed, rotation);
};   

void Drivebase::manualDriveForward(double speedMM){   
    double absSpeedMM = fabs(speedMM);  
    absSpeedMM /= (ROBOT_RADIUS_MM * 2 * M_PI); // Converting speed to rotations per second
    absSpeedMM *= 60; // Converts rotations per second to rotations per minute
    if (speedMM < 0){
       driveMotors.drive(directionType::rev, absSpeedMM, rpm); 
    } else { 
       driveMotors.drive(directionType::fwd, absSpeedMM, rpm);
    }
}; 

void Drivebase::manualTurnClockwise(double turnDeg){ 
    double absTurnDeg = fabs(turnDeg);   
    if (turnDeg < 0){ 
       driveMotors.turn(turnType::left, absTurnDeg,velocityUnits::dps);
    } else { 
       driveMotors.turn(turnType::right,absTurnDeg,velocityUnits::dps);
    }
    
}

void Drivebase::stop(){ 
    driveMotors.stop();
};  

pidcontroller Drivebase::getTurningController(double setpoint){ 
   return pidcontroller(turnPID.P, turnPID.I, turnPID.D, setpoint, turnPID.errorTolerance, turnPID.iLimit);
} 

pidcontroller Drivebase::getPowerController(double setpoint){ 
   return pidcontroller(powerPID.P, powerPID.I, powerPID.D, setpoint, powerPID.errorTolerance, powerPID.iLimit);
}


void Drivebase::init(){ 
    driveMotors.setStopping(brakeType::brake); 
    drivePowerEncoder.resetRotation(); 
    driveRotationEncoder.resetRotation();
};  

void Drivebase::periodic(){ 
    arcadeDrive(Controller.Axis3.position() / 100, Controller.Axis1.position() / 100);
};   

void Drivebase::updateTelemetry(){  
    double distTurned = driveRotationEncoder.rotation(rotationUnits::rev) * (ENCODER_WHEEL_RADIUS_MM * 2) * M_PI; 
    double angle = fmod(distTurned / ROT_ENCODER_DIST_FROM_CENTER_MM, 360);
    if (angle < 0) 
      angle += 360;  
    
    double forwardPower = drivePowerEncoder.velocity(velocityUnits::rpm) * (DRIVE_WHEEL_RADIUS_MM * 2 * M_PI) / (60 * 50); // For a single frame (20 milliseconds)
    
    double x = get<double>("Pos_X"); 
    double y = get<double>("Pos_Y"); 
    
    x += cos(angle / 360 * M_PI * 2) * forwardPower;  
    y += sin(angle / 360 * M_PI * 2) * forwardPower; 

    set<double>("Pos_X",x); 
    set<double>("Pos_Y",y); 
    set<double>("Angle_Degrees",angle);    
};  

DriveForward::DriveForward(Drivebase* drive, double distForward) :  
Command<Drivebase>(drive),  
control(drive->getPowerController(distForward)){ 
     
}; 

double DriveForward::getDistTraveled(){ 
    double currentPoint[2] = {sub->get<double>("Pos_X"), sub->get<double>("Pos_Y")}; 
    double xDiff = currentPoint[0] - startingPoint[0]; 
    double yDiff = currentPoint[1] - startingPoint[1]; 
    return sqrt(((xDiff * xDiff) + (yDiff + yDiff)));
}; 

void DriveForward::start(){ 
   startingPoint[0] = sub->get<double>("Pos_X"); 
   startingPoint[1] = sub->get<double>("Pos_Y");
}; 

void DriveForward::periodic(){ 
   sub->manualDriveForward(control.calculate(getDistTraveled())); 
}; 

void DriveForward::end(){ 
   sub->stop();
}; 

bool DriveForward::isOver(){ 
   return control.atSetpoint();
};





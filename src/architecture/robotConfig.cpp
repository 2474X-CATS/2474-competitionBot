#include "vex.h"

const vex::brain Brain; 

const vex::controller Controller = vex::controller(vex::controllerType::primary); 

// Subsystems 

//-----Channel
const vex::motor channelMotor1 = vex::motor(vex::PORT1); 
const vex::motor channelMotor2 = vex::motor(vex::PORT1);   
const vex::motor channelMotor3 = vex::motor(vex::PORT1); 
const vex::pneumatics channelPneumatics = vex::pneumatics(Brain.ThreeWirePort.A);
//-----Drivebase 
const vex::motor driveFrontLeft = vex::motor(vex::PORT1); 
const vex::motor driveFrontRight = vex::motor(vex::PORT1); 
const vex::motor driveBackLeft = vex::motor(vex::PORT1); 
const vex::motor driveBackRight = vex::motor(vex::PORT1); 
const vex::motor driveMidLeft = vex::motor(vex::PORT1); 
const vex::motor driveMidRight = vex::motor(vex::PORT1);




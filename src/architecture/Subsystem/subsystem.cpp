#include "subsystem.h" 
#include <thread>  
#include <iostream> 

Subsystem::Subsystem(){ 
   Subsystem::systems.push_back(this);   
};


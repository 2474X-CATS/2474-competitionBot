#ifndef __ROBOT_H__
#define __ROBOT_H__ 

#include <vector> 
#include <command.h>
#include "vex.h"  



class Robot { 
    private:      

       vex::competition competition; 
       vex::brain brain;   
       vex::controller controller;  

       void registerSystemSubtable(); 
       void updateSystemSubtable(); 

    public:   
       void driverControl();  

       void startTelemetry(); 
       
};



#endif
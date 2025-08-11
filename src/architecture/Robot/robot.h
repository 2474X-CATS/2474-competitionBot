#ifndef __ROBOT_H__
#define __ROBOT_H__ 

#include "vex.h" 

class Robot { 
    private:  
       static Robot instance;    
       void start(); 
       vex::competition competition; 
       vex::brain brain; 
    public: 
       vex::controller controller;  
       static void createRobot();  
};



#endif
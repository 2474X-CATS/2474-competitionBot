#include "robot.h"
#include "subsystem.h"
#include "telemetry.h"
#include "command.h"  


void drawCircleButton(int x, int y, string buttonName){ 
  color Color;  
  uint32_t designatedColor; 
  bool isBeingPressed = Telemetry::inst.getValueAt<bool>("system","Controller/Button_" + buttonName); 
  if (isBeingPressed){ 
    designatedColor = Color.red;
  } else { 
    designatedColor = Color.black;
  }
  Brain.Screen.drawCircle(x,y,15, designatedColor);
} 

void drawRectButton(int x, int y, int width, int height, string buttonName){ 
  color Color;  
  uint32_t designatedColor; 
  bool isBeingPressed = Telemetry::inst.getValueAt<bool>("system","Controller/Button_" + buttonName); 
  if (isBeingPressed){ 
    designatedColor = Color.red;
  } else { 
    designatedColor = Color.black;
  }
  Brain.Screen.drawRectangle(x-(width/2),y-(height/2),width,height, designatedColor);
}

void drawJoystick(int x, int y, string location){  
  color Color; 
  Brain.Screen.drawCircle(x,y, 30, Color.black); 
  int horizontalPower = Telemetry::inst.getValueAt<int>("system","Controller/Axis-Hori-" + location); 
  int verticalPower = Telemetry::inst.getValueAt<int>("system","Controller/Axis-Vert-" + location);  
  Brain.Screen.drawCircle(x + ((30/2) * (horizontalPower / 100)), y - ((30/2) * (verticalPower / 100)), 30);
}

void displayGraphicalData(){  
  color Color;
  Brain.Screen.drawRectangle(70,20,355,195, Color.rgb(100,100,100));   

  drawJoystick(115,70,"Left"); 
  drawJoystick(375,70,"Right");  

  drawCircleButton(330+22,150,"A");   
  drawCircleButton(330,150+22,"B"); 
  drawCircleButton(330,150-22,"X");   
  drawCircleButton(330-22,150,"Y");  
  
  drawCircleButton(160-22,150,"LEFT");   
  drawCircleButton(160+22,150,"RIGHT"); 
  drawCircleButton(160,150-22,"UP");   
  drawCircleButton(160,150+22,"DOWN");
  
  drawRectButton(142,12,35,20,"L2");
  drawRectButton(142,25,50,30,"L1"); 
  drawRectButton(350,12,35,20,"R2");
  drawRectButton(350,25,50,30,"R1"); 
  
} 

void Robot::driverControl()
{
    Subsystem::initSystems();
    while (true)
    { 
        Subsystem::updateSystems();
        vex::this_thread::sleep_for(20);
    }
}; 

void Robot::setAutonomousCommand(std::vector<std::vector<CommandInterface*>> comm){ 
   autonomousCommand = comm;
};

void Robot::initialize()
{
    registerSystemSubtable();
    Subsystem::initSystems();
};


void Robot::autonControl()
{
    CommandInterface::runCommandGroup(Robot::autonomousCommand); 
};

void Robot::registerSystemSubtable()
{ 
    Telemetry::inst.registerSubtable(
        "system",
        {
            //(EntrySet){"Battery/Temperature", EntryType::DOUBLE},
            //(EntrySet){"Battery/Voltage", EntryType::DOUBLE},
            //(EntrySet){"Battery/Current", EntryType::DOUBLE},
            (EntrySet){"Controller/Axis-Vert-Left", EntryType::INT},
            (EntrySet){"Controller/Axis-Hori-Left", EntryType::INT},
            (EntrySet){"Controller/Axis-Vert-Right", EntryType::INT},
            (EntrySet){"Controller/Axis-Hori-Right", EntryType::INT},
            (EntrySet){"Controller/Button_A", EntryType::BOOL},
            (EntrySet){"Controller/Button_B", EntryType::BOOL},
            (EntrySet){"Controller/Button_X", EntryType::BOOL},
            (EntrySet){"Controller/Button_Y", EntryType::BOOL},
            (EntrySet){"Controller/Button_DOWN", EntryType::BOOL},
            (EntrySet){"Controller/Button_UP", EntryType::BOOL},
            (EntrySet){"Controller/Button_LEFT", EntryType::BOOL},
            (EntrySet){"Controller/Button_RIGHT", EntryType::BOOL},
            (EntrySet){"Controller/Button_L1", EntryType::BOOL},
            (EntrySet){"Controller/Button_L2", EntryType::BOOL},
            (EntrySet){"Controller/Button_R1", EntryType::BOOL},
            (EntrySet){"Controller/Button_R2", EntryType::BOOL},
        });
};

void Robot::updateSystemSubtable()
{   
    //Telemetry::inst.placeValueAt<double>(Brain.Battery.temperature(), "system", "Battery/Temperature");
    //Telemetry::inst.placeValueAt<double>(Brain.Battery.voltage(), "system", "Battery/Voltage");
    //Telemetry::inst.placeValueAt<double>(Brain.Battery.current(), "system", "Battery/Current");
    Telemetry::inst.placeValueAt<int>(Controller.Axis3.position(), "system", "Controller/Axis-Vert-Left");
    Telemetry::inst.placeValueAt<int>(Controller.Axis4.position(), "system", "Controller/Axis-Hori-Left");
    Telemetry::inst.placeValueAt<int>(Controller.Axis2.position(), "system", "Controller/Axis-Vert-Right");
    Telemetry::inst.placeValueAt<int>(Controller.Axis1.position(), "system", "Controller/Axis-Hori-Right");
    Telemetry::inst.placeValueAt<bool>(Controller.ButtonA.pressing(), "system", "Controller/Button_A");
    Telemetry::inst.placeValueAt<bool>(Controller.ButtonB.pressing(), "system", "Controller/Button_B");
    Telemetry::inst.placeValueAt<bool>(Controller.ButtonX.pressing(), "system", "Controller/Button_X");
    Telemetry::inst.placeValueAt<bool>(Controller.ButtonY.pressing(), "system", "Controller/Button_Y");
    Telemetry::inst.placeValueAt<bool>(Controller.ButtonDown.pressing(), "system", "Controller/Button_DOWN");
    Telemetry::inst.placeValueAt<bool>(Controller.ButtonUp.pressing(), "system", "Controller/Button_UP");
    Telemetry::inst.placeValueAt<bool>(Controller.ButtonLeft.pressing(), "system", "Controller/Button_LEFT");
    Telemetry::inst.placeValueAt<bool>(Controller.ButtonRight.pressing(), "system", "Controller/Button_RIGHT");
    Telemetry::inst.placeValueAt<bool>(Controller.ButtonL1.pressing(), "system", "Controller/Button_L1");
    Telemetry::inst.placeValueAt<bool>(Controller.ButtonL2.pressing(), "system", "Controller/Button_L2");
    Telemetry::inst.placeValueAt<bool>(Controller.ButtonR1.pressing(), "system", "Controller/Button_R1");
    Telemetry::inst.placeValueAt<bool>(Controller.ButtonR2.pressing(), "system", "Controller/Button_R2");
};


void Robot::runTelemetryThread(bool showGraphics)
{  
  while (true){
    updateSystemSubtable();
    Subsystem::refreshTelemetry(); 
    if (showGraphics){ 
        displayGraphicalData();
    }  
    vex::this_thread::sleep_for(19);
  }
};
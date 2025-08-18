#ifndef __COMMAND_H__
#define __COMMAND_H__

#include "subsystem.h"
#include <vector>
#include <stdexcept>
#include <iostream>
#include <cstdlib>
#include <atomic>

struct ICommand
{ // Interface made for autonomous commands that use various types of subsystems

  virtual void run() = 0;
  virtual void occupySubsystem() = 0;
  virtual bool isSubsystemOccupied() = 0;

  static void runCommandGroup(std::vector<std::vector<ICommand *>> systems);

  static std::atomic<int> completedTasks;
};

template <class T>
class Command : public ICommand
{   

  static_assert(is_base_of<Subsystem, T>::value, "Command must wrap around a Subsystem type");

public:
  Command(T *sys) : sub(sys) {}
  T *sub;

  void run() override
  {
    this->start();
    do
    {
      this->periodic();
      vex::this_thread::sleep_for(20);
    } while (!this->isOver());
    this->end();
    this->sub->inCommand = false;
  };

  void occupySubsystem() override
  {
    this->sub->inCommand = true;
  };

  bool isSubsystemOccupied() override
  {
    return this->sub->inCommand;
  };

protected:
  virtual void start() {};
  virtual void periodic() = 0;
  virtual bool isOver() { return true; };
  virtual void end() = 0;

  virtual ~Command() = default;
};

#endif
#pragma once
#include "vex.h"
#include <memory>
#include <functional>  

using namespace vex;

class LambdaTaskWrapper {
public:
  std::function<int()> func;

  LambdaTaskWrapper(std::function<int()> f) : func(f) {}

  static int run(void* obj) {
    std::unique_ptr<LambdaTaskWrapper> self(static_cast<LambdaTaskWrapper*>(obj));
    return self->func();
  }
}; 

class Barrier {
private:
  int thread_count;
  int arrived = 0;
  int generation = 0;

  vex::mutex lock;

public:
  explicit Barrier(int count) : thread_count(count) {}

  void wait() {
    lock.lock();
    int my_gen = generation;
    arrived++;
    if (arrived == thread_count) {
      // Last thread resets
      arrived = 0;
      generation++;
      
      lock.unlock();
      return;
    }
    lock.unlock();
    while (generation == my_gen) {
      this_thread::yield();
    }
  }
};


#define make_task(lambda_expr) \
  vex::task(LambdaTaskWrapper::run, new LambdaTaskWrapper(std::function<int()>(lambda_expr)))
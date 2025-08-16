#pragma once
#include "vex.h"
#include <memory>
#include <functional>


class Barrier
{
private:
  int thread_count;
  int arrived = 0;
  int generation = 0;

  vex::mutex lock;

public:
  explicit Barrier(int count) : thread_count(count) {}

  void wait()
  {
    lock.lock();
    int my_gen = generation;
    arrived++;
    if (arrived == thread_count)
    {
      arrived = 0;
      generation++;
      lock.unlock();
      return;
    }
    lock.unlock();
    while (generation == my_gen)
    {
      vex::this_thread::yield();
    }
  }
};

class LambdaTaskWrapper
{
public:
  std::function<int()> func;

  LambdaTaskWrapper(std::function<int()> f) : func(f) {}

  static int run(void *obj)
  {
    std::unique_ptr<LambdaTaskWrapper> self(static_cast<LambdaTaskWrapper *>(obj));
    return self->func();
  }
};

#define make_task(lambda_expr) \
  vex::task(LambdaTaskWrapper::run, new LambdaTaskWrapper(std::function<int()>(lambda_expr)))
#pragma once
#include <array>

#include "Fork.h"
#include "Philosopher.h"

class Simulation {
 public:
  Simulation();
  Simulation(int eatTime_, int sleepTime_, int pNum_);
  ~Simulation();

  void stop();

 private:
  bool keepRunning;

  int eatTime;
  int sleepTime;
  int philosophersNumber;

  std::array<Fork, 128> forks;
  Philosopher** philosophers;

  std::thread consoleLogThread;
  void consoleLog();
};

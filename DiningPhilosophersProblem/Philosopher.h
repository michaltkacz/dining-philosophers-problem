#pragma once
#include <algorithm>
#include <array>
#include <chrono>
#include <random>
#include <string>
#include <thread>

#include "Fork.h"
#include "States.h"

class Philosopher {
 public:
  Philosopher(std::string name_, Fork& leftFork_, Fork& rightFork_,
              int eatTime_, int sleepTime_);
  ~Philosopher();

  std::string getName();
  States getState();
  Fork& getLeftFork();
  Fork& getRightFork();
  int getEatNumber();
  int getSleepNumber();

  void stopRunning();

 private:
  std::mt19937 rng{std::random_device{}()};

  std::thread thisThread;
  std::atomic_bool keepRunning;

  std::string name;
  Fork& leftFork;
  Fork& rightFork;

  int eatTime;
  int sleepTime;

  States state;
  int eatNumber;
  int sleepNumber;

  void run();
  void eat();
  void sleep();
};
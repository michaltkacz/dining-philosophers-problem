#include "Philosopher.h"

#include <iostream>

Philosopher::Philosopher(std::string name_, Fork& leftFork_, Fork& rightFork_,
                         int eatTime_, int sleepTime_)
    : name(std::move(name_)),
      leftFork(leftFork_),
      rightFork(rightFork_),
      eatTime(eatTime_),
      sleepTime(sleepTime_),
      eatNumber(0),
      sleepNumber(0),
      keepRunning(true),
      state(States::Sleep),
      thisThread(&Philosopher::run, this) {}

Philosopher::~Philosopher() {
  // finish philosopher thread
  thisThread.join();
  std::cout << name << " joined " << std::endl;
}

std::string Philosopher::getName() { return name; }

States Philosopher::getState() { return state; }

Fork& Philosopher::getLeftFork() { return leftFork; }

Fork& Philosopher::getRightFork() { return rightFork; }

int Philosopher::getEatNumber() { return eatNumber; }

int Philosopher::getSleepNumber() { return sleepNumber; }

void Philosopher::stopRunning() { keepRunning = false; }

void Philosopher::run() {
  // life cycle of the thread
  while (keepRunning) {
    {
      // The class scoped_lock is a mutex wrapper that provides a
      // convenient RAII-style mechanism for owning one or more mutexes for
      // the duration of a scoped block.
      //
      // When a scoped_lock object is created, it attempts to take ownership of
      // the mutexes it is given. When control leaves the scope in which the
      // scoped_lock object was created, the scoped_lock is destructed and the
      // mutexes are released, in reverse order. If several mutexes are given,
      // deadlock avoidance algorithm is used as if by std::lock.
      //
      // The scoped_lock class is non-copyable.
      std::scoped_lock eat_lock(leftFork.mutex, rightFork.mutex);

      // when forks are locked, eat
      eat();
    }
    // and go to sleep
    sleep();
  }
}

void Philosopher::eat() {
  eatNumber++;
  state = States::Eat;

  leftFork.setOwnerName(name);
  rightFork.setOwnerName(name);

  thread_local std::uniform_real_distribution<> wait(-0.25, 0.25);
  std::this_thread::sleep_for(
      std::chrono::milliseconds(eatTime + int(wait(rng)) * eatTime));
}

void Philosopher::sleep() {
  sleepNumber++;
  state = States::Sleep;

  thread_local std::uniform_real_distribution<> wait(-0.25, 0.25);
  std::this_thread::sleep_for(
      std::chrono::milliseconds(sleepTime + int(wait(rng) * sleepTime)));
}

#include "Simulation.h"

#include <chrono>
#include <iostream>
#include <thread>

Simulation::Simulation() : Simulation(1000, 1000, 5) {}

Simulation::Simulation(int eatTime_, int sleepTime_, int pNum_)
    : eatTime(eatTime_),
      sleepTime(sleepTime_),
      philosophersNumber(pNum_),
      keepRunning(true) {
  // init philosophers
  philosophers = new Philosopher*[philosophersNumber];
  for (int i = 0; i < philosophersNumber; i++) {
    philosophers[i] = new Philosopher{"P" + std::to_string(i), forks[i],
                                      forks[(i + 1) % philosophersNumber],
                                      eatTime, sleepTime};
  }

  // init console loggin thread
  consoleLogThread = std::thread(&Simulation::consoleLog, this);
}

Simulation::~Simulation() {
  // delete philosophers
  for (int i = 0; i < philosophersNumber; i++) {
    delete philosophers[i];
  }
  delete[] philosophers;
  // finish console loggin thread
  consoleLogThread.join();
  // end
  std::cout << "Simulation.consoleLog() joined" << std::endl;
  std::cout << "Simulation finished successfuly\n" << std::endl;
}

void Simulation::consoleLog() {
  // life cycle of the thread
  std::string pPrevOutput = "";
  std::string fPrevOutput = "";
  while (keepRunning) {
    // construct output
    std::string pOutput = "";
    std::string fOutput = "";
    for (int i = 0; i < philosophersNumber; i++) {
      std::string pName = philosophers[i]->getName();
      std::string pState = stateToString(philosophers[i]->getState());
      std::string pEatNumber = std::to_string(philosophers[i]->getEatNumber());
      std::string pSleepNumber =
          std::to_string(philosophers[i]->getSleepNumber());
      pOutput += pName;
      pOutput += " ";
      pOutput += pState;
      pOutput += "Eat number: ";
      pOutput += pEatNumber;
      pOutput += ", sleep number: ";
      pOutput += pSleepNumber;
      pOutput += "\n";

      std::string forkId = std::to_string(forks[i].getId());
      std::string forkOwnerName = forks[i].getOwnerName();
      fOutput += "Fork ";
      fOutput += forkId;
      fOutput += " has owner: ";
      fOutput += forkOwnerName;
      fOutput += "\n";
    }

    // clear screen and reprint only if output has changed
    if (pOutput != pPrevOutput || fOutput != fPrevOutput) {
      system("cls");
      std::cout << pOutput << std::endl;
      std::cout << fOutput << std::endl;
      pPrevOutput = pOutput;
      fPrevOutput = fOutput;
    }
  }
}

void Simulation::stop() {
  // stop every thread
  for (int i = 0; i < philosophersNumber; i++) {
    philosophers[i]->stopRunning();
  }
  // stop simulation
  keepRunning = false;
}

#include <conio.h>

#include <iostream>

#include "Simulation.h"

int main() {
  int pNum = 0;
  int sleepTime = 0;
  int eatTime = 0;

  std::cout << "Number of philosophers: ";
  std::cin >> pNum;
  std::cout << "Sleep time (milliseconds +/-25%): ";
  std::cin >> sleepTime;
  std::cout << "Eat time (milliseconds +/-25%): ";
  std::cin >> eatTime;

  // philosophers threads will start right away
  Simulation sim(eatTime, sleepTime, pNum);

  // wait for Q key to end program
  while (_getch() != 'q')
    ;

  // stop simulation, join all threads
  sim.stop();
}
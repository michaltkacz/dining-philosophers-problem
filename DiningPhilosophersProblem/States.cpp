#include "States.h"

std::string stateToString(States state) {
  switch (state) {
    case States::Eat:
      return "is eating...    ";
    case States::Sleep:
      return "is sleeping...  ";
    default:
      return "unknown";
  }
}
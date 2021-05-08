#pragma once

#include <mutex>
#include <string>

class Fork {
 public:
  static int Count;

  Fork();
  int getId();

  std::string getOwnerName();
  void setOwnerName(std::string name);

  std::mutex mutex;

 private:
  int id;
  std::string ownerName;
};

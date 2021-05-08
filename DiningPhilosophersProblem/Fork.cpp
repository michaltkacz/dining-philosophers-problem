#include "Fork.h"

int Fork::Count = 0;

Fork::Fork() : id(Fork::Count++), ownerName("none") {}

std::string Fork::getOwnerName() { return ownerName; }

void Fork::setOwnerName(std::string name) { ownerName = name; }

int Fork::getId() { return id; }
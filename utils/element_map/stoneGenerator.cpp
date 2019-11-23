#include "stoneGenerator.hh"
#include "linemate.hh"
#include "sibur.hh"
#include "deraumere.hh"
#include "mendiane.hh"

AStone *StoneGenerator::createStone(std::string className) {
    if (className.compare("Linemate") == 0 || className.substr(0,1).compare("L") == 0)
        return new Linemate();
    else if (className.compare("Sibur") == 0 || className.substr(0,1).compare("S") == 0)
        return new Sibur();
    else if (className.compare("Deraumere") == 0 || className.substr(0,1).compare("D") == 0)
        return new Deraumere();
    else if (className.compare("Mendiane") == 0 || className.substr(0,1).compare("M") == 0)
        return new Mendiane();
    return nullptr;
}
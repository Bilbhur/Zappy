#ifndef STONEGENERATOR_HH
#define STONEGENERATOR_HH

#include <string>
#include "aStone.hh"

class StoneGenerator
{
    public:
        AStone *createStone(std::string className);
};

#endif
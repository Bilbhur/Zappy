#include "aStone.hh"

AStone::AStone(std::string className, int posX, int posY, bool isWalkable):
AObject(posX, posY, className, isWalkable)
{}

AStone::~AStone()
{}

std::string AStone::getDisplayer() const {
    return this->getClassName().substr(0, 1);
}

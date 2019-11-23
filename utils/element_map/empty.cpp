#include "empty.hh"

Empty::Empty(int posX, int posY):
AObject(posX, posY, "Empty", true)
{}

Empty::~Empty()
{}

std::string Empty::getDisplayer(void) const {
    return this->getClassName().substr(0,1);
}
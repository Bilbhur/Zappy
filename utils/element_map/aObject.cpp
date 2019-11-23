#include "aObject.hh"

AObject::AObject(int posX, int posY, std::string className, bool isWalkable):
_isWalkable(isWalkable),
_posX(posX),
_posY(posY),
_className(className)
{}

AObject::~AObject()
{}

int AObject::getPosX() const {
    return this->_posX;
}

void AObject::setPosX(int posX) {
    AObject::_posX = posX;
}

int AObject::getPosY() const {
    return this->_posY;
}

void AObject::setPosY(int posY) {
    AObject::_posY = posY;
}

std::string AObject::getClassName() const {
    return this->_className;
}

std::string AObject::getDisplayer() const {
    return this->getClassName().substr(0,1);
}

bool AObject::getWalkable() const {
    return this->_isWalkable;
}
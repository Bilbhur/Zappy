#include "player.hh"

Player::Player(int posX, int posY):
AObject(posX, posY, "Player", false)
{
    this->_orientation = 'N';
}

Player::~Player()
{}

int Player::getId(void) const {
    return this->_id;
}

void Player::setId(int id) {
    this->_id = id;
}

int Player::getHitPoints(void) const {
    return this->_hitPoints;
}

void Player::setHitPoints(int hitPoints) {
    this->_hitPoints = hitPoints;
}

int Player::getVictoryPoints(void) const {
    return this->_victoryPoints;
}

void Player::setVictoryPoints(int victoryPoints) {
    this->_victoryPoints = victoryPoints;
}

int Player::getEnergy(void) const {
    return this->_energy;
}

void Player::setEnergy(int energy) {
    this->_energy = energy;
}

char Player::getOrientation(void) const {
    return this->_orientation;
}

void Player::setOrientation(char orientation) {
    this->_orientation = orientation;
}

std::string Player::getDisplayer() const {
    return std::to_string(this->getId());
}

bool Player::isAlive(void) const {
    if (this->_hitPoints > 0)
        return true;
    return false;
}

bool Player::checkEnergy() const{
    if (this->_energy > 0)
        return true;
    return false;
}

void Player::takeDamage(int damage) {
    if (this->isAlive())
        this->_hitPoints -= damage;
}

void Player::heal(int heal) {
    if (this->isAlive())
        this->_hitPoints += heal;
}

void Player::consumeEnergy(int energy) {
    if (this->isAlive())
        if (this->_energy > 0 && this->_energy - energy >= 0)
            this->_energy -= energy;
}

void Player::movePlayer(int posX, int posY) {
    if (this->isAlive()) {
        this->setPosX(posX);
        this->setPosY(posY);
    }
}

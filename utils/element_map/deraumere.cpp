#include "deraumere.hh"

Deraumere::Deraumere():
AStone("Deraumere", 4, 4, true)
{}

Deraumere::~Deraumere()
{}

void Deraumere::consume(Player *p, std::vector<Player*> players) {
    // std::cout << "Deraumere :: -1 hp" << std::endl;
    
    players.at(0)->heal(0);
    p->takeDamage(1);
}
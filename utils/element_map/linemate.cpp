#include "linemate.hh"
#include <algorithm>

Linemate::Linemate():
AStone("Linemate", 1, 1, true)
{}

Linemate::~Linemate()
{}

void Linemate::consume(Player *p, std::vector<Player*> players) {
    // std::cout << "Linemate :: +1 hp " << std::endl;
    
    players.at(0)->heal(0);
    p->heal(1);
}
#include "mendiane.hh"

Mendiane::Mendiane():
AStone("Mendiane", 2, 2, true)
{}

Mendiane::~Mendiane()
{}

void Mendiane::consume(Player *p, std::vector<Player*> players) {
    // std::cout << "Mendiane :: +1 vp" << std::endl;

    players.at(0)->heal(0);
    p->setVictoryPoints(1);
}
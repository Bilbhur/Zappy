#include "sibur.hh"

Sibur::Sibur():
AStone("Sibur", 3, 3, true)
{}

Sibur::~Sibur()
{}

void Sibur::consume(Player *p, std::vector<Player*> players) {
    // std::cout << "Sibur :: -1 hp to others" << std::endl;
    for (Player *player: players)
        if (player->getId() != p->getId())
            player->takeDamage(1);
}
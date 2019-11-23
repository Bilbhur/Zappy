#ifndef DERAUMERE_HH
#define DERAUMERE_HH

#include "aStone.hh"

class Deraumere: public AStone
{
    public:
        Deraumere();
        ~Deraumere();

        void consume(Player *p, std::vector<Player*> players) override;
};

#endif
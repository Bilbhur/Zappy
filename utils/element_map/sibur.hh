#ifndef SIBUR_HH
#define SIBUR_HH

#include "aStone.hh"

class Sibur: public AStone
{
    public:
        Sibur();
        ~Sibur();

        void consume(Player *p, std::vector<Player*> players) override;
};

#endif
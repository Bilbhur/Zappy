#ifndef LINEMATE_HH
#define LINEMATE_HH

#include "aStone.hh"

class Linemate: public AStone
{
    public:
        Linemate();
        ~Linemate();

        void consume(Player *p, std::vector<Player*> players) override;
};

#endif
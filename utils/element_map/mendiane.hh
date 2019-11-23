#ifndef MENDIANE_HH
#define MENDIANE_HH

#include "aStone.hh"

class Mendiane:public AStone
{
    public:
        Mendiane();
        ~Mendiane();
        
        void consume(Player *p, std::vector<Player*> players) override;
};

#endif
#ifndef ASTONE_HH
#define ASTONE_HH

#include "aObject.hh"
#include <iostream>
#include "player.hh"
#include <vector>

class AStone: public AObject
{
    
    public:
        AStone(std::string className, int posX, int posY, bool isWalkable);
        virtual ~AStone() = 0;
        
        virtual std::string getDisplayer(void) const;
        virtual void consume(Player *p, std::vector<Player*> players) = 0;
};

#endif
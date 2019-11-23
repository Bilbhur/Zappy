#ifndef PLAYER_HH
#define PLAYER_HH

#include "aObject.hh"

class Player: public AObject
{
    private:
        int _id;
        int _hitPoints = 10;
        int _victoryPoints = 0;
        int _energy = 2;
        char _orientation;

    public:
        Player(int posX, int posY);
        ~Player();

        int getId(void) const;
        void setId(int id);
        int getHitPoints(void) const;
        void setHitPoints(int hitPoints);
        int getVictoryPoints(void) const;
        void setVictoryPoints(int victoryPoints);
        int getEnergy(void) const;
        void setEnergy(int energy);
        char getOrientation(void) const;
        void setOrientation(char orientation);
        std::string getDisplayer(void) const override;
        
        bool isAlive(void) const;
        bool checkEnergy(void) const;

        void takeDamage(int damage);
        void heal(int heal);
        void consumeEnergy(int energy);
        void movePlayer(int posX, int posY);
};

#endif
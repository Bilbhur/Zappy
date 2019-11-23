#ifndef MAP_HH
#define MAP_HH

#include <string>
#include <vector>
#include <array>
#include "element_map/player.hh"
#include "element_map/aStone.hh"

class Map
{
    private:
        int _width;
        int _height;
        int _nbPlayers;
        double _spawnPercent;
        std::vector<Player*> _players;

        AStone *_iStone;
        AObject ***_board;
        std::string _stones[4] = {"L", "M", "S", "D"};

    public:
        Map(int width, int height, int nbPlayers, double spawnPercent);
        ~Map();

        int getWidth(void) const;
        void setWidth(int width);
        int getHeight(void) const;
        void setHeight(int height);
        int getNbPlayers(void) const;
        void setNbPlayers(int nbPlayers);
        
        int getRandom(int range);
        AObject ***getBoard(void) const;
        std::vector<Player*> getPlayers() const;

        AStone *getIStone(void) const;
        void setIStone(int x, int y);
        
        bool checkIfInBoard(int x, int y);
        bool checkEmptySet(int x, int y);
        bool checkIsPlayer(int x, int y);
        bool checkIsStone(int x, int y);

        bool placeObject(void);
        bool placeObject(int id);
        bool placeObject(int x, int y);
        bool placeObject(double spawnPercent);
        
        void createMap(void);
        void drawMap(void);

        void createPortionMap(Player *player);
        std::array<std::string, 4> createPortionMap(Player *player, Map* map);

        void consumeStone(int x, int y, Player *player);
};

#endif
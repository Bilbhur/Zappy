#ifndef INSTRUCTION_HH
#define INSTRUCTION_HH

#include <vector>
#include <unordered_map>
#include "map.hh"
#include "element_map/player.hh"

class Instruction {
    public:
        Instruction();
        ~Instruction();

        bool left(Player *p);
        bool right(Player *p);

        bool leftfwd(Player *p, Map *m);
        bool rightfwd(Player *p, Map *m);

        bool fwd(Player *p, Map *m);
        bool back(Player *p, Map *m);
        bool jump(Player *p, Map *m);

        // std::map<std::string, int> inspect_deux(std::vector<Player*> players);
        std::vector<std::unordered_map<std::string, int>> inspect(Player *player, std::vector<Player*> players);
        std::unordered_map<std::string, std::string> me(Player *p);

        bool movement(Player *p, Map *m, int x, int y);
        std::tuple<int, int> computeValue(Player *player, int value);
};

#endif
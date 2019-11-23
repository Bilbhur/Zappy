#ifndef JSON_MANAGE_hh
#define JSON_MANAGE_hh

#include <iostream>
#include "json.hpp"
#include "map.hh"
#include "element_map/player.hh"

using json = nlohmann::json;

class JsonManage {
    public:
        JsonManage();
        ~JsonManage();
        json getJsonServer(std::string command, int id);
        json getJsonClient(std::string action, std::string state, Map* map, Player* player);

        json getJsonClient(std::string action, std::vector<std::unordered_map<std::string, int>> inspected, Map* map, Player* player);
        json getJsonClient(std::string action, std::unordered_map<std::string, std::string> me, Map* map, Player* player);

        json getJsonStart(int id);

};

#endif // JSON_MANAGE_HH
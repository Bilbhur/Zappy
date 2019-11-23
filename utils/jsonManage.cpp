#include <sstream>
#include "jsonManage.hh"
#include "json.hpp"
#include "element_map/player.hh"
#include "map.hh"

using json = nlohmann::json;

JsonManage::JsonManage() {

}

JsonManage::~JsonManage() {
    
}

json JsonManage::getJsonServer(std::string command, int id) {
    json jsonToServer;
    jsonToServer["id"] = id;
    jsonToServer["command"] = command;

    return jsonToServer;
}

// Get the json for instructions functions (overloading)
json JsonManage::getJsonClient(std::string action, std::string state, Map* map, Player* player) {
    json jsonForClient;
    jsonForClient[action] = state;
    auto mapClient = map->createPortionMap(player, map);
    jsonForClient["map"] = mapClient;
    std::string orientation(1, player->getOrientation());
    jsonForClient["orientation"] = orientation;

    return jsonForClient;
}

// Get the json for function Inspect (overloading)
json JsonManage::getJsonClient(std::string action, std::vector<std::unordered_map<std::string, int>> inspected, Map* map, Player* player) {
    json jsonForClient;
    jsonForClient[action] = inspected;
    auto mapClient = map->createPortionMap(player, map);
    jsonForClient["map"] = mapClient;
    std::string orientation(1, player->getOrientation());
    jsonForClient["orientation"] = orientation;

    return jsonForClient;
}

// Get the json for function Me (overloading)
json JsonManage::getJsonClient(std::string action, std::unordered_map<std::string, std::string> me, Map* map, Player* player) {
    json jsonForClient;
    jsonForClient[action] = me;
    auto mapClient = map->createPortionMap(player, map);
    jsonForClient["map"] = mapClient; 
    std::string orientation(1, player->getOrientation());
    jsonForClient["orientation"] = orientation;

    return jsonForClient;
}

json JsonManage::getJsonStart(int id) {
    json jsonStart;
    jsonStart["id"] = id;
    return jsonStart;
}
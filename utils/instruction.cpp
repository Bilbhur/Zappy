#include "instruction.hh"
#include "element_map/empty.hh"

Instruction::Instruction()
{}

Instruction::~Instruction()
{}

bool Instruction::left(Player *p) {
    if (p->getOrientation() == 'N')
        p->setOrientation('W');
    else if (p->getOrientation() == 'W')
        p->setOrientation('S');
    else if (p->getOrientation() == 'S')
        p->setOrientation('E');
    else if (p->getOrientation() == 'E')
        p->setOrientation('N');
    p->consumeEnergy(1);
    return true;
}

bool Instruction::right(Player *p) {
    if (p->getOrientation() == 'N')
        p->setOrientation('E');
    else if (p->getOrientation() == 'E')
        p->setOrientation('S');
    else if (p->getOrientation() == 'S')
        p->setOrientation('W');
    else if (p->getOrientation() == 'W')
        p->setOrientation('N');
    p->consumeEnergy(1);
    return true;
}

bool Instruction::fwd(Player *player, Map *map) {
    
    int x = 0;
    int y = 0;

    std::tie(x, y) = computeValue(player, 1);

    player->consumeEnergy(1);
    if (this->movement(player, map, x, y))
        return true;
    return false;
}

bool Instruction::back(Player *player, Map *map) {
    int x = 0;
    int y = 0;

    std::tie(x, y) = computeValue(player, -1);

    player->consumeEnergy(1);
    if (this->movement(player, map, x, y))
        return true;
    return false;
}

bool Instruction::jump(Player *player, Map *map) {
    int x = 0;
    int y = 0;

    std::tie(x, y) = computeValue(player, 3);

    player->consumeEnergy(2);
    if (this->movement(player, map, x, y))
        return true;
    return false;
}

bool Instruction::leftfwd(Player *p, Map *m) {
    this->left(p);
    p->setEnergy(p->getEnergy()+1);
    if (this->fwd(p, m))
        return true;
    return false;
}

bool Instruction::rightfwd(Player *p, Map *m) {
    this->right(p);
    p->setEnergy(p->getEnergy()+1);
    if (this->fwd(p, m))
        return true;
    return false;
}

// Return a vector of unordered_map, containing id, life, victory
std::vector<std::unordered_map<std::string, int>> Instruction::inspect(Player *player, std::vector<Player*> players) {

    std::vector<std::unordered_map<std::string, int>> vec;

    for(Player *p: players) {
        if (p->getId() != player->getId()) {
            std::unordered_map<std::string, int> umap;
            umap["id"] = p->getId();
            umap["life"] = p->getHitPoints();
            umap["victory"] = p->getVictoryPoints();

            vec.push_back(umap);
        }
    }
    player->consumeEnergy(1);
    return vec;
}

// Return an unordered_map of all information of the current player
std::unordered_map<std::string, std::string> Instruction::me(Player *p) {
    std::unordered_map<std::string, std::string> values;
    
    values["id"] = std::to_string(p->getId());
    values["life"] = std::to_string(p->getHitPoints());
    values["energy"] = std::to_string(p->getEnergy());
    values["victory"] = std::to_string(p->getVictoryPoints());

    // Cast the char into a string by the std::string constructor
    std::string s(1, p->getOrientation());
    values["orientation"] = s;

    return values;
}

bool Instruction::movement(Player *player, Map *map, int posX, int posY) {
    int x = player->getPosX();
    int y = player->getPosY();

    int newX = x + posX;
    int newY = y + posY;
    
    if (map->checkIfInBoard(newX, newY)) {
        // Consume the stone
        if (map->checkIsStone(newX, newY)) 
            map->consumeStone(newX, newY, player);

        // Move the player or hit the ones ahead
        if (!map->getBoard()[newY][newX]->getWalkable()) {
            if (map->checkIsPlayer(newX, newY)) {
                // The cast is needed (Reminder :: the board is a map of AObject !)
                Player *p = static_cast<Player*>(map->getBoard()[newY][newX]);
                p->takeDamage(1);
            }
        }
        else {
            player->movePlayer(newX, newY);
            map->getBoard()[newY][newX] = player;
            map->getBoard()[y][x] = new Empty(x, y);
        }
        return true;
    } else {
        // If cannot do the movement return false
        return false;
    }
}

// Compute the future x and y value for the player from his orientation
std::tuple<int, int> Instruction::computeValue(Player *player, int value) {
    int x = 0;
    int y = 0;
    
    if (player->getOrientation() == 'N')
        y -= value;
    else if (player->getOrientation() == 'E')
        x += value;
    else if (player->getOrientation() == 'S')
        y += value;
    else if (player->getOrientation() == 'W')
        x -= value;

    return {x, y};
}
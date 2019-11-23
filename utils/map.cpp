#include <iostream>
#include <random>
#include <array>
#include <string>
#include "map.hh"
#include "element_map/empty.hh"
#include "element_map/stoneGenerator.hh"
#include "element_map/linemate.hh"
#include "element_map/sibur.hh"
#include "element_map/deraumere.hh"
#include "element_map/mendiane.hh"

Map::Map(int width, int height, int nbPlayers, double spawnPercent):
_width(width),
_height(height),
_nbPlayers(nbPlayers),
_spawnPercent(spawnPercent)
{
    this->createMap();
    this->drawMap();
}

Map::~Map()
{}

int Map::getNbPlayers() const{
    return _nbPlayers;
}

int Map::getWidth() const {
    return this->_width;
}

void Map::setWidth(int width) {
    this->_width = width;
}

int Map::getHeight(void) const {
    return this->_width;
}

void Map::setHeight(int height) {
    this->_height = height;
}

AObject ***Map::getBoard() const {
    return this->_board;
}

AStone* Map::getIStone() const {
    return this->_iStone;
}

// Cast the object at coordonates into AStone
void Map::setIStone(int x, int y) {
    this->_iStone = static_cast<AStone*>(this->_board[y][x]);
}

// Check if you're in the map, avoid NullPointerException (segfault)
bool Map::checkIfInBoard(int x, int y) {
    if (x >= 0 && y >= 0 && x < this->_width && y < this->_height)
        return true;
    return false;
}

// Check if a box is empty on the map
bool Map::checkEmptySet(int x, int y) {
    if (this->checkIfInBoard(x, y))
        if (_board[y][x]->getDisplayer().compare("E") == 0)
            return true;
    return false;
}

// Check if the object at coordonates is a player
bool Map::checkIsPlayer(int x, int y) {
    if (_board[y][x]->getClassName().compare("Player") == 0)
        return true;
    return false;
}

// Check if the object at coordonates is a stone
bool Map::checkIsStone(int x, int y) {
    if (_board[y][x]->getDisplayer().compare("L") == 0 ||
        _board[y][x]->getDisplayer().compare("M") == 0 ||
        _board[y][x]->getDisplayer().compare("D") == 0 ||
        _board[y][x]->getDisplayer().compare("S") == 0)
        return true;
    return false;
}

// Get a random number to place objects and whatever
int Map::getRandom(int range) {

    std::random_device rd; // Obtain a random number from hardware
    std::mt19937 eng(rd()); // Seed the generator
    std::uniform_int_distribution<> distr(0, range-1); // Define the range 

    return distr(eng);
}

// Place a player randomly in the map (overloading)
bool Map::placeObject(int id) {
    int x = this->getRandom(_width);
    int y = this->getRandom(_height);

    if (this->checkEmptySet(x, y)) {
        Player *p = new Player(x, y);
        p->setId(id);
        _board[y][x] = p;
        _players.push_back(p);
        return true;
    }
    return false;
}

// Place a stone randomly in the map (overloading)
bool Map::placeObject() {

    int x = this->getRandom(_width);
    int y = this->getRandom(_height);
    int indexStone = this->getRandom(sizeof(this->_stones)/sizeof(this->_stones[0]));
    StoneGenerator *sg = new StoneGenerator();

    if (this->checkEmptySet(x, y)) {
        AStone *stone = sg->createStone(this->_stones[indexStone]);

        stone->setPosX(x);
        stone->setPosY(y);

        _board[y][x] = stone;
        return true;
    }
    return false;
}

// Place a random stone randomly in the map (overloading)
bool Map::placeObject(double spawnPercent) {

    int indexStone;
    int nbBoxes = this->_height * this->_width;
    int nbStones = nbBoxes * spawnPercent;
    int nbBoxesEmpty = nbBoxes - this->_nbPlayers;

    StoneGenerator *sg = new StoneGenerator();

    if(nbBoxesEmpty < nbStones) {
        // Place a stone in each empty boxe

        indexStone = this->getRandom(sizeof(this->_stones)/sizeof(this->_stones[0]));
        for(int i = 0; i < this->_height; i++) 
            for(int j = 0; j < this->_width; j++) 
                this->_board[i][j] = sg->createStone(this->_stones[indexStone]);
    } else
        // Place a stone in a percentage boxes of the map
        for(int s = 0; s < nbStones;)
            // Check if a stone is successfully placed
            if (this->placeObject())
                // Increase the number of stone placed
                s++;
    return true;
}

// Create the full map
void Map::createMap() {
    // Allocate memory of the first array of pointers
    this->_board = new AObject**[this->_height];

    for(int i = 0; i < this->_height; i++) {
        // Allocate memory of the second array of pointers
        this->_board[i] = new AObject*[this->_width];

        for(int j = 0; j < this->_width; j++)
            this->_board[i][j] = new Empty(i, j);
    }

    for(int k = 1; k < this->_nbPlayers+1;)
        if (this->placeObject(k))
            k++;

    this->placeObject(this->_spawnPercent);
}

// Draw the map on the CLI
void Map::drawMap() {
    int x = 0;
    int y = 0;

    for(int i = 0; i < (this->_height*2+1); i++) {
        if(i == 0) {
            for(int j = 0; j < this->_width; j++) {
                if(j == 0) {
                    std::cout << "┌───";
                } else if( j == this->_width-1) {
                    std::cout << "┬───┐" << std::endl;
                } else {
                    std::cout << "┬───";
                }
            }
        } else if (i == this->_height*2) {
            for(int j = 0; j < this->_width; j++) {
                if(j == 0) {
                    std::cout << "└───";
                } else if( j == this->_width-1) {
                    std::cout << "┴───┘" << std::endl;
                } else {
                    std::cout << "┴───";
                }
            }
        } else if(i%2 == false) {
            for(int j = 0; j < this->_width; j++) {
                if(j == 0) {
                    std::cout << "├───";
                } else if( j == this->_width-1) {
                    std::cout << "┼───┤" << std::endl;
                } else {
                    std::cout << "┼───";
                }
            }
        } else {
            for(int j = 0; j < this->_width; j++) {
                if(j == this->_width-1) {
                    if(this->checkEmptySet(x, y)) {
                        std::cout << "│   │" << std::endl;
                    } else {
                        std::cout << "│ " << this->_board[y][x]->getDisplayer() << " │" << std::endl;
                    }
                    x = 0;
                    y++;
                } else {
                    if(this->checkEmptySet(x, y)) {
                        std::cout << "│   ";
                    } else {
                        std::cout << "│ " << this->_board[y][x]->getDisplayer() << " ";
                    }
                    x++;
                }
            }
        }
    }

}

// Return a vector of string of the portion map to the player
// Implementation incoming…
std::array<std::string, 4> Map::createPortionMap(Player *player, Map* map) {

    std::array<std::string, 4> resultTab{"V"};
    char wall = 'W';
    int xMax{map->getWidth() - 1}, yMax{map->getHeight() - 1}, x{player->getPosX()}, y{player->getPosY()};

    if (player->getOrientation() == 'N') {
        if (y - 1 < 0 || x - 1 < 0)
            resultTab[0] = wall;
        else
            resultTab[0] = map->_board[y-1][x-1]->getDisplayer();

        if (y - 1 < 0)
            resultTab[1] = wall;
        else 
            resultTab[1] = map->_board[y-1][x]->getDisplayer();

        if (y - 1 < 0 || x + 1 > xMax) 
            resultTab[2] = wall;
        else
            resultTab[2] = map->_board[y-1][x+1]->getDisplayer();

        if (y -2 < 0)
            resultTab[3] = wall;
        else
            resultTab[3] = map->_board[y-2][x]->getDisplayer();

    } else if (player->getOrientation() == 'E') {
        if (y - 1 < 0 || x + 1 > xMax)
            resultTab[0] = wall;
        else
            resultTab[0] = map->_board[y-1][x+1]->getDisplayer();
        
        if (x + 1 > xMax)
            resultTab[1] = wall;
        else
            resultTab[1] = map->_board[y][x+1]->getDisplayer();
        
        if (y + 1 > yMax || x + 1 > xMax)
            resultTab[2] = wall;
        else
            resultTab[2] = map->_board[y+1][x+1]->getDisplayer();
        
        if (x + 2 > yMax)
            resultTab[3] = wall;
        else
            resultTab[3] = map->_board[y][x+2]->getDisplayer();

    } else if (player->getOrientation() == 'S') {
        if (y + 1 > yMax || x + 1 > xMax)
            resultTab[0] = wall;
        else
            resultTab[0] = map->_board[y+1][x+1]->getDisplayer();
        
        if (y + 1 > yMax)
            resultTab[1] = wall;
        else
            resultTab[1] = map->_board[y+1][x]->getDisplayer();

        if (y + 1 > yMax || x - 1 < 0)
            resultTab[2] = wall;
        else
            resultTab[2] = map->_board[y+1][x-1]->getDisplayer();

        if (y + 2 > yMax)
            resultTab[3] = wall;
        else
            resultTab[3] = map->_board[y+2][x]->getDisplayer();
    
    } else if (player->getOrientation() == 'W') {
        if (y + 1 > yMax || x - 1 < 0)
            resultTab[0] = wall;
        else
            resultTab[0] = map->_board[y+1][x-1]->getDisplayer();
        
        if (x - 1 < 0)
            resultTab[1] = wall;
        else
            resultTab[1] = map->_board[y][x-1]->getDisplayer();
        
        if (y - 1 < 0 || x - 1 < 0)
            resultTab[2] = wall;
        else
            resultTab[2] = map->_board[y-1][x-1]->getDisplayer();

        if (x - 2 < 0)
            resultTab[3] = wall;
        else
            resultTab[3] = map->_board[y][x-2]->getDisplayer();
    }
    return resultTab;
}

std::vector<Player*> Map::getPlayers() const {
    return _players;
}

// Cast the AObject at [x, y] in a stone to use the consumption method
void Map::consumeStone(int x, int y, Player *p) {
    if (this->checkIsStone(x, y)) {
        std::cout << "CONSUMPTION" << std::endl;
        this->setIStone(x, y);
        _iStone->consume(p, this->getPlayers());
    }
}
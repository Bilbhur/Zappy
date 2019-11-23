#ifndef SERVER_HH
#define SERVER_HH

#include "../utils/aBaseNetwork.hh"
#include "../utils/aCommand.hh"
#include "../utils/map.hh"
#include <SFML/Network.hpp>
#include <vector>
#include <cstdlib>
#include "../utils/json.hpp"

using json = nlohmann::json;

class Server: public ABaseNetwork, public ACommand {
    public:
        Server(const std::string host, const int port, unsigned short nbPlayers, int cycleGame);
        ~Server();
        void runServer();
        void addMap(Map* map);
        void clearOutput(void);

        json handleCmd(std::string cmd, std::vector<Player*> players, int id);

    private:
        const unsigned short _nbPlayers;
        std::vector<sf::TcpSocket*> _clients;
        unsigned int _clientID;
        Map* _map;
        const int _cycleGame;
};

#endif // SERVER_HH

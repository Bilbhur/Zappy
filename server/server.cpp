#include <iostream>
#include <string>
#include <sstream>
#include <exception>
#include <SFML/Network.hpp>
#include <thread>
#include <algorithm>
#include "server.hh"
#include "../utils/jsonManage.hh"
#include "../utils/json.hpp"
#include "../utils/element_map/player.hh"
#include "../utils/instruction.hh"
#include "../utils/map.hh"

Server::Server(const std::string host,
               const int port,
               const unsigned short nbPlayers,
               int cycleGame): ABaseNetwork(host, port), _nbPlayers(nbPlayers), _cycleGame(cycleGame) {}

Server::~Server() {
    delete _map;
}

void Server::runServer() {
    sf::Packet receivePacket, sendPacket;
    JsonManage jsonClient;
    std::string dataReceive;
    // Instruction instruction;

    std::thread threadGetCommands(&Server::getCommands, this);

    threadGetCommands.detach();

    sf::TcpListener listener;
    if (listener.listen(this->getPort(), this->getHost()) != sf::Socket::Done) {
        std::cerr << "Could not listen on port " << this->getPort() << std::endl;
        exit(EXIT_FAILURE);
    }
    sf::SocketSelector selector;
    selector.add(listener);
    std::cout << "Waiting for incoming connection ..." << std::endl;

    int i = 0;

    // Lobby loop waiting for all players to join the server
    while(!this->getQuit() && i < this->_nbPlayers) {
        if (selector.wait()) {
            if (selector.isReady(listener)) {
                sf::TcpSocket* client = new sf::TcpSocket;
                if (listener.accept(*client) == sf::Socket::Done) {
                    std::cout << "A new client has joined the server" << std::endl;
                    selector.add(*client);
                    client->setBlocking(false);
                    this->_clients.push_back(client);
                    i++;
                }
            }
        }
        for (std::size_t j = 0; j < this->_clients.size(); j++) {
            if (this->_clients[j]->receive(receivePacket) == sf::Socket::Disconnected) {
                this->_clients.erase(this->_clients.begin() + j);
                std::cout << "Disconnected during the lobby" << std::endl;
                i--;
            }
        }
    }
    this->_clientID = 0;

    // Starting loop to notify client the game can begin by sending packets
    for (std::size_t j = 0; j < this->_clients.size(); j++) {
        std::cout << "Start packet has been send to client " << this->_clientID << std::endl;
        sendPacket << jsonClient.getJsonStart(this->_clientID).dump();
        if (this->_clients[j]->send(sendPacket) != sf::Socket::Done) {
            std::cerr << "Player " << j << " is not reachable" << std::endl;
        } else {
            this->_clientID += 1;
        }
        sendPacket.clear();
    }

    sf::Clock timerGameCycle;
    int cmpPlayerLose{0};
    auto players = this->_map->getPlayers();

    if (!this->getQuit()) {
        std::cout << "All players are connected, starting the game ..." << std::endl;
        sf::Clock timer;
        while (!this->getQuit()) {

            // Client action
            if (timerGameCycle.getElapsedTime().asMilliseconds() < this->_cycleGame) {
                if (timer.getElapsedTime().asMilliseconds() > 50) {
                    for (std::size_t i = 0; i < this->_clients.size(); i++) {
                        sf::Packet receivePacket, sendPacket;
                        
                        // Handle the command send by the client
                        if (this->_clients[i]->receive(receivePacket) == sf::Socket::Done) {

                            receivePacket >> dataReceive;
                            auto receiveJson = json::parse(dataReceive);
                            int id;
                            std::istringstream(receiveJson["id"].dump()) >> id;


                            // Affichage de debug
                            std::cout << "Id d'un player : " << players[id]->getId() << std::endl;                        
                            std::cout << "Energie : " << players[id]->getEnergy() << std::endl;
                            

                            // Send the command return to the client
                            sendPacket << this->handleCmd(receiveJson["command"], players, id).dump();

                            if (this->_clients[i]->send(sendPacket) != sf::Socket::Done)
                                return;
                                
                            this->_map->drawMap();
                        }

                        // If client is disconnected, erase it from the client list
                        else if (this->_clients[i]->receive(receivePacket) == sf::Socket::Disconnected) {
                            std::cout << "Client " << i << " disconnected" << std::endl;
                            this->_clients.erase(this->_clients.begin() + i);

                            // If client list size is 1, end the game
                            if (this->_clients.size() == 1) {
                                std::cout << "No client left, closing the server ..." << std::endl;
                                this->quit();
                            }
                        }
                    }
                    timer.restart();
                }
            } else {
                // Game lap starting
                timerGameCycle.restart();

                // Foreach players
                std::for_each(players.begin(), players.end(), [&cmpPlayerLose](Player* player){
                    if (player->isAlive() == true) {
                        cmpPlayerLose = cmpPlayerLose + 1;
                    }
                    player->setEnergy(2);
                });

                // TODO victory function
                // It only one player's left
                if (cmpPlayerLose <= _map->getNbPlayers() - 2) {
                    std::cout << "Game finish !!!" << std::endl;
                    return;
                }
                cmpPlayerLose = 0;

                _map->placeObject();
                
                // Clean & print again the map
                this->clearOutput();
                this->_map->drawMap();
            }
        }
    }
}

void Server::addMap(Map* map) {
    _map = map;
}

void Server::clearOutput() {
    std::system("clear");
}

json Server::handleCmd(std::string cmd, std::vector<Player*> players, int id) {

    JsonManage jsonClient;
    Instruction instruction;
    bool status = false;
    std::vector<std::unordered_map<std::string, int>> cmd_inspect;
    std::unordered_map<std::string, std::string> cmd_me;

    json toto;

    if(cmd == "me")
        cmd_me = instruction.me(players[id]);
    else {
        if (players[id]->checkEnergy()) {   
            if(cmd == "right")
                status = instruction.right(players[id]);
            else if(cmd == "left")
                status = instruction.left(players[id]);
            else if(cmd == "fwd")
                status = instruction.fwd(players[id], _map);
            else if(cmd == "leftfwd")
                status = instruction.leftfwd(players[id], _map);
            else if(cmd == "rightfwd")
                status = instruction.rightfwd(players[id], _map);
            else if(cmd == "jump")
                if (players[id]->getEnergy() > 1)
                    status = instruction.jump(players[id], _map);
                else
                    status = false;
            else if(cmd == "back")
                status = instruction.back(players[id], _map);
            else if(cmd == "inspect")
                cmd_inspect = instruction.inspect(players[id], players);
        }
    }
    
    std::string state = status ? "OK" : "KO";

    if (cmd == "me")
        toto = jsonClient.getJsonClient(cmd, cmd_me, _map, players[id]);
    else if (cmd == "inspect")
        toto = jsonClient.getJsonClient(cmd, cmd_inspect, _map, players[id]);
    else
        toto = jsonClient.getJsonClient(cmd, state, _map, players[id]);

    return toto;
}
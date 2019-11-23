#include "client.hh"
#include "../utils/json.hpp"
#include <iostream>

Client::Client(const std::string host, const int port): ABaseNetwork(host, port) {}

int Client::sendCommands() {
    return 0;
}

int Client::getId() {
    return this->_id;
}

void Client::setId(int id) {
    this->_id = id;
}

void Client::setReady() {
    _ready = true;
}

bool Client::getReady() {
    return _ready;
}

void Client::runClient() {
    sf::Clock timer, timeout;
    sf::Packet receivePacket, sendPacket;
    std::string dataReceive;
    JsonManage jsonClient;

    if (this->_socket.connect(this->getHost(), this->getPort()) != sf::Socket::Done) {
        std::cerr << "Error while connecting to the server" << std::endl;
        exit(EXIT_FAILURE);
    }
    // Set the this->_socket blocking state to not waiting for data to return
    this->_socket.setBlocking(true);
    std::cout << "Connected to server: " << this->getHost() << std::endl;

    std::cout << "Waiting for players to start" << std::endl;

    // Lobby loop waiting for all clients to be connected
    while (this->_socket.receive(receivePacket) != sf::Socket::Done) {
        if (this->_socket.receive(receivePacket) == sf::Socket::Disconnected) {
            std::cerr << "Server is not reachable, disconnecting ..." << std::endl;
            this->quit();
            exit(EXIT_FAILURE);
        }
    }
    std::cout << "Server is ready, starting the game ..." << std::endl;

    receivePacket >> dataReceive;
    json receiveJson = json::parse(dataReceive);
    this->setId(receiveJson["id"]);
    std::cout << "id server :" << receiveJson["id"] << this->getId() << "json : " << receiveJson.dump(4) << std::endl;

    std::string command;
    while (!this->getQuit()) {
        while (std::cin >> command && (command != "exit" || command != "quit")) {
            if (command == "left" || command == "right" || command == "fwd" || 
                command == "leftfwd" || command == "rightfwd" || command == "jump" ||
                command == "back" || command == "inspect" || command == "me") {
                sf::Packet receivePacket, sendPacket;
                sendPacket << this->getJsonServer(command, this->getId()).dump();

                if (this->_socket.send(sendPacket) == sf::Socket::Done) {
                    std::cout << "Sending command to server " << command << std::endl;
                    if (this->_socket.receive(receivePacket) == sf::Socket::Done) {
                        receivePacket >> dataReceive;
                        auto receiveJson = json::parse(dataReceive);
                        std::cout << command << std::endl;
                        std::cout << "Server response: " << receiveJson.dump(4) << std::endl;

                        std::array<std::string, 4> tabMap = receiveJson["map"];
                        std::cout << tabMap[1] << std::endl;
                        std::string orientation = receiveJson["orientation"]; 
                        std::cout << orientation << std::endl;
                        this->displayMapClient(tabMap, orientation);
                    }
                } else {
                //  If could not send packet to the server, wait and exit
                    std::cout << "Server is not reachable, waiting for 5 seconds ..." << std::endl;
                    sf::Packet sendPacket;
                    while(this->_socket.send(sendPacket) != sf::Socket::Done && !this->getQuit()) {
                        if (timeout.getElapsedTime().asSeconds() > 5) {
                            std::cerr << "Exiting, server not reachable..." << std::endl;
                            exit(EXIT_FAILURE);
                        }
                    }
                }
                command.clear();
            } else if (command == "exit" || command == "quit") {
                std::cout << "Quit !!! " << command << std::endl;
                this->quit();
                return;
            } else {
                std::cout << "To quit the server, type 'exit' or 'quit': " << command << std::endl;
            }
        }
    }
}

void Client::getCommands() {
    sf::Clock timeout;
    std::string dataReceive, command;

    while (std::cin >> command && (command != "exit" || command != "quit" || command != "stop")) {
        if (command == "exit" || command == "quit") {
            std::cout << "Bye !!! " << command << std::endl;
            exit(EXIT_SUCCESS);
        } else {
            std::cout << "To quit the server, type 'exit' or 'quit': " << command << std::endl;
        }
    }
}

void Client::startThreadGetCommands() {
    try{
        std::thread threadGetCommands(&Client::getCommands, this);
        _threadGetCommands = &threadGetCommands;
    } catch (...) {
        std::cout << "fail" << std::endl;
    }

}

void Client::stopThreadGetCommands() {
    _threadGetCommands->detach();
}

// Draw the portion of map for the player
void Client::displayMapClient(std::array<std::string, 4> mapClient, std::string orientation) {
    // example when the player is pointing north
    // std::cout << "    ┌───┐    " << std::endl;
    // std::cout << "    │   │    " << std::endl;
    // std::cout << "┌───┼───┼───┐" << std::endl;
    // std::cout << "│   │   │   │" << std::endl;
    // std::cout << "└───┼───┤───┘" << std::endl;
    // std::cout << "    │ ▲ │    " << std::endl;
    // std::cout << "    └───┘    " << std::endl;
    int w = 3;
    std::string empty = "E";

    std::cout << " orientation in function : " << orientation << std::endl;
    if(orientation == "N"){
        std::cout << "    ┌───┐    " << std::endl;
        if(mapClient[3] == empty) {
            std::cout << "    │   │    " << std::endl;
        } else {
            std::cout << "    │ " << mapClient[3] << " │    " << std::endl;
        }  
        std::cout << "┌───┼───┼───┐" << std::endl;
        for(int j = 0; j < w; j++) {
            if(j == w - 1) {
                if(mapClient[j] == empty) {
                    std::cout << "│   │" << std::endl;
                } else {
                    std::cout << "│ " << mapClient[j] << " │" << std::endl;
                }
            } else {
                if(mapClient[j] == empty) {
                    std::cout << "│   ";
                } else {
                    std::cout << "│ " << mapClient[j] << " ";
                }
            }
        }
        std::cout << "└───┼───┤───┘" << std::endl;
        std::cout << "    │ ▲ │    " << std::endl;
        std::cout << "    └───┘    " << std::endl; 
    } 
    else if(orientation == "E") {
        std::cout << "    ┌───┐    " << std::endl;
        if(mapClient[0] == empty) {
            std::cout << "    │   │    " << std::endl;
        } else {
            std::cout << "    │ " << mapClient[0] << " │    " << std::endl;
        }  
        std::cout << "┌───┼───┼───┐" << std::endl;
        for(int j = 0; j < w; j++) {
            if(j == 0) {
                std::cout << "│ ► ";
            } else if(j == w - 1) {
                if(mapClient[3] == empty) {
                    std::cout << "│   │" << std::endl;
                } else {
                    std::cout << "│ " << mapClient[3] << " │" << std::endl;
                }
            } else {
                if(mapClient[1] == empty) {
                    std::cout << "│   ";
                } else {
                    std::cout << "│ " << mapClient[1] << " ";
                }
            }
        }
        std::cout << "└───┼───┤───┘" << std::endl;
        if(mapClient[2] == empty) {
            std::cout << "    │   │    " << std::endl;
        } else {
            std::cout << "    │ " << mapClient[2] << " │    " << std::endl;
        } 
        std::cout << "    └───┘    " << std::endl; 
    } else if(orientation == "S") {
        std::cout << "    ┌───┐    " << std::endl;
        std::cout << "    │ ▼ │    " << std::endl;
        std::cout << "┌───┼───┼───┐" << std::endl;
        for(int j = 0; j < w; j++) {
            if(j == w - 1) {
                if(mapClient[2 - j] == empty) {
                    std::cout << "│   │" << std::endl;
                } else {
                    std::cout << "│ " << mapClient[2 - j]  << " │" << std::endl;
                }
            } else {
                if(mapClient[2 - j] == empty) {
                    std::cout << "│   ";
                } else {
                    std::cout << "│ " << mapClient[2 - j] << " ";
                }
            }
        }
        std::cout << "└───┼───┤───┘" << std::endl;
        if(mapClient[3] == empty) {
            std::cout << "    │   │    " << std::endl;
        } else {
            std::cout << "    │ " << mapClient[3] << " │    " << std::endl;
        }  
        std::cout << "    └───┘    " << std::endl; 
    } else if(orientation == "W") {
        std::cout << "    ┌───┐    " << std::endl;
        if(mapClient[2] == empty) {
            std::cout << "    │   │    " << std::endl;
        } else {
            std::cout << "    │ " << mapClient[2] << " │    " << std::endl;
        }  
        std::cout << "┌───┼───┼───┐" << std::endl;
        for(int j = 0; j < w; j++) {
            if(j == w - 1) {
                std::cout << "│ ◄ │" << std::endl;
            } else if(j == 0) {
                if(mapClient[3] == empty) {
                    std::cout << "│   ";
                } else {
                    std::cout << "│ " << mapClient[3] << " ";
                }
            } else {
                if(mapClient[1] == empty) {
                    std::cout << "│   ";
                } else {
                    std::cout << "│ " << mapClient[1] << " ";
                }
            }
        }
        std::cout << "└───┼───┤───┘" << std::endl;
        if(mapClient[0] == empty) {
            std::cout << "    │   │    " << std::endl;
        } else {
            std::cout << "    │ " << mapClient[0] << " │    " << std::endl;
        } 
        std::cout << "    └───┘    " << std::endl; 
    }
}
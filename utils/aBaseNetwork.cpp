#include "aBaseNetwork.hh"
#include <iostream>

ABaseNetwork::ABaseNetwork(std::string host, int port): _host(host), _port(port) {

}

ABaseNetwork::~ABaseNetwork() {

}

std::string ABaseNetwork::getHost() const {
    return this->_host;
}

int ABaseNetwork::getPort() const {
    return this->_port;
}

// void ABaseNetwork::handleArgs(char **argv) {
//     argv[0][0] = 'a';
//     std::cout << "Handle arguments" << std::endl;
// }
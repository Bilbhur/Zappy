#include "aCommand.hh"
#include <iostream>

ACommand::ACommand() {
    _quit = false;
}

ACommand::~ACommand() {
    
}

void ACommand::getCommands() {
    std::string command;
    while (std::cin >> command) {
        if (command == "exit" || command == "quit") {
            // TODO IMPLEMENTATION OF DESTROY SERVER
            this->_mQuit.lock();
            this->quit();
            this->_mQuit.unlock();
            return;
        } else {
            std::cout << "To quit the server, type 'exit' or 'quit': " << command << std::endl;
        }
    }
}

void ACommand::quit() {
    _quit = true;
}

bool ACommand::getQuit() const {
    return _quit;
}

int ACommand::sendCommands() {
    return 0;
}
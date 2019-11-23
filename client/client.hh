#ifndef CLIENT_HH
#define CLIENT_HH

#include <SFML/Network.hpp>
#include <thread>
#include "../utils/aCommand.hh"
#include "../utils/aBaseNetwork.hh"
#include "../utils/jsonManage.hh"

class Client: public ABaseNetwork, public ACommand, public JsonManage {
    public:
        Client(const std::string host, const int port);
        void runClient();
        int sendCommands() override;
        void getCommands() override;
        static void * testcmd(void *);
        void startThreadGetCommands();
        void stopThreadGetCommands();
        void setId(int id);
        int getId();
        void setReady();
        bool getReady();
        void displayMapClient(std::array<std::string, 4>  mapClient, std::string orientation);
    private:
        std::thread* _threadGetCommands;
        bool threadGetCommandsRunning{true};
        sf::TcpSocket _socket;
        int _id;
        bool _ready{false};
};

#endif // CLIENT_HH

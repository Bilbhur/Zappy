#ifndef A_BASE_NETWORK_HH
#define A_BASE_NETWORK_HH

#include <string>

class ABaseNetwork
{
    private:
        std::string _host;
        int _port;
    public:
        ABaseNetwork(std::string host, int port);
        virtual ~ABaseNetwork() = 0;

        std::string getHost(void) const;
        int getPort(void) const;

        // void handleArgs(char ** argv);
};

#endif // A_BASE_NETWORK_HH
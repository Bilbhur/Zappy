#include "server.hh"
#include "../utils/map.hh"
#include <boost/program_options.hpp>
#include <iostream>
#include <vector>

namespace po = boost::program_options;

void usage(const po::options_description &desc) {
    std::cout << desc << std::endl;
    exit(EXIT_SUCCESS);
}

Server* initServer(const int argc, const char **argv) {
    std::string host;
    unsigned short port, nbPlayers;
    int cycleGame, mapHeight, mapWidth;
    double spawnPercent;
    try {
        po::options_description desc("Options");
        desc.add_options()
            ("help,h", "Help description")
            ("map-height", po::value<int>(&mapHeight)->default_value(5), "Map height")
            ("map-width", po::value<int>(&mapWidth)->default_value(5), "Map width")
            ("host", po::value<std::string>(&host)->default_value("127.0.0.1"), "Server listen host")
            ("port", po::value<unsigned short>(&port)->default_value(4242), "Server listen port")
            ("players", po::value<unsigned short>(&nbPlayers)->default_value(4), "Total players")
            ("cycle", po::value<int>(&cycleGame)->default_value(500), "Game cycle duration in ms")
            ("stone-percent", po::value<double>(&spawnPercent)->default_value(0.5), "Stone spawn percentage");
        po::variables_map args;
        po::store(
            po::parse_command_line(argc, argv, desc),
            args
        );
        po::notify(args);

        if (args.count("help")) {
            usage(desc);
        }
        if (args.count("map-height")) {
            if (mapHeight > 0) {
                std::cout << "Map height: " << mapHeight << std::endl;
            } else {
                std::cout << "Bad map height: " << mapHeight << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        if (args.count("map-width")) {
            if (mapWidth > 0) 
                std::cout << "Map width: " << mapWidth << std::endl;
            else {
                std::cout << "Bad map width: " << mapWidth << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        if (args.count("host")) {
            if (host.size() >= 7 && host.size() <= 15) {
                for (size_t i = 0; i < host.size(); i++) {
                    if (!isdigit(host[i]) && host[i] != '.') {
                        std::cout << "Bad Host: " << host << std::endl;
                        exit(EXIT_FAILURE);
                    }
                }
                std::cout << "Host: " << host << std::endl;
            } else {
                std::cout << "Bad host: " << host << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        if (args.count("port")) {
            if (port > 0 && port < 65535) {
                std::cout << "Port: " << port << std::endl;
            } else {
                std::cout << "Bad port: " << port << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        if (args.count("players")) {
            if (nbPlayers > 0 && nbPlayers <= (mapWidth * mapHeight))
                std::cout << "Players: " << nbPlayers << std::endl;
            else {
                std::cout << "Bad number of players: " << nbPlayers << " must be less or equal to number max of case" << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        if (args.count("cycle")) {
            if (cycleGame >= 500)
                std::cout << "Cycle: " << cycleGame << std::endl;
            else {
                std::cout << "Bad time cycle: " << cycleGame << " must be more than 500" <<std::endl;
                exit(EXIT_FAILURE);
            }
        }
        if (args.count("stone-percent")) {
            if (spawnPercent >= 0 && spawnPercent <= 1)
                std::cout << "Stone percent: " << spawnPercent << std::endl;
            else {
                std::cout << "Bad stone percent: " << spawnPercent << " must be between 0 and 1" << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        Map* map = new Map{mapWidth, mapHeight, nbPlayers, spawnPercent};

        Server* server = new Server{host, port, nbPlayers, cycleGame};

        server->addMap(map);
        return server;
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
}

int main(const int argc, const char **argv) {
    auto server = initServer(argc, argv);
    server->runServer();
    delete server;

    return 0;
}
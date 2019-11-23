#include "client.hh"
#include <string>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

void usage(const po::options_description &desc) {
    std::cout << desc << std::endl;
    exit(EXIT_SUCCESS);
}

Client* initClient(const int argc, const char **argv) {
    std::string host;
    unsigned short port;

    try {
        po::options_description desc("Options");
        desc.add_options()
            ("help,h", "Help description")
            ("host", po::value<std::string>(&host)->default_value("127.0.0.1"), "Server listen host")
            ("port", po::value<unsigned short>(&port)->default_value(4242), "Server listen port");
        po::variables_map args;
        po::store(
            po::parse_command_line(argc, argv, desc),
            args
        );
        po::notify(args);

        if (args.count("help")) {
            usage(desc);
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
                std::cout << "Bad Host: " << host << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        if (args.count("port")) {
            if (port > 0 && port < 65535) {
                std::cout << "Port: " << port << std::endl;
            } else {
                std::cout << "Bad Port: " << port << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        Client* client = new Client{host, port};
        return client;
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
}

int main(const int argc, const char **argv) {
    auto client = initClient(argc, argv);
    client->runClient();
    delete client;

    return 0;
}

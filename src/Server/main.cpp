/*
** EPITECH PROJECT, 2026
** network
** File description:
** main
*/

#include <iostream>

#include "TcpServer.hpp"

int main(const int argc, const char *argv[])
{
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <port>" << std::endl;
        return 84;
    }

    TCPServer server{std::atoi(argv[1]), "127.0.0.1"};

    server.run();

    return 0;
}

/*
** EPITECH PROJECT, 2026
** network
** File description:
** main
*/

#include <iostream>

#include "TcpServer.hpp"

int main()
{
    TCPServer server{4242, "127.0.0.1"};

    server.run();

    return 0;
}

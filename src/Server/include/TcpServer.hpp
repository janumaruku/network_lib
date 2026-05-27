/*
** EPITECH PROJECT, 2026
** network
** File description:
** TcpServer
*/

#pragma once

#include <string>

#include "Acceptor.hpp"
#include "IoContext.hpp"

class TCPServer {
public:
    TCPServer() = delete;

    explicit TCPServer(const std::string &host, const int &port);

    ~TCPServer() = default;

    void run();

private:
    std::string _host;
    int _port;
    network::IOContext _ioContext;
    network::Acceptor _acceptor;

    void startAccept();
};

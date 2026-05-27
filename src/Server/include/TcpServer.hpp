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

    explicit TCPServer(const int &port, const std::string &host);

    ~TCPServer() = default;

    void run();

private:
    network::IOContext _ioContext;
    network::Acceptor _acceptor;

    void startAccept();
};

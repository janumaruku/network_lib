/*
** EPITECH PROJECT, 2026
** network
** File description:
** TcpClient
*/

#pragma once

#include <string>

#include "ConnectedSocket.hpp"
#include "IoContext.hpp"

class TCPClient {
public:
    TCPClient() = delete;

    explicit TCPClient(const int &port, const std::string &host);

    ~TCPClient() = default;

    void send(const std::string &message) const;

    std::string receive();

private:
    int _port;
    std::string _host;
    network::ConnectedSocket _socket;
    network::IOContext _ioContext;
    std::string _readBuffer;
    std::string _transmission;
};

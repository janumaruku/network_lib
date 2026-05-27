/*
** EPITECH PROJECT, 2026
** network
** File description:
** ClientSession
*/

#pragma once
#include <memory>

#include "ConnectedSocket.hpp"

class ClientSession {
public:
    explicit ClientSession(
        const std::shared_ptr<network::ConnectedSocket> &socket);

    void start();

private:
    std::shared_ptr<network::ConnectedSocket> _socket;
    std::string _readBuffer;
    std::string _writeBuffer;
    std::string _transmission;

    void handleRead();

    void handleWrite();

    void handleTransmission(const size_t &bytes);
};

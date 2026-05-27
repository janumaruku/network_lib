/*
** EPITECH PROJECT, 2026
** network
** File description:
** ClientSession
*/

#include "ClientSession.hpp"

ClientSession::ClientSession(
    const std::shared_ptr<network::ConnectedSocket> &socket): _socket{socket}
{
    _readBuffer.resize(1024);
}

void ClientSession::start()
{
    handleRead();
}

void ClientSession::handleRead()
{
    _socket->asyncReadSome(network::buffer(_readBuffer, _readBuffer.size()),
        [this](const auto &error, const auto &bytes) {
            if (error) {
                std::cerr << "Error: " << error.message() << std::endl;
                return;
            }

            if (bytes == 0) {
                std::cerr << "Connection closed" << std::endl;
                return;
            }

            handleTransmission(bytes);
        });
}

void ClientSession::handleWrite()
{
    _writeBuffer += "\r\n";

    _socket->asyncWrite(network::buffer(_writeBuffer), [](auto, auto) {});
}

void ClientSession::handleTransmission(const size_t &bytes)
{
    _transmission.append(_readBuffer.begin(), _readBuffer.begin() + bytes);

    if (_transmission.ends_with("\r\n")) {
        _transmission.erase(_transmission.end() - 2);
        std::cout << _transmission << std::endl;

        // Send _data to a processor function or a dispatcher to
        // be interpreted.

        _writeBuffer = "Message received...";
        handleWrite();

        _transmission.clear();
        handleRead();
        return;
    }

    handleRead();
}

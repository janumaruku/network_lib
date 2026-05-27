/*
** EPITECH PROJECT, 2026
** network
** File description:
** TcpClient
*/

#include "TcpClient.hpp"

TCPClient::TCPClient(const int &port, const std::string &host): _port{port},
    _host{host}, _socket{_ioContext}
{
    network::Endpoint endpoint{port, host};
    _socket.connect(endpoint);
    std::cout << receive() << std::endl;
    std::cout << "Connected to " << _host << ":" << _port << std::endl;
}

void TCPClient::send(const std::string &message) const
{
    _socket.write(network::buffer(message + "\r\n"),
        [](auto, auto) {});
}

std::string TCPClient::receive()
{
    _transmission.clear();

    while (!_transmission.ends_with("\r\n")) {
        _socket.read(network::buffer(_readBuffer, _readBuffer.size()),
            [this](const std::error_code &error, const size_t &bytes) {
                if (error) {
                    throw std::runtime_error(error.message());
                }

                _transmission.insert(_transmission.end(), _readBuffer.begin(),
                    _readBuffer.begin() + bytes);
            });
    }

    _transmission.erase(_transmission.end() - 2);

    return _transmission;
}

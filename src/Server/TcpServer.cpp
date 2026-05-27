/*
** EPITECH PROJECT, 2026
** network
** File description:
** TcpServer
*/

#include "TcpServer.hpp"

TCPServer::TCPServer(const std::string &host, const int &port): _host{host},
    _port{port}, _acceptor{_ioContext, network::Endpoint{port}}
{}

void TCPServer::run()
{
    startAccept();
    _ioContext.run();
}

void TCPServer::startAccept()
{
    _acceptor.asyncAccept([this](const std::error_code &error,
        const std::shared_ptr<network::ConnectedSocket> &socket) {
            if (error) {
                std::cerr << "Error: " << error.message() << std::endl;
                startAccept();
                return;
            }

            const auto endpoint = socket->remoteEndpoint();
            std::cout << "Connection accepted from: " << endpoint.
                getHostname() << ":" << endpoint.getPort() << std::endl;

            socket->write(network::buffer(std::string{"Connection accepted"}),
                [](auto, auto) {});
            startAccept();
        });
}

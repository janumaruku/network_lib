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

    std::cerr << "RETRY_ACCEPT  " << strerror(EAGAIN) << std::endl;
    std::cerr << "RETRY_ACCEPT  " << strerror(EWOULDBLOCK) << std::endl;
    std::cerr << "ACCEPT_BAD_FILE_DESCRIPTOR  " << strerror(EBADF) << std::endl;
    std::cerr << "RETRY_ACCEPT  " << strerror(ECONNABORTED) << std::endl;
    std::cerr << "ACCEPT_BAD_ADDRESS  " << strerror(EFAULT) << std::endl;
    std::cerr << "RETRY_ACCEPT  " << strerror(EINTR) << std::endl;
    std::cerr << "ACCEPT_INVALID_STATE  " << strerror(EINVAL) << std::endl;
    std::cerr << "ACCEPT_RESOURCE_EXHAUSTED  " << strerror(EMFILE) << std::endl;
    std::cerr << "ACCEPT_RESOURCE_EXHAUSTED  " << strerror(ENOBUFS) << std::endl;
    std::cerr << "ACCEPT_RESOURCE_EXHAUSTED  " << strerror(ENOMEM) << std::endl;
    std::cerr << "ACCEPT_BAD_FILE_DESCRIPTOR  " << strerror(ENOTSOCK) << std::endl;
    std::cerr << "ACCEPT_INVALID_STATE  " << strerror(EOPNOTSUPP) << std::endl;
    std::cerr << "ACCEPT_PERMISSION_DENIED  " << strerror(EPERM) << std::endl;
    std::cerr << "ACCEPT_PROTOCOL_ERROR  " << strerror(EPROTO) << std::endl;

    return 0;
}

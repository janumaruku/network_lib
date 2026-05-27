/*
** EPITECH PROJECT, 2026
** network
** File description:
** main
*/

#include <iostream>

#include "CommandBuilder.hpp"
#include "CommandContext.hpp"
#include "Shell.hpp"
#include "TcpClient.hpp"

int main(const int argc, const char *argv[])
{
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <port> <host>" << std::endl;
        return 84;
    }

    TCPClient client{std::atoi(argv[1]), argv[2]};
    const auto sendCommand = shell::command::CommandBuilder()
         .name("send")
         .description("Send a command to the server")
         .arg([](shell::command::PositionalArgumentBuilder &builder) {
             builder.name("message")
                .description("Message to send to the server")
                .required();
         })
         .action(
             [&client](shell::command::CommandContext &ctx) {
                 const auto message = ctx.arg("message");
                 client.send(message);
                 const auto response = client.receive();
                 std::cout << response << std::endl;
             }).build();

    shell::Shell shell{"tcp_client", "tcp/client> "};
    shell.registerCommand(sendCommand);
    shell.run();
    std::cout << "Hello client!" << std::endl;

    return 0;
}

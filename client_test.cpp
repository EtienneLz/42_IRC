#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <cstring>

//#define PORT 12345

const int BUF_SIZE = 512;

int main(int argc, char const* argv[])
{
    (void)argc;
    if (argc < 3) {
        std::cout << "Usage: BOT <port> <pass>" << std::endl;
        return 1;
    }
    int PORT = atoi(argv[1]);
    std::string pass = argv[2];
    if (pass != "BOT"){
        std::cout << "Wrong password" << std::endl;
        return 1;
    }

    int sock = 0, valread, client_fd;
    struct sockaddr_in serv_addr;
    std::string hello = "Hello from client 1\n";

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "Socket creation error" << std::endl;
        return 1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary
    // form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        std::cerr << "\nInvalid address/ Address not supported" << std::endl;
        return 1;
    }
    if ((client_fd = connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0) {
        std::cerr << "\nConnection Failed" << std::endl;
        return 1;
    }
    std::string passMsg = "PASS BOT\r\n";
    send(sock, passMsg.c_str(), passMsg.length(), 0);
    std::string nickMsg = "NICK BOT\r\n";
    send(sock, nickMsg.c_str(), nickMsg.length(), 0);
    std::string userMsg = "USER BOT 0 * : BOT\r\n";
    send(sock, userMsg.c_str(), userMsg.size(), 0);
    // std::cout << "Hello message sent 1\nsock = " << sock << std::endl;
    // valread = read(sock, buffer, 1024);
    // std::cout << buffer << std::endl;

    char buffer[BUF_SIZE];
    while (true) {
        int count = recv(sock, buffer, BUF_SIZE, 0);
        if (count < 0) {
            std::cout << "Error receiving message" << std::endl;
            break ;
        }
        if (count == 0) {
            std::cout << "Server closed connection" << std::endl;
            break ;
        }
        buffer[count] = '\0';
        std::cout << buffer << std::endl;
        std::string tmp = buffer;
        size_t pos = tmp.find_first_of(":", 1);
        if (pos == std::string::npos)
            continue;
        std::string cmd = tmp.substr(pos + 1);
        if (cmd[0] == '!' && std::strcmp(cmd.c_str() + 1, "meteo"))
        {
            pos = tmp.find_first_of("#");
            if (pos == std::string::npos)
                continue;
            std::string chan = tmp.substr(pos);
            pos = chan.find_first_of(" ");
            if (pos == std::string::npos)
                continue;
            chan.erase(pos);
            std::string reply = "PRIVMSG " + chan + " :CHE PAS\r\n";
            send(sock, reply.c_str(), reply.size(), 0);
        }
    }
    // closing the connected socket
    close(client_fd);
    return 0;
}
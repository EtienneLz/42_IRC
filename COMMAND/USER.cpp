#include <vector>
#include "../User.hpp"
#include "../socketRun.hpp"

void    user_cmd(mClients clients, const std::string &params, int id) {
    std::vector<std::string> parts = split(command, ' ');

    std::string message;
    message = ":OurIRC ";
    if (parts.size() < 4) {
        message += ERR_NEEDMOREPARAMS;
        message += " * :Not enough parameters\r\n";
        send(id, message.c_str(), message.length(), MSG_DONTWAIT);
        return;
    }
    std::string username = parts[1];
    int mode = std::stoi(parts[2]);
    int unused = std::stoi(parts[3]);
    std::string realname = parts[4];

    clients.setUsername(username);
    clients.setRealname(realname);

}
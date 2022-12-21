#include "command.hpp"

void    user_cmd(socketRun server, std::string params, int id) {
    std::vector<std::string> parts;
    std::stringstream ss(params);
    std::string s;
    while (std::getline(ss, s, ' '))
        parts.push_back(s);

    std::string message;
    message = ":OurIRC ";
    if (parts.size() < 4) {
        message += "461";
        message += " * :Not enough parameters\r\n";
        send(id, message.c_str(), message.length(), MSG_DONTWAIT);
        return ;
    }
    std::string username = parts[1];
    std::string realname = parts[4];

    server.getUserMap()[id]->setUsername(username);
    server.getUserMap()[id]->setRealname(realname);

}
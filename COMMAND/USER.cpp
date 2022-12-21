#include "command.hpp"

void    user_cmd(socketRun server, std::string params, int id) {
    std::vector<std::string> parts;
    std::stringstream ss(params);
    std::string s;
    while (std::getline(ss, s, ' '))
        parts.push_back(s);

    if (parts.size() < 4) {
        std::cout << "LEL" << std::endl;
        send_message(server, id, ERR_NEEDMOREPARAMS, "");
        return ;
    }
    std::string name;
    for (std::vector<std::string>::iterator it = parts[4]; it++; it = parts.end()) {
        name += (*)it;
    }
    std::string username = parts[1];
    std::string realname = name;

    std::cout << "KEK" << std::endl;
    server.getUserMap()[id]->setUsername(username);
    server.getUserMap()[id]->setRealname(realname);
    send_message(server, id, RPL_WELCOME, "");
    send_message(server, id, RPL_YOURHOST, "");
    send_message(server, id, RPL_CREATED, "");
    send_message(server, id, RPL_MYINFO, "");
}
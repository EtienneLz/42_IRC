#include "command.hpp"

void    user_cmd(socketRun server, std::string params, int id) {
    std::vector<std::string> parts;
    std::stringstream ss(params);
    std::string s;

    if (server.getUserMap()[id]->getMode('r') == true)
		return (send_message(server, id, ERR_RESTRICTED, ""));
    
    if (server.getUserMap()[id]->getUserCmd() == true)
		return (send_message(server, id, ERR_ALREADYREGISTRED, ""));

    while (std::getline(ss, s, ' '))
        parts.push_back(s);

    if (parts.size() < 5 || parts[3][0] != ':') {
        send_message(server, id, ERR_NEEDMOREPARAMS, "");
        return ;
    }
    std::string name;
    std::vector<std::string>::iterator it = parts.begin() + 3;
    for (int i = 0; it != parts.end(); i++) {
        name += *it;
        if (i == 0) {
            name += " ";
            name = name.substr(1);
        }
        it++;
    }
    std::string username = parts[0];
    std::string host = parts[2];
    std::string realname = name;

    server.getUserMap()[id]->setUsername(username);
    server.getUserMap()[id]->setHost(host);
    server.getUserMap()[id]->setRealname(realname);

    server.getUserMap()[id]->setUserCmd();
    send_message(server, id, RPL_WELCOME, "");
    send_message(server, id, RPL_YOURHOST, "");
    send_message(server, id, RPL_CREATED, "");
    send_message(server, id, RPL_MYINFO, "");
}
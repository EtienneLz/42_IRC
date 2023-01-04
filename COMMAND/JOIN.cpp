#include "command.hpp"

void    JOIN(Server *server, std::string params, int id) {
    std::vector<std::string> parts;
    std::stringstream ss(params);
    std::string s;

    if (server->getUserMap()[id]->getMode('r') == true)
		return (send_message(server, id, ERR_RESTRICTED, ""));

    while (std::getline(ss, s, ' '))
        parts.push_back(s);

    if (parts.size() < 1) {
        send_message(server, id, ERR_NEEDMOREPARAMS, "");
        return ;
    }

    std::string name;
    mChannel chanMap;
    bool exist = false;

    name = *parts.begin();
    chanMap = server->getChannelMap();

    for (mChannel::iterator it = chanMap.begin(); it != chanMap.end(); it++)
        if (it->first == name)
            exist = true;

    if (exist) {
        server->getChannelMap()[name] = new Channel();
    }
    else {

    }
}
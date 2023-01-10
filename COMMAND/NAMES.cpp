#include "command.hpp"

void    NAMES(Server *server, std::string params, int id) {
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

    bool exist = false;
    if (parts[0][0] != '#')
        return send_message(server, id, RPL_ENDOFNAMES, "");

    for (mChannel::iterator iter = server->getChannelMap().begin(); iter != server->getChannelMap().end(); iter++)
        if (iter->first == parts[0])
            exist = true;
    
    if (!exist)
        return send_message(server, id, RPL_ENDOFNAMES, "");
    else {
        std::string message;
        for (std::vector<User*>::iterator it = server->getChannelMap()[parts[0]]->getUsers().begin(); it != server->getChannelMap()[parts[0]]->getUsers().end(); ++it) {
            message =  ":" + (*it)->getNick() + "!" + (*it)->getNick()  + "@" + (*it)->getHost() + " 353 " + " = " + parts[0] + " :" + (*it)->getNick();
            std::cout << "DEBUG ----- " << message << std::endl;
            send(id, message.c_str(), message.length(), MSG_DONTWAIT);
        }
    }
}
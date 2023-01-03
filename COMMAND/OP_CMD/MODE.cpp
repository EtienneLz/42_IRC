#include "../command.hpp"

void    MODE(socketRun server, std::string params, int id) {
    std::vector<std::string> parts;
    std::stringstream ss(params);
    std::string s;

    if (server.getUserMap()[id]->getMode('r') == true)
		return (send_message(server, id, ERR_RESTRICTED, ""));

    while (std::getline(ss, s, ' '))
        parts.push_back(s);
    if (parts.size() < 1) {
        send_message(server, id, ERR_NEEDMOREPARAMS, "");
        return ;
    }

    if (parts.size() == 1) {
        send_message(server, id, RPL_UMODEIS, "");
        return ;
    }

    if (*parts.begin() == "*")
        *parts.begin() = server.getUserMap()[id]->getNick();

    if (*parts.begin() != server.getUserMap()[id]->getNick()) {
        send_message(server, id, ERR_USERSDONTMATCH, "");
        return ;
    }

    bool positive;
    std::string flags;
    flags = *(parts.begin() + 1);
    if (flags.at(0) == '+')
        positive = true;
    else if (flags.at(0) == '-')
        positive = false;
    else {
        send_message(server, id, ERR_UMODEUNKNOWNFLAG, "");
        return ;
    }
    for (std::string::iterator it = flags.begin(); it != flags.end(); it++) {
        if (*it == 'o' && positive)
            (void)it;
        else if (*it == 'o' && !positive)
            server.getUserMap()[id]->setMode('o', false);
        else if (*it == 'r' && positive)
            (void)it;
        else if (*it == 'r' && !positive)
            server.getUserMap()[id]->setMode('r', true);
        else if (*it == 'i' && positive)
            server.getUserMap()[id]->setMode('i', true);
        else if (*it == 'i' && !positive)
            server.getUserMap()[id]->setMode('i', false);
    }
    send_message(server, id, RPL_UMODEIS, "");
}
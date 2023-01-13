#include "../command.hpp"

void    MODE(Server *server, std::string params, int id) {
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

    if (parts.size() == 1) {
        send_message(server, id, RPL_UMODEIS, "");
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

    Channel *chan;

    if (parts[0][0] == '#') {
        chan = server->getChannelMap()[parts[0]];

    

    if (chan) {
        if (parts.size() < 3)
            return send_message(server, id, ERR_NEEDMOREPARAMS, "");
        std::map<int, User *> usermap = chan->getMapUser();
        for (std::string::iterator it = flags.begin(); it != flags.end(); it++) {
            int target = 0;
            for (std::map<int, User *>::iterator iter = usermap.begin(); iter != usermap.end(); iter++) {
                if ((*iter).second->getNick() == parts[2])
                    target = (*iter).second->getId();
            }
            if (target == 0)
                return send_message(server, id, ERR_UMODEUNKNOWNFLAG, "");
            if (*it == 'o' && positive)
                chan->getChanops().push_back(server->getUserMap()[target]);
            else if (*it == 'o' && !positive) {
                bool found = false;
                for (std::vector<User *>::iterator iter = chan->getChanops().begin(); iter != chan->getChanops().end(); iter++) {
                    if ((*iter)->getNick() == parts[2]) {
                        found = true;
                        chan->getChanops().erase(iter);
                    }
                }
            }
        }
    }
    else {
    }
    if (*parts.begin() == "*")
        *parts.begin() = server->getUserMap()[id]->getNick();    

    if (*parts.begin() != server->getUserMap()[id]->getNick()) {
        send_message(server, id, ERR_USERSDONTMATCH, "");
        return ;
    }

    for (std::string::iterator it = flags.begin(); it != flags.end(); it++) {
        if (*it == 'o' && positive)
            (void)it;
        else if (*it == 'o' && !positive)
            server->getUserMap()[id]->setMode('o', false);
        else if (*it == 'r' && positive)
            (void)it;
        else if (*it == 'r' && !positive)
            server->getUserMap()[id]->setMode('r', true);
        else if (*it == 'i' && positive)
            server->getUserMap()[id]->setMode('i', true);
        else if (*it == 'i' && !positive)
            server->getUserMap()[id]->setMode('i', false);
    }
    send_message(server, id, RPL_UMODEIS, "");
    }
}
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

    if (parts.size() == 1 && parts[0][0] != '#') {
        send_message(server, id, RPL_UMODEIS, "");
        return ;
    }
    else if (parts.size() == 1 && parts[0][0] == '#') {
        return ;
    }

    bool positive;
    std::string flags;
    std::string message;
    User *targetPtr;
    flags = parts[1];
    if (flags.at(0) == '+')
        positive = true;
    else if (flags.at(0) == '-')
        positive = false;
    else {
        send_message(server, id, ERR_UMODEUNKNOWNFLAG, "");
        return ;
    }

    Channel *chan = NULL;

    if (parts[0][0] == '#')
        chan = server->getChannelMap()[parts[0]];

    if (chan) {
        if (parts.size() < 3)
            return send_message(server, id, ERR_NEEDMOREPARAMS, "");
        std::map<int, User *> usermap = chan->getMapUser();
        int target = 0;

        for (std::map<int, User *>::iterator iter = usermap.begin(); iter != usermap.end(); iter++) {
            if ((*iter).second->getNick() == parts[2]) {
                target = (*iter).second->getId();
                targetPtr = (*iter).second;
            }
        }

        if (target == 0)
            return send_chan_message(server, id, ERR_USERNOTINCHANNEL, parts[2], chan->getName());

        if (parts[1][1] && parts[1][1] == 'o' && positive) {
            chan->getChanops().push_back(server->getUserMap()[target]);
            message = ":" + targetPtr->getNick() + "!" + targetPtr->getUsername()  + "@" + targetPtr->getHost() + " MODE " + targetPtr->getNick() + " +o\n\r";
            send(targetPtr->getId(), message.c_str(), message.length(), MSG_DONTWAIT);
            std::cout << "REPLY CHAN --- " << message << std::endl;;
            return;
        }

        else if (parts[1][1] && parts[1][1] == 'o' && !positive) {
            bool found = false;
            for (std::vector<User *>::iterator iter = chan->getChanops().begin(); iter != chan->getChanops().end(); iter++) {
                if ((*iter)->getNick() == parts[2]) {
                    found = true;
                    chan->getChanops().erase(iter);
                    message = ":" + targetPtr->getNick() + "!" + targetPtr->getUsername()  + "@" + targetPtr->getHost() + " MODE " + targetPtr->getNick() + " -o\n\r";
                    send(targetPtr->getId(), message.c_str(), message.length(), MSG_DONTWAIT);
                    std::cout << "REPLY CHAN --- " << message << std::endl;
                    return;
                }
            }
            for (std::vector<User *>::iterator iter = chan->getChanops().begin(); iter != chan->getChanops().end(); iter++) {
                std::cout << "Dwkjoiweg -- " << (*iter)->getNick() << std::endl;
            }
            return;
        }

        else
            return send_chan_message(server, id, ERR_UNKNOWNMODE, parts[1], chan->getName());
    }
    else {
    if (*parts.begin() == "*")
        *parts.begin() = server->getUserMap()[id]->getNick();    

    if (*parts.begin() != server->getUserMap()[id]->getNick()) {
        send_message(server, id, ERR_USERSDONTMATCH, "");
        return ;
    }

    for (std::string::iterator it = flags.begin(); it != flags.end(); it++) {
        if (*it == 'o' && positive)
            (void)it;
        else if (*it == 'o' && !positive) {
            server->getUserMap()[id]->setMode('o', false);
        }
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
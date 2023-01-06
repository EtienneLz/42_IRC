#include "command.hpp"

void    JOIN(Server *server, std::string params, int id) {
    std::vector<std::string> parts;
    std::stringstream ss(params);
    std::string s;
    std::map<int, User*> clients = server->getUserMap();

    if (server->getUserMap()[id]->getMode('r') == true)
		return (send_message(server, id, ERR_RESTRICTED, ""));

    while (std::getline(ss, s, ' '))
        parts.push_back(s);

    if (parts.size() < 1) {
        send_message(server, id, ERR_NEEDMOREPARAMS, "");
        return ;
    }

    bool exist = false;

    for (std::vector<std::string>::iterator it = parts.begin(); it != parts.end(); it++) {
        std::string name = *it;

        if (name[0] != '#') {
            send_message(server, id, ERR_NOSUCHCHANNEL, "");
            break ;
        }

        for (mChannel::iterator iter = server->getChannelMap().begin(); iter != server->getChannelMap().end(); iter++) {
            std::cout << "ITER" << std::endl;
            if (iter->first == name) {
                std::cout << "COUSCOUS" << std::endl;
                exist = true;
            }
        }

        if (exist) {
            std::cout << "IM HERE" << std::endl;
            server->getChannelMap()[name]->joinChan(server->getUserMap()[id]);
            std::vector<User *> chanUsers = server->getChannelMap()[name]->getUsers();
            std::string message = ":" + clients[id]->getNick() + "!" + clients[id]->getNick()  + "@" + clients[id]->getHost() + " JOIN " + ":" + name + "\r\n";
            for (std::vector<User *>::iterator it2 = server->getChannelMap()[name]->getUsers().begin(); it2 != server->getChannelMap()[name]->getUsers().end(); it2++) {
                std::cout << "REPLY CHAN --- " << message << std::endl;
                send((*it2)->getId(), message.c_str(), message.length(), MSG_DONTWAIT);
            }
            send_chan_message(server, id, RPL_TOPIC, server->getChannelMap()[name]->getTopic(), name);

        }
        else {
            std::cout << "TA MERE" << std::endl;
            server->getChannelMap()[name] = new Channel;
            server->getChannelMap()[name]->setOwner(server->getUserMap()[id]);
            server->getChannelMap()[name]->setName(name);
            server->getChannelMap()[name]->joinChan(server->getUserMap()[id]);
            server->getChannelMap()[name]->setTopic("default");
            server->getChannelMap()[name]->getChanops().push_back(server->getUserMap()[id]);
            std::cout << "map chan size --- " << server->getChannelMap()[name]->userList() << std::endl;
            std::string message = ":" + clients[id]->getNick() + "!" + clients[id]->getNick()  + "@" + clients[id]->getHost() + "JOIN " + ":" + name + "\r\n";
            send_chan_message(server, id, RPL_TOPIC, server->getChannelMap()[name]->getTopic(), name);
        }
    }
    return ;
}
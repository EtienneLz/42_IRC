#include "command.hpp"


void	NICK(Server *server, std::string nick, int id) {

	std::map<int, User*> clients = server->getUserMap();

	if (clients[id]->getMode('r') == true)
		return (send_message(server, id, ERR_RESTRICTED, ""));

	if (!nick.size())
		return (send_message(server, id, ERR_NONICKNAMEGIVEN, ""));
	else if (nick.length() > 9 || (!isalpha(nick[0]) && !isspecial(nick[0])))
		return (send_message(server, id, ERR_ERRONEUSNICKNAME, nick));

	for (size_t i = 0; i < nick.size(); i++)
		if (!isalnum(nick[i]) && !isspecial(nick[i]) && nick[i] != '-')
			return (send_message(server, id, ERR_ERRONEUSNICKNAME, nick));

	for (std::map<int, User*>::iterator it = clients.begin(); it != clients.end(); ++it)
		if ((*it->second).getNick() == nick) {
			while (clients[id]->getRegistered() != true)
				sleep(5);
			return (send_message(server, id, ERR_NICKNAMEINUSE, nick));
		}
			// return (send_message(server, id, ERR_NICKNAMEINUSE, nick));
	server->getUserMap()[id]->setNick(nick);
	//return (send_message(server, id, -1, nick));
}
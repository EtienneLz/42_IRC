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
		if ((*it->second).getNick() == nick)
			return (send_message(server, id, ERR_NICKNAMEINUSE, nick));

	std::string old_nick = server->getUserMap()[id]->getNick();
	if (old == "")
		old = "*";
	server->getUserMap()[id]->setNick(nick);
	std::string new_nick = server->getUserMap()[id]->getNick();
	std::string message = ":" + old_nick + "!" + old_nick  + "@" + clients[id]->getHost() + " NICK " + new_nick + "\r\n";
	std::cout << "REPLY --- " << message;
	send(id, message.c_str(), message.length(), MSG_DONTWAIT);
}
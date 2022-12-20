#include <map>
#include <string>
#include <cctype>
#include "User.hpp"
#define ERR_NICKNAMEINUSE 433
#define ERR_NONICKNAMEGIVEN 431
#define ERR_ERRONEUSNICKNAME 432

static bool	isSpecial(char c) {
	if (c == '[' || c == ']' || c == '\\' || c == '`' || c == '_' || c == '^' ||
		c == '{' || c == '|' || c == '}')
		return (true);
	return (false);
}

int	NICK(std::map<int, User*> &clients, std::string nick, int id) {
	

	if (!nick.size())
		return (ERR_NONICKNAMEGIVEN);
	else if (nick.length() > 9 || (!isalpha(nick[0]) && !isSpecial(nick[0])))
		return (ERR_ERRONEUSNICKNAME);

	for (size_t i = 0; i < nick.size(); i++)
		if (!isalnum(nick[i]) && !isSpecial(nick[i]) && nick[i] != '-')
			return (ERR_ERRONEUSNICKNAME);

	for (std::map<int, User*>::iterator it = clients.begin(); it != clients.end(); ++it)
		if ((*it->second).getNick() == nick)
			return (ERR_NICKNAMEINUSE);
	clients[id]->setNick(nick);
	return (0);
}
#include "command.hpp"

void	PRIVMSG(Server *server, std::string params, int id) {
	if (server->getUserMap()[id]->getMode('r') == true)
		return (send_message(server, id, ERR_RESTRICTED, ""));
	else if (!params.size())
		return (send_message(server, id, ERR_NEEDMOREPARAMS, params));

	std::string targets;
	std::string message;

	size_t pos = params.find_first_of(':');
	if (pos != std::string::npos)
	{
		targets = params.substr(0, pos - 1);
		message = params.substr(pos);
	}
	else
		return (send_message(server, id, ERR_NORECIPIENT, message));


	if (targets.size() == 0)
		return (send_message(server, id, ERR_NORECIPIENT, params));
	else if (message.size() == 1)
		return (send_message(server, id, ERR_NOTEXTTOSEND, params));

	else
	{
		std::vector<std::string> msgTargets;
		std::stringstream ss(targets);
		std::string s;

		if (targets.find(',') != std::string::npos)
			while (std::getline(ss, s, ','))
				msgTargets.push_back(s);
		else
			msgTargets.push_back(targets);

		size_t users = 0;
		size_t messages = 0;
		for (std::vector<std::string>::iterator itT = msgTargets.begin(); itT != msgTargets.end(); itT++)
		{
			++users;
			if (targets[0] == '#' && targets.find('.') != std::string::npos)
			{
				size_t pos = msgTargets[0].find('.');
				msgTargets[0] = msgTargets[0].substr(pos + 1);
			}
			for (std::map<int, User*>::iterator it = server->getUserMap().begin(); it != server->getUserMap().end(); it++)
			{
				if (it->second->getNick() == *itT)
				{
					if (message[0] == ':')
					{
						std::string reply = ":" + server->getUserMap()[id]->getNick() + "!"
						+ server->getUserMap()[id]->getNick() + "@"
						+ server->getUserMap()[id]->getHost() + " PRIVMSG " + *itT + " "
						+ message + "\r\n";
						send(it->first, reply.c_str(), reply.size(), MSG_DONTWAIT);
						++messages;
					}
					else
						return (send_message(server, id, ERR_NORECIPIENT, *itT));
				}
			}
			if (server->getChannelMap()[*itT])
			{
				Channel *chan = server->getChannelMap()[*itT];
				std::vector<User*> users = chan->getUsers();
				for (std::vector<User*>::iterator it = users.begin(); it != users.end(); it++)
				{
					if ((*it)->getUsername() == server->getUserMap()[id]->getUsername())
					{
						for (std::vector<User*>::iterator it = users.begin(); it != users.end(); it++)
						{
							if ((*it)->getUsername() == server->getUserMap()[id]->getUsername())
								;
							else
								send((*it)->fd, message.c_str(), message.size(), MSG_DONTWAIT);
						}
						++messages;
					}
				}
			}
			if (users != messages)
				return (send_message(server, id, ERR_NOSUCHNICK, *itT));
		}
	}
}
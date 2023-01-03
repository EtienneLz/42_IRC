#include "command.hpp"

void	PRIVMSG(socketRun server, std::string params, int id) {
	if (server.getUserMap()[id]->getRegister() == false)
		return (send_message(server, id, ERR_ALREADYREGISTRED, ""));
	else if (!params.size())
		return (send_message(server, id, ERR_NEEDMOREPARAMS, params));

	std::string targets;
	std::string message;

	size_t pos = params.find_first_of(':');
	targets = params.substr(0, pos - 1);
	message = params.substr(pos);

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
		for (std::vector<std::string>::iterator itm = msgTargets.begin(); itm != msgTargets.end(); itm++)
		{
			++users;
			if (targets[0] == '#' && targets.find('.') != std::string::npos)
			{
				size_t pos = msgTargets[0].find('.');
				msgTargets[0] = msgTargets[0].substr(pos + 1);
			}
			std::map<int, User*>::iterator it = server.getUserMap().begin();
			for (; it != server.getUserMap().end(); it++)
			{
				if (it->second->getNick() == *itm)
				{
					if (message[0] == ':')
					{
						send(it->first, message.c_str(), message.size(), MSG_DONTWAIT);
						++messages;
					}
					else
						++messages;//error no ':' in the message text
				}
			}
			//do the same for Channel
			// std::cout << "message = " << messages << std::endl;
			if (users != messages)
				return (send_message(server, id, ERR_NOSUCHNICK, *itm));
		}
	}
}
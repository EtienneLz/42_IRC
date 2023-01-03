#include "command.hpp"

void	PRIVMSG(socketRun server, std::string params, int id) {
	if (server.getUserMap()[id]->getRegister() == false)
		return (send_message(server, id, ERR_ALREADYREGISTRED, ""));
	else if (!params.size())
		return (send_message(server, id, ERR_NEEDMOREPARAMS, params));

	std::vector<std::string> parts;
	std::stringstream ss(params);
	std::string s;

	while (std::getline(ss, s, ':'))
		parts.push_back(s);
	parts[0].erase(parts[0].end() - 1);

	if (parts.size() == 0)
		return (send_message(server, id, ERR_NORECIPIENT, params));
	else if (parts.size() == 1)
		return (send_message(server, id, ERR_NOTEXTTOSEND, params));

	else
	{
		std::vector<std::string> msgTargets;
		std::stringstream ss(parts[0]);
		std::string s;

		if (parts[0].find(',') != std::string::npos)
			while (std::getline(ss, s, ','))
				msgTargets.push_back(s);
		else
			msgTargets.push_back(parts[0]);

		size_t users = 0;
		size_t messages = 0;
		for (std::vector<std::string>::iterator itm = msgTargets.begin(); itm != msgTargets.end(); itm++)
		{
			++users;
			std::map<int, User*>::iterator it = server.getUserMap().begin();
			if (parts[0][0] == '#' && parts[0].find('.') != std::string::npos)
			{
				size_t pos = msgTargets[0].find('.');
				msgTargets[0] = msgTargets[0].substr(pos + 1);
				{
					for (; it != server.getUserMap().end(); it++)
					{
						if (it->second->getNick() == *itm)
						{
							if (parts[1][0] == ':')
							{
								send(it->first, parts[1].c_str(), parts[1].size(), MSG_DONTWAIT);
								++messages;
							}
							else
								++messages;//error no ':' in the message text
						}
					}
					//do the same for Channel
					// std::cout << "message = " << messages << std::endl;
				}
			}
			else
			{
				for (it = server.getUserMap().begin(); it != server.getUserMap().end(); it++)
				{
					if (it->second->getNick() == *itm)
					{
						if (parts[1][0] == ':')
						{
							send(it->first, parts[1].c_str(), parts[1].size(), MSG_DONTWAIT);
							++messages;
						}
						else
							++messages;//error no ':' in the message text
					}
				}
			}
			if (users != messages)
				return (send_message(server, id, ERR_NOSUCHNICK, *itm));
		}
	}
}
#include "../command.hpp"

void	PART(Server *server, std::string params, int id) {
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
		targets = params;

	std::vector<std::string> chans;
	std::stringstream ss(targets);
	std::string s;

	if (targets.find(',') != std::string::npos)
		while (std::getline(ss, s, ','))
			chans.push_back(s);
	else
		chans.push_back(targets);

	for (std::vector<std::string>::iterator itC = chans.begin(); itC != chans.end(); ++itC)
	{
		std::string name = *itC;
		Channel *chan = server->getChannelMap()[name];
		if (chan)
		{
			std::vector<User*> users = chan->getUsers();
			std::vector<User*>::iterator itU = users.begin();
			for (; itU != users.end(); itU++)
			{
				if ((*itU)->getNick() == server->getUserMap()[id]->getNick())
				{
					server->getChannelMap()[name]->leaveChan((*itU)->getNick());
					for (std::vector<User*>::iterator it = users.begin(); it != users.end(); it++)
					{
						if (message.size() == 0)
							message = "Bye evryone !";
						std::string reply = ":" + server->getUserMap()[id]->getNick() + "!"
							+ server->getUserMap()[id]->getNick() + "@"
							+ server->getUserMap()[id]->getHost() + " PART " + name + " "
							+ message + "\r\n";
						send((*it)->getId(), reply.c_str(), reply.size(), MSG_DONTWAIT);
					}
				}
			}
			if (itU == users.end())
				send_message(server, id, ERR_NOTONCHANNEL, server->getUserMap()[id]->getNick());
		}
		else
			send_message(server, id, ERR_NOSUCHCHANNEL, "");
	}
}
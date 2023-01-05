#include "command.hpp"

void	JOIN(Server *server, std::string params, int id)
{
	if (server->getUserMap()[id]->getMode('r') == true)
		return (send_message(server, id, ERR_RESTRICTED, ""));
	else if (!params.size())
		return (send_message(server, id, ERR_NEEDMOREPARAMS, params));

	std::vector<std::string> servName;
	std::stringstream ss(params);
	std::string s;

	if (params.find(',') != std::string::npos)
		while (std::getline(ss, s, ','))
			servName.push_back(s);
	else
		servName.push_back(params);

	for (std::vector<std::string>::iterator it = servName.begin(); it != servName.end(); it++)
	{
		if ((*it)[0] != '#')
			return (send_message())
	}

		return ()
	if (server->getChannelMap()[])
}
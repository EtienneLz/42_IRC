# include "../command.hpp"


bool	isUser (Server *serv, std::string user, std::string why, int id_exec) {
	for (std::map<int, User*>::iterator it = serv->getUserMap().begin(); it!= serv->getUserMap().end(); it++) {
		if (user.compare(it->second->getNick()) == 0) {
			std::string exec = serv->getUserMap()[id_exec]->getNick();
			std::string message = ":" + exec + "!" +  exec + "@" + serv->getUserMap()[id_exec]->getHost() +
			" KILL " + user + " :" + why + "\r\n";
			std::cout << "REPLY --- " << message;
			send(it->first, message.c_str(), message.length(), MSG_DONTWAIT);
			// send_message() to operator ?
			serv->setKilled(it->first);
			return TRUE;
		}
	}
	return FALSE;
}

std::vector<std::string> splitArgsKill(std::string params, size_t end_pos) {
	std::size_t pos;
	std::vector<std::string> args;

	while ((pos = params.find(' ')) < end_pos) {
			args.push_back(params.substr(0, pos));
			params = params.substr(pos + 1);
		}
		args.push_back(params);
	if (args[args.size() - 1][0] == ':')
		args[args.size() - 1].erase(0, 1);
	return args;
}

void KILL(Server *serv, std::string params, int id) {
	User *oper;
	if (serv->getUserMap()[id])
		oper = serv->getUserMap()[id];
	else
		return; //error
	std::vector<std::string> args;
	size_t end_pos;
	if ((end_pos = params.find(':')) != std::string::npos)
		args = splitArgsKill(params, end_pos);
	else
		args = splitArgsKill(params, std::string::npos);
	if (args.size() != 2)
		return (send_message(serv, id, ERR_NEEDMOREPARAMS, ""));
	if (oper->getMode('r') == true)
		return (send_message(serv, id, ERR_RESTRICTED, ""));
	if (oper->getMode('o') == false)
	 	return (send_message(serv, id, ERR_NOPRIVILEGES, ""));
	if (isUser(serv, args[0], args[1], id) != TRUE) {
		return (send_message(serv, id, ERR_NOSUCHNICK, ""));
	}
	return;
	
}
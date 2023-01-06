# include "../command.hpp"

void	send_chan() {

}

bool	isUser (Channel chan, std::vector<std::string> args, int id) {
	std::vector<User*> vec_users = chan.getUsers();
	std::vector<User*> vec_chanops = chan.getChanops();
	std::string user = args[1];
	std::string why;
	if (args.back() != user)
		why = args[2];
	else
		why ="";
	for (std::vector<User*>::iterator it = vec_users.begin(); it!= vec_users.end(); it++) {
		if (user.compare((*it)->getNick()) == 0) {
			for (std::vector<User*>::iterator it = vec_chanops.begin(); it!= vec_chanops.end(); it++) {
				if ((*it).fd == id)
				std::string exec = (*it)->getNick();
			}
			std::string exec = serv->getUserMap()[id_exec]->getNick();
			std::string message = ":" + exec + "!" +  exec + "@" + serv->getUserMap()[id_exec]->getHost() +
			" KILL " + user + " :" + why + "\r\n";
			std::cout << "REPLY --- " << message;
			send(it->first, message.c_str(), message.length(), MSG_DONTWAIT);
			// send user kicked msg ?
			vec.erase(it);
			return TRUE;
		}
	}
	return FALSE;
}

User	*isChanop(User oper, Channel chan) {
	std::vector<User*> vec = chan.getChanops();
	for (std::vector<User*>::iterator it = vec.begin(); it!= vec.end(); it++) {
		if (oper.getNick().compare((*it)->getNick()) == 0)
			return *it;
	}
	return NULL;
}

Channel *getChan(Server::mChannel mchan, std::string str) {
	if (str[0] == '#')
		str.erase(0, 1);
	for (std::map<std::string, Channel*>::iterator it = mchan.begin(); it != mchan.end(); it++) {
		if (str.compare((*it).second->getName()) == 0) {
			return(*it).second;
		}
	}
	return NULL;
}

std::vector<std::string> splitArgs(std::string params, size_t end_pos) {
	std::size_t pos;
	std::vector<std::string> args;

	while ((pos = params.find(' ')) < end_pos) {
			args.push_back(params.substr(0, pos));
			params = params.substr(pos + 1);
		}
		args.push_back(params);
	if (args[0][0] == '#')
		args[0].erase(0, 1);
	if (args[args.size() - 1][0] == ':')
		args[args.size() - 1].erase(0, 1);
	return args;
}

void KICK(Server *serv, std::string params, int id) {
	User *oper;
	if (serv->getUserMap()[id])
		oper = serv->getUserMap()[id];
	else
		return; //error
	if (oper->getMode('r') == true)
		return (send_message(serv, id, ERR_RESTRICTED, ""));

	std::vector<std::string> args;
	size_t end_pos;
	if ((end_pos = params.find(':')) != std::string::npos)
		args = splitArgs(params, end_pos);
	else
		args = splitArgs(params, std::string::npos);
	if (args.size() < 2)
		return (send_message(serv, id, ERR_NEEDMOREPARAMS, ""));

	Channel	*chan = NULL;
	User *chanoper = NULL;
	chan = getChan(serv->getChannelMap(), args[0]);
	
	if (!chan) {
		return (send_message(serv, id, ERR_NOSUCHCHANNEL, ""));
	}
	else if ((chanoper = isChanop(*oper, *chan)) == NULL) {
		return (send_message(serv, id, ERR_CHANOPRIVSNEEDED, ""));
	}
	else if (isUser(*chan, args, id) != TRUE) {
		return (send_message(serv, id, ERR_NOTONCHANNEL, ""));
	}
	//if (args.size() == 3 )
	// send message "kick done!" with arg comment to channel
	return;
	
}
# include "../command.hpp"

int		isUser (Channel chan, std::string user, int *op) {
	std::vector<User*> vec_users = chan.getUsers();
	std::vector<User*> vec_chanops = chan.getChanops();
	int i = 0;
	for (std::vector<User*>::iterator it = vec_users.begin(); it!= vec_users.end(); it++) {
		if (user.compare((*it)->getNick()) == 0) {
			return i;
			}
			i++;
		}
	i = 0;
	for (std::vector<User*>::iterator it = vec_chanops.begin(); it!= vec_chanops.end(); it++) {
		if (user.compare((*it)->getNick()) == 0) {
			*op = 1;
			return i;
			}
			i++;
		}
	return -1;
}

User	*isChanop(User oper, Channel chan) {
	std::vector<User*> vec = chan.getChanops();
	for (std::vector<User*>::iterator it = vec.begin(); it!= vec.end(); it++) {
		if (oper.getNick().compare((*it)->getNick()) == 0)
			return *it;
	}
	return NULL;
}

// Channel *getChan(Server::mChannel mchan, std::string str) {
// 	if (str[0] == '#')
// 		str.erase(0, 1);
// 	if mchan[str]
// 	for (std::map<std::string, Channel*>::iterator it = mchan.begin(); it != mchan.end(); it++) {
// 		if (str.compare((*it).second->getName()) == 0) {
// 			return(*it).second;
// 		}
// 	}
// 	return NULL;
// }

std::vector<std::string> splitArgs(std::string params, size_t end_pos) {
	std::size_t pos;
	std::vector<std::string> args;

	while ((pos = params.find(' ')) < end_pos) {
			args.push_back(params.substr(0, pos));
			params = params.substr(pos + 1);
		}
		args.push_back(params);
	if (args[args.size() - 1][0] == ':')
		args[args.size() - 1].erase(0, 1);
	for (std::vector<std::string>::iterator it = args.begin(); it!= args.end(); it++)
		std::cout << "\nARGS = " << *it << std::endl;
	return args;
}


void	sendToChan(std::string message, Channel chan) {
	std::vector<User*> vec_users = chan.getUsers();
	std::vector<User*> vec_chanops = chan.getChanops();
	for (std::vector<User*>::iterator it = vec_users.begin(); it!= vec_users.end(); it++) {
		if ((*it) != NULL)
			send((*it)->fd, message.c_str(), message.length(), MSG_DONTWAIT);
	}
	for (std::vector<User*>::iterator it = vec_chanops.begin(); it!= vec_chanops.end(); it++) {
		if ((*it) != NULL)
			send((*it)->fd, message.c_str(), message.length(), MSG_DONTWAIT);
		}
}

void KICK(Server *serv, std::string params, int id) {
	User *exec;
	if (serv->getUserMap()[id])
		exec = serv->getUserMap()[id];
	else
		return; //error
	if (exec->getMode('r') == true)
		return (send_message(serv, id, ERR_RESTRICTED, ""));

	std::vector<std::string> args;
	size_t end_pos;
	if ((end_pos = params.find(':')) != std::string::npos)
		args = splitArgs(params, end_pos);
	else
		args = splitArgs(params, std::string::npos);
	if (args.size() < 2)
		return (send_message(serv, id, ERR_NEEDMOREPARAMS, ""));

	std::string why = "";
	if (args.size() == 3)
		why = args[2];
	else
		why = "";

	Channel	*chan = NULL;
	User *chanoper = NULL;
	int kicked = -1;
	int op = 0;
	
	if ((chan = serv->getChannelMap()[args[0]]) == NULL)
		return (send_message(serv, id, ERR_NOSUCHCHANNEL, ""));
	else if ((chanoper = isChanop(*exec, *chan)) == NULL) {
		return (send_message(serv, id, ERR_CHANOPRIVSNEEDED, ""));
	}
	else if ((kicked = isUser(*chan, args[1], &op)) == -1) {
		return (send_message(serv, id, ERR_NOTONCHANNEL, ""));
	}

	std::string message = ":" + exec->getNick() + "!" +  exec->getNick() + "@" +
	exec->getHost() + " KICK " + args[0] + " :" + why + "\r\n";
	std::cout << "REPLY --- " << message;
	sendToChan(message, *chan);
	if (op == 0)
		chan->getUsers().erase(chan->getUsers().begin() + kicked);
	else
		chan->getChanops().erase(chan->getChanops().begin() + kicked);
	
	return;
	
}
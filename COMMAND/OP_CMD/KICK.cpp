# include "../command.hpp"

void KICK(socketRun serv, std::string params, int id) {
	// User oper;
	// if (serv.getUserMap()[id])
	// 	oper = serv.getUserMap()[id];
	// else
	// 	//error
	if (serv.getUserMap()[id]->getRegister() == false)
		return (send_message(serv, id, ERR_RESTRICTED, ""));

	std::vector<std::string> args = trimArgs(params);

	Channel	*chan;
	chan = getChan(serv.getChannelMap(), args[0]);
	
	if (!chan) {
		std::cout << "ERROR CHANNEL\n"; // mettre fonction erreur
		return;
	}
	else {
		if ()
	}
	User client;
	if (serv.getUserMap()[id])
		client = serv.getUserMap()[id];
	else
		//error
	
}

Channel *getChan(socketRun::mChannel mchan, std::string str) {
	for (std::map<std::string, Channel*>::iterator it = mchan.begin(); it != mchan.end(); it++) {
		if (str.compare((*it).second->getName()) == 0) {
			return(*it).second;
		}
	}
	return NULL;
}

std::vector<std::string> trimArgs(std::string params) {
	std::size_t pos;
	std::vector<std::string> args;

	while ((pos = params.find(' ')) != std::string::npos) {
			args.push_back(params.substr(0, pos));
			params = params.substr(pos + 1);
		}
		args.push_back(params);
	if (args[0].front() == '#')
		args[0].erase(0, 1);
	return args;
}
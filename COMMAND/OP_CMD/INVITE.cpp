#include "../command.hpp"

void INVITE(Server *server, std::string params, int id)
{
	std::string target;
	std::string channel;

	size_t pos = params.find_first_of(" ");
	if (pos != std::string::npos) {
		target = params.substr(0, pos);
		channel = params.substr(pos + 1);
	} else {
		return (send_message(server, id, ERR_NORECIPIENT, ""));
	}

	User *user = server->getUserMapName()[target];
	if (!user) {
		return (send_message(server, id, ERR_NOSUCHNICK, target));
	}

	Channel *chan = server->getChannelMap()[channel];
	if (!chan) {
		return (send_message(server, id, ERR_NOSUCHCHANNEL, channel));
	}

	if (!chan->isOp(id)) {
		return (send_message(server, id, ERR_CHANOPRIVSNEEDED, channel));
	}

	chan->joinChan(user);
	std::vector<User *> chanUsers = chan->getUsers();
	std::string message = ":" + target + "!" + user->getUsername()  + "@" + user->getHost() + " JOIN :" + channel + "\r\n";
	for (std::vector<User *>::iterator it = chan->getUsers().begin(); it != chan->getUsers().end(); it++) {
		std::cout << "REPLY CHAN --- " << message << std::endl;
		send((*it)->getId(), message.c_str(), message.length(), MSG_DONTWAIT);
	}

	if (chan->getTopic() != "")
		send_chan_message(server, user->getId(), RPL_TOPIC, chan->getTopic(), channel);
	else
		send_chan_message(server, user->getId(), RPL_NOTOPIC, "", channel);

	std::string reply = ":" + server->getUserMap()[id]->getNick() + " INVITE " + target + " " + channel + "\r\n";
	send(user->getId(), reply.c_str(), reply.size(), MSG_DONTWAIT);
	NAMES(server, channel, user->getId());
	send_chan_message(server, user->getId(), RPL_ENDOFNAMES, "", channel);
}
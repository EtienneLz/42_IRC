# include "Channel.hpp"

Channel::Channel (User &creator, std::string name, socketRun &server) :_name(name) {
	_owner = creator;
	(void)server;
}

Channel::~Channel () {
	// if (!_chanops.empty()) {
	// 	for (iter it = _chanops.begin(); it != _chanops.end(); it ++) {
	// 		it
	// 	}
	// }
	// if (!_users.empty()) {
	// 	for (iter it = _users.begin(); it != _users.end(); it ++) {
	// 		it->erase();
	// 	}
	// }
}

std::vector<User *> Channel::getUsers() {
	return _users;
}

std::vector<User *> Channel::getChanops() {
	return _chanops;
}

std::string Channel::getName() {
	return _name;
}

std::string Channel::getTopic() {
	return _topic;
}

void	Channel::setTopic(std::string title) {
	_topic = title;
}
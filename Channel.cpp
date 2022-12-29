# include "Channel.hpp"

Channel::Channel (User &creator, std::string name, socketRun &server) :_name(name) {
	_chanops.push_back(creator.getUsername());
}

Channel::~Channel () {
	if (!_chanops.empty()) {
		for (iter it = _chanops.begin(); it != _chanops.end(); it ++) {
			it->erase();
		}
	}
	if (!_users.empty()) {
		for (iter it = _users.begin(); it != _users.end(); it ++) {
			it->erase();
		}
	}
	if (!_banned.empty()) {
		for (iter it = _banned.begin(); it != _banned.end(); it ++) {
			it->erase();
		}
	}
}

std::vector<std::string> Channel::getUsers() {
	return _users;
}

std::vector<std::string> Channel::getChanops() {
	return _chanops;
}

std::vector<std::string> Channel::getBanned() {
	return _banned;
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
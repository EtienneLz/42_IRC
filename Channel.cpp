# include "Channel.hpp"

Channel::Channel () {}

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

void	Channel::joinChan(User *newUser) {
	iter toFind;
	bool found = false;
	for (iter it = _chanUsers.begin(); it != _chanUsers.end(); it++) {
		std::cout << "NIQUE NAME --- " << (*it)->getNick() << std::endl;
		if ((*it)->getNick() == newUser->getNick()) {
			toFind = it;
			found = true;
			break ;
		}
	}
	if (!found)
		_chanUsers.push_back(newUser);
}

void	Channel::leaveChan(std::string oldUser) {
	iter toFind;
	bool found = false;
	for (iter it = _chanUsers.begin(); it != _chanUsers.end(); it++)
		if ((*it)->getNick() == oldUser) {
			toFind = it;
			found = true;
			break ;
		}
	if (found)
		_chanUsers.erase(toFind);
}

std::string			Channel::userList(void) {
	std::string ret = "";
	for (std::vector<User *>::iterator it = _chanUsers.begin(); it != _chanUsers.end(); it++)
		ret += " ~" + (*it)->getNick();
	return ret;
}

std::vector<User *> &Channel::getUsers() {
	return _chanUsers;
}

std::vector<User *> &Channel::getChanops() {
	return _chanops;
}

std::string Channel::getName() {
	return _name;
}

std::string Channel::getTopic() {
	return _topic;
}

void		Channel::setName(std::string name) {
	_name = name;
}

void		Channel::setOwner(User *owner) {
	_owner = owner;
}

void	Channel::setTopic(std::string title) {
	_topic = title;
}
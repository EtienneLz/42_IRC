#include "User.hpp"

User::User() {
	fd = -1;
	num_conn = 0;
	count = -1;
}

User::~User() {

}

std::string User::getUsername() {
	return _username;
}

void        User::setUsername(std::string str) {
	_username = str;
}

std::string User::getRealname() {
	return _realname;
}

void        User::setRealname(std::string str) {
	_realname = str;
}

std::string User::getNick() {
	return _nickname;
}

void        User::setNick(std::string str) {
	_nickname = str;
}
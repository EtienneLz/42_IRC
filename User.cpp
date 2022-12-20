#include "User.hpp"

User::User():_register(false) {
	fd = -1;
	num_conn = 0;
	count = -1;
}

User::~User() {}

std::string User::getUsername() {return _username;}

void        User::setUsername(std::string str) {_username = str;}

std::string User::getRealname() {return _realname;}

void        User::setRealname(std::string str) {_realname = str;}

std::string const &User::getNick(void) const {return (_nickname);}

bool const &User::getRegister(void) const {return (_register);}

void		User::setNick(std::string nick) {_nickname = nick;}

void		User::setRegister(void) {_register = true;}



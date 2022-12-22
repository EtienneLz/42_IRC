#include "User.hpp"

User::User():_register(false) {
	fd = -1;
	num_conn = 0;
	count = -1;
}

User::~User() {}

const std::string User::getUsername() const {return _username;}

void        User::setUsername(std::string str) {_username = str;}

const std::string User::getRealname() const {return _realname;}

void        User::setRealname(std::string str) {_realname = str;}

const std::string User::getHost() const {return _host;}

void        User::setHost(std::string str) {_host = str;}

std::string const &User::getNick(void) const {return (_nickname);}

bool const &User::getRegister(void) const {return (_register);}

void		User::setNick(std::string nick) {_nickname = nick;}

void		User::setRegister(void) {_register = true;}

std::ostream& operator<<(std::ostream& output, const User &user) {
	output << "\n******************************INFO*********************************\n";
	output << "USERNAME: " << user.getUsername() << "\nNICKNAME: " << user.getNick() << std::endl;
	if (user.getRegister())
		output << "Is registered = yes";
	else
		output << "IS registered = no";
	output << "\n*******************************************************************\n";
	output << std::endl << std::endl;
	return output;
}


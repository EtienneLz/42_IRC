#include "User.hpp"

User::User():_register(false), _userCmdDone(false) {
	fd = -1;
	num_conn = 0;
	count = -1;
	_mode.o = false;
	_mode.r = true;
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

bool const &User::getUserCmd(void) const {return (_userCmdDone);}

void		User::setUserCmd(void) {_userCmdDone = true;}

bool const &User::getOperator(void) const {return (_operator);}

void		User::setOperator(void) {_operator = true;}

void        User::setMode(char flag, bool add){
	if (add) {
		if (flag == 'o')
			_mode.o = true;
		else if (flag == 'r')
			_mode.r = true;
	}
	else {
		if (flag == 'o')
			_mode.o = false;
		else if (flag == 'r')
			_mode.r = false;
	}
}

bool const	&User::getMode(char flag) const {
		if (flag == 'o')
			return _mode.o;
		else if (flag == 'r')
			return _mode.r;
		else
			return _mode.r;
	}

std::ostream& operator<<(std::ostream& output, const User &user) {
	output << "\n******************************INFO*********************************\n";
	output << "USERNAME: " << user.getUsername() << "\nNICKNAME: " << user.getNick() << std::endl;
	if (user.getMode('r') == true)
		output << "Is restricted = yes" << std::endl;
	else
		output << "Is restricted = no" << std::endl;
	if (user.getRegister())
		output << "Is registered = yes";
	else
		output << "Is registered = no";
	output << "\n*******************************************************************\n";
	output << std::endl << std::endl;
	return output;
}
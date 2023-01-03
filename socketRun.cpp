#include "socketRun.hpp"

socketRun::socketRun(int port, std::string pwd) :_port(port), _count(0), _pwd(pwd), _hostname("0.0.0.0"), _opPwd("AUPP") {
	// _commands["KICK"] = &KICK();
	// _commands["KILL"] = &KILL();
	// _commands["QUIT"] = &QUIT();
	_commands["MODE"] = MODE;
	_commands["OPER"] = OPER;
	// _commands["CAP"] = &CAP;
	// _commands["JOIN"] = &JOIN;
	_commands["NICK"] = NICK;
	_commands["PASS"] = PASS;
	_commands["USER"] = user_cmd;
	_commands["PING"] = PING;
	// _commands["PRIVMSG"] = &PRIVMSG;

	int on = 1;
	_addrlen = sizeof(_address);

	// Create a communication endpoint in TCP IPv4
	if ((_sd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket() failed");
		exit(EXIT_FAILURE);
	}

	// Once the listening sd is bound to a port, no other local address can bind to the port
	if (setsockopt(_sd, SOL_SOCKET, SO_REUSEADDR, (char*)&on, sizeof(on)) < 0)
		socketError("setsockopt() failed");

	// Sets the non_blocking option on the sd and all of which will derived from it
	// if (fcntl(_sd, F_SETFL, O_NONBLOCK) < 0)
	// 	socketError("fcntl() failed");

	// Initialize sockaddr_in struct
	memset((char*)&_address, 0, _addrlen);
	_address.sin_family = AF_INET;
	_address.sin_addr.s_addr = htonl(INADDR_ANY);
	_address.sin_port = htons(_port);

	// Bind the sd to an address
	if (bind(_sd, (struct sockaddr *)&_address, _addrlen) < 0)
		socketError("bind() failed");

	// Sets the sd in a passive mode where it can accept incoming connections requests
	if (listen(_sd, 3) < 0)
		socketError("listen() failed");
	std::cout << "Listening...\n";

}

socketRun::~socketRun() {

}

void socketRun::selectLoop() {
	fd_set rfds;
	struct timeval tv;
	int retval;
	int sd_max;
	int curr_sd;
	std::string welcome = "Welcome on our IRC server!\n"; 

	// select() loop
	while (TRUE) {

	tv.tv_sec = 20;
	tv.tv_usec = 0;
	FD_ZERO(&rfds);
	FD_SET(_sd,&rfds);
	sd_max = _sd;

	for (iterator it = _clients.begin(); it != _clients.end(); it++) {
		curr_sd = it->first;
		if (curr_sd > 0)
			FD_SET(curr_sd, &rfds);
		if (curr_sd > sd_max)
			sd_max = curr_sd;
	}

	retval = select(sd_max + 1, &rfds, NULL, NULL, &tv);

	if (retval < 0 && errno != EINTR)
		perror("select() failed\n");
	//check if fds are register and so, active
	if (FD_ISSET(_sd, &rfds)) {
		int fdcl;
		if ((fdcl = accept(_sd, (struct sockaddr *)&_address, (socklen_t*)&_addrlen)) < 0)
			socketError("accept() failed\n");

		//adding a new user
		_clients[fdcl] = new User;
		_count++;
		std::cout << "\nAdding new user with fd: " << fdcl << "\nNumber of users: " << _count << std::endl;
	}

	for (iterator it = _clients.begin(); it != _clients.end(); it++) {
		curr_sd = it->first;
		char buf[1025];
		if (FD_ISSET(curr_sd, &rfds)) {
			int valread;
			if ((valread = read(curr_sd, buf, 1024)) == 0) {
				_count--;
				std::cout << "User " << it->second->getUsername() << " with fd " << curr_sd << " disconnected\n";
				std::cout << "Number of users: " << _count << std::endl;
				close(curr_sd);
				_clients.erase(curr_sd);
				break;
			}
			else {
				buf[valread] = '\0';
				receiveMessage(buf, curr_sd);
				std::cout << *_clients[curr_sd];
				//sending msg back
				// send(curr_sd, buf, strlen(buf), 0);
				//send(curr_sd, buf, strlen(buf), MSG_DONTWAIT);
			}
		}
	}
	}
}

void socketRun::receiveMessage(std::string buf, int id) {
	std::string s;
	std::string cmd;
	std::string args;
	std::size_t pos;
	std::size_t poscmd;

	while ((pos = buf.find("\r\n")) != std::string::npos) {
		s = buf.substr(0, pos);
		buf.erase(0, pos + 2);
		if ((poscmd = s.find(' ')) != std::string::npos) {
			cmd = s.substr(0, poscmd);
			args = s.substr(poscmd + 1);
		}
		else {
			args = "";
			cmd = s;
		}
		std::cout << "COMMAND RECEPTION --- "<< cmd << " " << args << std::endl;
		if (_commands[cmd])
			_commands[cmd](*this, args, id);
		else 
			std::cout << "Command does not exist...\n";
	}

}

void socketRun::readData() {

}

void socketRun::socketError(std::string str) {
	perror(str.c_str());
	close(_sd);
	exit(EXIT_FAILURE);
}

int socketRun::getPort() const {
	return _port;
}

const std::string &socketRun::getPwd() const {
	return _pwd;
}

const std::string	&socketRun::getHostname() {
	return _hostname;
}

void			socketRun::setHostname(std::string name) {
	_hostname = name;
}

const int			&socketRun::getCount() {
	return _count;
}

std::map<int, User*> 	&socketRun::getUserMap() {
	return _clients;
}

const std::string		&socketRun::getOpPwd() {
	return _opPwd;
}

std::ostream& operator<<(std::ostream& output, const socketRun &sock) {
	output << "port = " << sock.getPort() << std::endl;
	output << "password = " << sock.getPwd() << std::endl;
	return (output);
}
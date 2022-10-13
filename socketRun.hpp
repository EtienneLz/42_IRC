#ifndef SOCKETRUN_HPP
# define SOCKETRUN_HPP

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/poll.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <cerrno>
#include <vector>
#include "User.hpp"


//#define PORT 12345

class socketRun {
private:
	struct sockaddr_in	_address;
	int					_sd;
	int					_addrlen; //= sizeof(address);
	int					_port;
	int					_on;
	//int					_timeOut;
	//int					_nfds;
	std::string			_pwd;
	std::vector<User*> _client;
	
	socketRun();
public:
	socketRun(int port, std::string pwd);
	~socketRun();

	// CREATE SOCKET
	// void setSocket();
	// void bindSocket();
	// void listenSocket();

	void selectLoop();
	void readData();
	void socketError(std::string str);

	// GET
	int getPort() const;
	const std::string &getPwd() const;

};

std::ostream& operator<<(std::ostream& output, const socketRun &sock);

#endif
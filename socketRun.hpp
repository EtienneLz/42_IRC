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
#define TRUE 1
#define FALSE 0
#define INACTIVE -1

class socketRun {
private:
	struct sockaddr_in	_address;	// sd address
	int					_sd;		// server socket descriptor
	int					_addrlen;	//= sizeof(_address);
	int					_port;		// port used for connection
	int					_count;		// number of users
	std::string			_pwd;		// password
	std::vector<User*> _client;		// array of users

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
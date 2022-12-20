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
#include <map>
#include "User.hpp"
// #include "COMMAND/command.hpp"


//#define PORT 12345
#define TRUE 1
#define FALSE 0
#define INACTIVE -1

class socketRun {
public:
	typedef std::map<int, User*> 	mClient;
	typedef std::pair<int, User*>	pClient;
	typedef mClient::iterator		iterator;

private:
	struct sockaddr_in	_address;	// sd address
	int					_sd;		// server socket descriptor
	int					_addrlen;	//= sizeof(_address);
	int					_port;		// port used for connection
	int					_count;		// number of users
	std::string			_pwd;		// password
	mClient				_clients;	// array of users
	std::string			_hostname;	//name of server
	
	socketRun();
public:
	socketRun(int port, std::string pwd);
	~socketRun();

	// CREATE SOCKET
	// void setSocket();
	// void bindSocket();
	// void listenSocket();

	void selectLoop();
	// void newUser(int fdcl);
	void readData();
	void socketError(std::string str);

	void checkCmd();

	// GET
	int getPort() const;
	const std::string &getPwd() const;

	const std::string		&getHostname();
	void			setHostname(std::string name);
	const int		&getCount();
	mClient 	&getUserMap();
};

std::ostream& operator<<(std::ostream& output, const socketRun &sock);

#endif
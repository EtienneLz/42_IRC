#ifndef SOCKETRUN_HPP
# define SOCKETRUN_HPP

#include <sys/socket.h>
#include <sys/poll.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <iostream>


//#define PORT 12345

class socketRun {
private:
	struct sockaddr_in	_address;
	int					_sd;
	int					_addrlen; //= sizeof(address);
	int					_port;
	int					_on;
	int					_timeOut;
	int					_nfds;
	std::string			_pwd;
	struct pollfd		_pfd[200];
	socketRun();
public:
	socketRun(int port, std::string pwd);
	~socketRun();

	void pollLoop();
	void selectLoop();
	void socketError(std::string str);

};

#endif
#ifndef SOCKETRUN_HPP
# define SOCKETRUN_HPP

#include <sys/socket.h>
#include <netinet/in.h>

//#define PORT 12345

class socketRun {
private:
	struct sockaddr_in _address;
	int _sd;
	int _addrlen; //= sizeof(address);
	int _port;
	socketRun();
public:
	socketRun(int port);
	~socketRun();

};

#endif
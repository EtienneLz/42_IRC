#include "socketRun.hpp"

socketRun::socketRun(int port, std::string pwd) :_port(port), _pwd(pwd) {
	_on = 1;
	//_nfds = 1;
	_addrlen = sizeof(_address);
	if ((_sd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket() failed");
		exit(EXIT_FAILURE);
	}
	if (setsockopt(_sd, SOL_SOCKET, SO_REUSEADDR, (char*)&_on, sizeof(_on)) < 0)
		socketError("setsockopt() failed");
	if (fcntl(_sd, F_SETFL, O_NONBLOCK) < 0)
		socketError("fcntl() failed");
	//initialize sockaddr_in struct
	memset((char*)&_address, 0, _addrlen);
	_address.sin_family = AF_INET;
	_address.sin_addr.s_addr = htonl(INADDR_ANY);
	_address.sin_port = htons(_port);
	if (bind(_sd, (struct sockaddr *)&_address, _addrlen) < 0)
		socketError("bind() failed");
	if (listen(_sd, 3) < 0)
		socketError("listen() failed");
	std::cout << "Listening...\n";
	//initialize pollfd struct
	// memset(_pfd, 0, sizeof(_pfd));
	// _pfd[0].fd = _sd;
	// _pfd[0].events = POLLIN;
	/// set time to wait until the program will end if no activity
	//_timeOut = (3 * 60 * 1000);

}

socketRun::~socketRun() {

}

void socketRun::selectLoop() {
	fd_set rfds;
	struct timeval tv;
	int retval;
	int nb_conn;

	tv.tv_sec = 10;
	tv.tv_usec = 0;
	// select() loop
	while (retval > 0) {
	FD_ZERO(&rfds);
	FD_SET(_sd,&rfds);

	retval = select(_sd + 1, &rfds, NULL, NULL, &tv);

	if (retval == -1)
        perror("select() failed\n");
	else if (retval) {
	    printf("Data is available now\nsd prev = %d\n", _sd);
		if (FD_ISSET(_sd, &rfds)) {
			retval--;
			_client.push_back(new User());
		    printf("fd is set\n");

			for (std::vector<User*>::iterator it = _client.begin(); it != _client.end(); it++) {
				if ((*it)->fd == -1) {
					int fdcl;
					fdcl = accept(_sd, NULL, NULL);
					if (fdcl < 0) {
						perror("accept() failed");
						exit(EXIT_FAILURE);
					}
					printf("accept = %d\n", fdcl);
					(*it)->fd = fdcl;
					(*it)->num_conn = ++nb_conn;
					(*it)->count = 0;
					break;
				}
			}

			char buf[1000];
			int lus;
			lus = read(fdcl, buf, sizeof(buf));
			printf("lus = %d\nsd = %d\n", lus, _sd);
			if (lus > 0) {
				printf("Data received\n");
				printf("%s\n", buf);
			}
			std::string hello;
			hello = "Hello from server! : " + static_cast<std::string>(buf);
			int ret;
			ret = send(fdcl, hello.c_str(), strlen(hello.c_str()), 0);
			printf("ret = %d\n", ret);
		}
	}
	else
	    printf("No data within 10 seconds\n");
	}
	
}

void socketRun::readData() {

}

// void socketRun::selectLoop() {
// 	char buf[1024];

// 	struct timeval ltime; 
// 	ltime.tv_usec = 0;
// 	//time_t startListen = time(NULL);
// 	ltime.tv_sec = 60;
// 	//do {
// 		//int ret;
// 		int end_serv = 0;
// 		//int close_conn = 0;
// 		fd_set rfds, copyFds;
// 		int maxSd = _sd;
// 		int newSd;
// 	do {
// 		FD_ZERO(&rfds);
// 		FD_SET(_sd, &rfds);
// 		memcpy(&copyFds, &rfds, sizeof(rfds));
// 		std::cout << "Waiting on select()...\n";
// 		int ret = select(_sd + 1, &rfds, NULL, NULL, &ltime);
// 		if (ret == 0) {
// 			perror("select() timed out. End program.\n");
// 			break;
// 		}
// 		else if (ret < 0) {
// 			perror("select() failed.\n");
// 			break;
// 		}
// 		int ret_copy = ret;
// 		for (int i = 0; i <= maxSd && ret_copy > 0; ++i) {
// 			if (FD_ISSET(i, &copyFds)) {
// 				ret_copy--;
// 				if (i == _sd) {
// 					std::cout << "Listening socket is readable\n";
// 					do {
// 						newSd = accept(_sd, NULL, NULL);
// 						if (newSd < 0) {
// 							if (errno != EWOULDBLOCK) {
// 								perror("accept() failed.\n");
// 								end_serv = 1;
// 							}
// 							break;
// 						}
// 						if (fcntl(newSd, F_SETFL, O_NONBLOCK) < 0)
// 	                        socketError("fcntl() failed");
// 						write(newSd, "Hello from server\n", strlen("Hello from server\n"));
// 						std::cout << "New incoming connection - " << newSd << std::endl;
// 						FD_SET(newSd, &rfds);
// 						if (newSd > maxSd)
// 							maxSd = newSd;
// 					} while (newSd != -1);
// 				}
// 				else {
// 					std::cout << "Descriptor is readable\n";
// 					int close_conn = 0;
// 					do {
// 						std::cout << "Waiting to read...\n";
// 						int ret = recv(i, buf, sizeof(buf), 0);
// 						if (ret < 0) {
// 							if (errno != EWOULDBLOCK) {
// 								perror("recv() failed.\n");
// 								close_conn = 1;
// 							}
// 							break;
// 						}
// 						if (ret == 0) {
// 							std::cout << "Connection closed.\n";
// 							close_conn = 1;
// 							break;
// 						}
// 						int len = ret;
// 						printf("%s\n", buf);
// 						//write(newSd, buf, strlen(buf)); //TEST
// 						ret = send(i, buf, len, 0);
// 						if (ret < 0) {
// 							perror("send() failed.\n");
// 							close_conn = 1;
// 							break;
// 						}
// 					} while (1);
// 					if (close_conn) {
// 						close(i);
// 						FD_CLR(i, &rfds);
// 						if (i == maxSd) {
// 							while (FD_ISSET(maxSd, &rfds) == 0)
// 								maxSd--;
// 						}
// 					}
// 				}
// 			}
// 		}
		
// 	} while (end_serv == 0);
// 	for (int i = 0; i <= maxSd; ++i) {
// 		if (FD_ISSET(i, &rfds))
// 			close(i);
// 	}
// }



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

std::ostream& operator<<(std::ostream& output, const socketRun &sock) {
	output << "port = " << sock.getPort() << std::endl;
	output << "password = " << sock.getPwd() << std::endl;
	return (output);
}
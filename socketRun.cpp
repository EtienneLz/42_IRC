#include "socketRun.hpp"

socketRun::socketRun(int port, std::string pwd) :_port(port), _pwd(pwd) {
	_on = 1;
	_count = 0;
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
	int sd_max;
	int curr_sd;
	int i = 0;
	std::string welcome = "Welcome on our IRC server!\n"; 
	//int nb_conn;

	// select() loop
	while (TRUE) {

	tv.tv_sec = 10;
	tv.tv_usec = 0;
	FD_ZERO(&rfds);
	FD_SET(_sd,&rfds);
	sd_max = _sd;

	for (std::vector<User*>::iterator it = _client.begin(); it != _client.end(); it++) {
		curr_sd = (*it)->fd;
		if (curr_sd > 0)
			FD_SET(curr_sd, &rfds);
		if (curr_sd > sd_max)
			sd_max = curr_sd;
	}

	retval = select(sd_max + 1, &rfds, NULL, NULL, &tv);

	if (retval < 0 && errno != EINTR)
		perror("select() failed\n");
	else if (retval == 0) {
		printf("No data within 10 seconds\n");
		break;
	}
	if (FD_ISSET(_sd, &rfds)) {
		int fdcl;
		if ((fdcl = accept(_sd, (struct sockaddr *)&_address, (socklen_t*)&_addrlen)) < 0)
			socketError("accept() failed\n");
		if (send(fdcl, welcome.c_str(), welcome.length(), 0) != (ssize_t)welcome.length())
			perror("send() failed\n");
		_client.push_back(new User);
		for (std::vector<User*>::iterator it = _client.begin(); it != _client.end(); it++) {
			if ((*it)->fd == INACTIVE) {
				(*it)->fd = fdcl;
				(*it)->num_conn = i;
				_count++;
				printf("Adding new user with fd: %d at %d pos\n", (*it)->fd, (*it)->num_conn);
				printf("Number of users: %d\n", _count);
				break;
			}
			i++;
		}
		i = 0;
	}
	printf("ok 1\n");
	for (std::vector<User*>::iterator it = _client.begin(); it != _client.end(); it++) {
		curr_sd = (*it)->fd;
		char buf[1025];
		if (FD_ISSET(curr_sd, &rfds)) {
			int valread;
			if ((valread = read(curr_sd, buf, 1024)) == 0) {
				_count--;
				printf("User disconnected, pos: %d\n", (*it)->num_conn);
				printf("Number of users: %d\n", _count);
				close(curr_sd);
				(*it)->fd = INACTIVE;
			}
			else {
				buf[valread] = '\0';
				//sending msg back
				printf("\n%s\n", buf);
				send(curr_sd, buf, strlen(buf), 0);
			}
		}
	}
	printf("ok 2\n");
	}


	// if (retval == -1)
    //     perror("select() failed\n");
	// else if (retval) {
	//     printf("Data is available now\nsd prev = %d\n", _sd);
	// 	if (FD_ISSET(_sd, &rfds)) {
	// 		//retval--;
	// 		//_client.push_back(new User());
	// 	    printf("fd is set\n");

	// 		// for (std::vector<User*>::iterator it = _client.begin(); it != _client.end(); it++) {
	// 		// 	if ((*it)->fd == -1) {
	// 				int fdcl;
	// 				fdcl = accept(_sd, NULL, NULL);
	// 				if (fdcl < 0) {
	// 					perror("accept() failed");
	// 					exit(EXIT_FAILURE);
	// 				}
	// 				printf("accept = %d\n", fdcl);
	// 		// 		(*it)->fd = fdcl;
	// 		// 		(*it)->num_conn = ++nb_conn;
	// 		// 		(*it)->count = 0;
	// 		// 		break;
	// 		// 	}
	// 		// }

	// 		char buf[1025];
			
	// 		int lus;
	// 		lus = read(fdcl, buf, sizeof(buf));
	// 		printf("lus = %d\nsd = %d\n", lus, _sd);
	// 		if (lus > 0) {
	// 			buf[lus] = '\0';
	// 			printf("Data received\n");
	// 			printf("%s\n", buf);
	// 		}
	// 		std::string hello;
	// 		hello = "Hello from server! : " + static_cast<std::string>(buf);
	// 		int ret;
	// 		ret = send(fdcl, hello.c_str(), strlen(hello.c_str()), 0);
	// 		printf("ret = %d\n", ret);
	// 	}
	// }
	// else {
	//     printf("No data within 10 seconds\n");
	// 	break;
	// }
	// }
	
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

std::ostream& operator<<(std::ostream& output, const socketRun &sock) {
	output << "port = " << sock.getPort() << std::endl;
	output << "password = " << sock.getPwd() << std::endl;
	return (output);
}
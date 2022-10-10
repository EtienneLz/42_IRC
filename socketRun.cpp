#include "socketRun.hpp"

socketRun::socketRun(int port, std::string pwd) :_port(port), _pwd(pwd) {
	_on = 1;
	_nfds = 1;
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
	if (listen(_sd, 30) < 0)
		socketError("listen() failed");
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
	char buf[200];

	struct timeval ltime;
	ltime.tv_usec = 0;
	time_t startListen = time(NULL);
	ltime.tv_sec = 120;
	while (true) {
		fd_set rfds;
		FD_ZERO(&rfds);
		FD_SET(_sd, &rfds);
		int selectRet = select(_sd + 1, &rfds, NULL, NULL, &ltime);
		if (selectRet == 0) {
			perror("select() timed out. End program.\n");
			break;
		}
		else if (selectRet < 0) {
			perror("select() failed.\n");
			break;
		}
		else {
			int retRec = recv()
			if ()
		}
	}
}

void socketRun::pollLoop() {
	do {
		std::cout << "Waiting on poll()...\n";
		int ret = poll(_pfd, _nfds, _timeOut);
		if ( ret < 0) {
			perror("poll() failed");
			break;
		}
		if (ret == 0) {
			perror("poll() timed out. End program.\n");
			break;
		}
		int current = _nfds;
		for (int i = 0; i < current; i++) {

		}
	}
	//while ()
}

void socketRun::socketError(std::string str) {
	perror(str.c_str());
	close(_sd);
	exit(EXIT_FAILURE);
}
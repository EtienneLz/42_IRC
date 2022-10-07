#include "socketRun.hpp"

socketRun::socketRun(int port) :_port(port) {
	_addrlen = sizeof(_address);
	if ((_sd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket failed");
		exit(EXIT_FAILURE);
	}
}

socketRun::~socketRun() {

}
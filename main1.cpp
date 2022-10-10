#include "socketRun.hpp"
#include <iostream>

int main (int argc, char **argv) {
	if (argc != 3) {
		std::cout << "Wrong number of argument, please do ./ircserv <port> <password>\n";
		exit(0);
	}
	socketRun sox(atoi(argv[1]), static_cast<std::string>(argv[2]));
	std::cout << sox << std::endl;
	return (0);
}
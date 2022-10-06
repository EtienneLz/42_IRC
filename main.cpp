#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>

#define PORT 12345

int main(int argc, char **argv) {
	int sd;
	int new_socket;
	int read_ret;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buf[1024] = {0};
	std::string hello = "Hello from server!\n";

	if ((sd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	//fcntl(sd, F_SETFL, O_NONBLOCK);
	memset((char*)&address, 0, addrlen);
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htonl(INADDR_ANY);
	address.sin_port = htons(PORT);
	if (bind(sd, (struct sockaddr *)&address, addrlen) < 0) {
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	if (listen(sd, 3) < 0) {
		perror("error listen");
		exit(EXIT_FAILURE);
	}
	while (1) {
		printf("--- Waiting for connection ---\n");
		if ((new_socket = accept(sd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
		perror("error accept");
		exit(EXIT_FAILURE);
		}
		read_ret = read(new_socket, buf, 1024);
		printf("%s\n", buf);
		if (read_ret < 0)
			printf("No bytes to read\n");
		write(new_socket, hello.c_str(), strlen(hello.c_str()));
		close(new_socket);
		printf("--- Message sent ---\n");
	}
	return (0);
}
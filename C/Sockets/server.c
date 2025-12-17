#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080

int main(int argc, char const* argv[]) {
	int server_fd, new_socket;
	ssize_t valread;
	struct sockaddr_in address;
	int opt = 1;
	socklen_t addrlen = sizeof(address);
	char buffer[1024] = {0};
	char* hello = "Hello from server";

	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {  // 0 -> tcp connection
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	// Forcefully attaching socket to the port 8080
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	// Forcefully attaching socket to the port 8080
	if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	if (listen(server_fd, 5) < 0) {
		perror("listen");
		exit(EXIT_FAILURE);
	}
	printf("Server listening on port %d...\n", PORT);

	while (1) {
		printf("Waiting for a new connection...\n");
        char client_address[1024];

		if ((new_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen)) < 0) {
			perror("accept");
			// exit(EXIT_FAILURE);
            continue;
		}
        inet_ntop(AF_INET, &address, client_address, 1024 - 1);
        printf("Connected with client IP: %s\n", client_address);

		// subtract 1 for the null
		// terminator at the end
		valread = read(new_socket, buffer, 1024 - 1);
		printf("Data recieved: %s\n", buffer);
		// send(new_socket, hello, strlen(hello), 0);
        write(new_socket, hello, strlen(hello));
		printf("Hello message sent\n");

		// closing the connected socket
		close(new_socket);

	}
    // closing the listening socket
    close(server_fd);
    return 0;
}

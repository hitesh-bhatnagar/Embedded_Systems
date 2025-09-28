#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main(){
	int server_fd, new_socket;

	struct sockaddr_in address;
	int len = sizeof(address);
	char buffer[1024] = {0};
	char *hello = "Hello from server";

	// create socket
	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(server_fd == 0){
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	// define server address
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;	// listen on all interfaces
	address.sin_port = htons(PORT);

	// Bind socket to address/port
	if(bind(server_fd, (struct sockaddr *)&address, len) < 0) {
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

	// listen for connections
	if(listen(server_fd, 3) < 0){
		perror("listen");
		exit(EXIT_FAILURE);
	}
	printf("Server listening on port %d ... \n", PORT);

	// accept a client
	new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&len);
	  if (new_socket < 0) {
	      perror("accept");
	      exit(EXIT_FAILURE);
	  }

	  // receive message
	  read(new_socket, buffer, 1024);
	  printf("Message from client: %s\n", buffer);

	  // send reply
	  send(new_socket, hello, strlen(hello), 0);
	  printf("Hello message sent\n");

	  // close sockets
	  close(new_socket);
	  close(server_fd);

	  return 0;

}

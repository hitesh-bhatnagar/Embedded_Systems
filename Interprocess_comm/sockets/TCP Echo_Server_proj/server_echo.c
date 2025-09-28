#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main(){
	int server_fd, new_socket;
	struct sockaddr_in address;
	int addrlen = sizeof(address);
	char buffer[1024];

	int len = sizeof(address);

	// create socket
	server_fd = socket(AF_INET, SOCK_STREAM, 0);

	// Fill in server address
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	// Bind
	bind(server_fd, (struct sockaddr *)&address, len);

	// listen 
	listen(server_fd, 3);
	printf("Server listening on port &d ... \n", PORT);

	// Accept client
	new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);

	// Echo loop

	while(1){
		memset(buffer, 0, sizeof(buffer));
		int valread = read(new_socket, buffer, sizeof(buffer));
		if(valread <= 0) break;		// connection  closed
		printf("Client %s\n", buffer);

		send(new_socket, buffer, strlen(buffer), 0);	// echo back 
	}	

	close(new_socket);
	close(server_fd);
	return 0;
}

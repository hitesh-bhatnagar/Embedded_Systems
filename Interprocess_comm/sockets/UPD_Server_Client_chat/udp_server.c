#include <stdio.h>
#include  <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>

#define PORT 8080

int main(){

	int sockfd;
	char buffer[1024];
	struct sockaddr_in servaddr, client_addr;
	socklen_t len = sizeof(client_addr);

	// create socket 
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	// Fill server info
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = INADDR_ANY;		// accept from any client

	servaddr.sin_port = htons(PORT);

	// bind socket to port
	bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr));

	printf("UDP server listening on port %d ...\n", PORT);

	// Receive message
	int n = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&client_addr, &len);
	buffer[n] = '\0';
	printf("Client : %s\n", buffer);

	// Reply to client
	char*reply = "Hello from UDP server";
	sendto(sockfd, reply, strlen(reply), 0, (struct sockaddr *)&client_addr, len);

	close(sockfd);
	return 0;
}

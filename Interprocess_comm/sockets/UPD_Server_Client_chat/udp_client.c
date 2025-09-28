#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 8080

int main(){
	int sockfd;
	char buffer[1024];
	struct sockaddr_in servaddr;
	socklen_t len= sizeof(servaddr);

	// create socket
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	// Fill server info
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);

	inet_pton(AF_INET, "127.0.0.1",&servaddr.sin_addr);

	// send message to server
	char *msg = "Hello form UDP client";
	sendto(sockfd, msg, strlen(msg), 0, (struct sockaddr *)&servaddr, len);
	printf("Message sent\n");

	// Receive reply
	int n = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&servaddr, &len);
 	buffer[n] = '\0';

 	printf("Server : %s\n", buffer);
	
	close(sockfd);
	return 0;
}
 

#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 8080

int main(){
	int sock = 0;
	struct sockaddr_in serv_addr;
	char *arr = "Hello form client side";
	char buffer[1024] = {0};

	// create socket
	if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		printf("\n Socet creation error \n");
		return -1;
	}

	// Define server address
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	// Comvert TPv4 addresses from text to binary
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0){
		printf("\n Invalid address/ Address not supported \n");
		return -1;
	}	

	// Connet to server
	if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
		printf("\n Connection Failed\n");
		return -1;
	}


	// send message
	send(sock,arr , strlen(arr), 0);
	printf("message sent\n");

	// Receive reply
	read(sock , buffer, 1024);
	printf("Message from server : %s\n", buffer);


	close(sock);
	return 0;
	
}

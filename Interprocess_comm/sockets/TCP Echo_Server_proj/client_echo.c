#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>

#define PORT 8080

int main(void){

	int sock = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in serv_addr;
	char buffer[1024];

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

	connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

	while(1){
		printf("Enter message");
		fgets(buffer, sizeof(buffer), stdin);
		send(sock, buffer, strlen(buffer), 0);
		memset(buffer, 0, sizeof(buffer));

		read(sock, buffer, sizeof(buffer));
		printf("Server echoed: %s\n", buffer);

		
	}
	close(sock);
	
	return 0;
}

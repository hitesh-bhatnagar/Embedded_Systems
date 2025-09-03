#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(){
	int fd = open("myfifo", O_WRONLY);

	if(fd == -1){
		perror("open");
		return 1;
	}

	const char* msg = "Hello FIFO!";

	if(write(fd, msg, strlen(msg) + 1) == -1){
		perror("write");
		close(fd);
		return 1;
	}

	close(fd);
	printf("Message written to FIFO %s\n", msg);
	return 0;
}

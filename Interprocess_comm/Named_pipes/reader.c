#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void){
	char buffer[100];
	int fd = open("myfifo", O_RDONLY);

	if(fd == -1){
		perror("open");
		return 1;
		
	}

	ssize_t bytes_read = read(fd, buffer, sizeof(buffer) - 1);

	if(bytes_read > 0){
		printf("Read from FIFO %s\n", buffer);
		
	}else printf("Failed to read from FIFO \n");

	close(fd);
	return 0;
}

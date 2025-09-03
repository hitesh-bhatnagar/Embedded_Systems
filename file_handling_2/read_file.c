#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
	int fd;
	char buffer[50];
	fd = open("test_sys.txt", O_RDONLY);
	if(fd < 0){
		perror("Error opening  file");
		return 1;
	}

	read(fd, buffer, sizeof(buffer));
	printf("File content : %s\n", buffer);
	close(fd);
	return 0;
}

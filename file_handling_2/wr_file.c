    #include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
	int fd;			// File descriptor(Linux represents files with numbers)
	char msg[] = "Hello Embedded Linux!\n";

	// Opwn a file (create if not exists), write only
	fd = open("test_sys.txt", O_WRONLY | O_CREAT, 0644);	// 0644 permissions (owner read/write, others read)

	if(fd < 0){
		perror("Error operning file");
		return 1;
	}

	write(fd, msg, sizeof(msg));
	close(fd);
	return  0;
}

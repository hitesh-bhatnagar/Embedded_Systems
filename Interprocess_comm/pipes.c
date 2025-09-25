					// 		Parent - Child Char (Anonymous pipe)

/*
Pipe is a unidirectional comm. channel
Anaonymouse Pipe:	
	* Created with pipe(fd);
	* fd[0] = read end, fd[1] = write end
	* Work only between parent  child processes (after fork)

Named pipe (FIFO):
	* Created with mkfifo("myfifo", 0666)
	* Works between any two processes
	* behaves like a file (open , read, write)

*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(){
	int fd[2];
	char write_msg[] = "Hello from parent";
	char read_msg[100];

	if(pipe(fd) == -1){		// create a pipe
		perror("pipe failed");
		return 1;
	}

	pid_t pid = fork();

	if(pid < 0){
		perror("fork failed");
		return 1;
		
	}
	else if (pid > 0){		// parent process
		close(fd[0]);		
		write(fd[1], write_msg, strlen(write_msg) + 1);
		close(fd[1]);
	}

	else{		// child process
		close(fd[1]);		// close write end
		read(fd[0], read_msg, sizeof(read_msg));
		printf("Child received : %s\n", read_msg);
		close(fd[0]);
		
	}
	return 0;
}

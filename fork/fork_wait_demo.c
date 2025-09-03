#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void){

	pid_t pid = fork();

	if(pid == 0){
		printf("Child : Running 'date' command \n");
		execlp("date", "date", NULL);
		
	}
	else if(pid > 0){
		int status;
		wait(&status);	// makes paren tpause until child finishes parent can also check if the child exited normally (status)
		printf("Parent: Child finished with status %d\n", status);
		
	}
	else printf("Fork failed\n");
	

	return 0;
}

#include <stdio.h>
#include <unistd.h>
#include <time.h>

int main(){
	pid_t pid = fork();

	if(pid == 0) {
		printf("I am the child process!! PID = %d\n", getpid());
		for(int i = 1; i <=5; i++) printf("%d\n", i);
	}
	else if(pid > 0){
		printf("I am the parent process!! PID = %d, My child's PID = %d\n", getpid(), pid);
		for(char i = 'A'; i < 'F'; i++) printf("%c\n", i);
	}
	else printf("Fork failed\n");
	return 0;
}

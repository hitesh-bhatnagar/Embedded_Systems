#include <stdio.h>
#include <unistd.h>

int main(void){

	pid_t pid = fork();
	if(pid == 0) execlp("date", "date", NULL);	// child replaces itself with 'date'

	// Parent just prints the message
	else if(pid > 0) printf("Parent process (PID: %d), Child PID: %d\n", getpid(), pid);
	else printf("Fork failed!\n");
	return 0;
}

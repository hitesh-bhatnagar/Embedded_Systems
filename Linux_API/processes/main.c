#include<stdio.h>
#include <stdlib.h>		// general functions (exit)
#include <unistd.h>		// system calls (fork, execvp);
#include <string.h>
#include <sys/wait.h>	// wait() function 
#include <time.h>


#define max_Input 1024
#define max_Args 64

int main(void){

	char input[max_Input];
	char *args[max_Args];

	while(1){
		printf("MYSHELL >>> ");
		fflush(stdout);

		if(fgets(input, sizeof(input), stdin) == NULL) break; // reads user input

		input[strcspn(input, "\n")] = 0;	// remove new line character

		if(strcmp(input, "exit") == 0){
			printf("Existing myshell ... \n");
			break;
		}

		// split input into arguments
		int i = 0;
		char *token = strtok(input, " ");
		while(token != NULL && max_Args - 1){
			args[i++] = token;
			token = strtok(NULL, " " );
			
		}
		args[i] = NULL;
	
		pid_t pid = fork(); // create a child process

		if(pid < 0) perror("fork failed");
		else if(pid == 0) {
			execvp(args[0], args);
			perror("exec failed");
			exit(1);
		}
		else wait(NULL);	// wait for child to finish
	}

	return 0;
}

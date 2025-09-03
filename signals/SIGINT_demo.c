#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handle_sigint(int sig){
	printf("Caught signal %d (Ctrl + c). Exiting gracefully \n", sig);
	_exit(0);
}

int main(){
	signal(SIGINT, handle_sigint);		// register signal handler
	while(1){
		printf("Running .. Press Ctrl + C to stop. \n");
		sleep(2);
		
	}
	return 0;
}

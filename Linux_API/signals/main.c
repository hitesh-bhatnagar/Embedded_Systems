// Create a timer 
// when user prese Ctrl + C (SIGINT) if pressed y then terminates


#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <ctype.h>

volatile sig_atomic_t sigint_flag = 0;	// atomic means the operation happens all at once

void terminate(int sig){
	sigint_flag = 1;
}

int main(void){
	int sec = 0;
	char choice;

	signal(SIGINT, terminate);

	printf("safe timer started. Press Ctrl + C to stop \n");
	while(1){
		printf("Time elapsed %d sec \n", sec++);
		sleep(1);
		
		if(sigint_flag){
			printf("\n Caught SIGINT. Do you really wanna exit (y/n)");
			choice = getchar();

			while(getchar() != '\n' && getchar() != EOF);

			if(tolower(choice) == 'y'){
				printf("Exiting safely ... \n");
				exit(0);
			}else {
				printf("Continuing...\n");
				sigint_flag = 0;
			}
		}


	}
	return 0;
}

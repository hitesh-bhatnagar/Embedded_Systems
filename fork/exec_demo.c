#include <stdio.h>
#include <unistd.h>

int main(){
	printf("Before exec()\n");

	execlp("ls", "ls", "-l", NULL);

	printf("This will not run if exec is successful.\n");
	return 0;
}

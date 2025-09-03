// Pipes allow processes to communicate with each other (like UART/SPI/I2C in hardware)

// Ex: Parent sends data to child using a pipe

#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(){
    int fd[2];      // fd[0] = read end, fd[1] = write end
    pipe(fd);

    if(fork() == 0) {   // child process
        close(fd[1]);       // close write end
        char msg[100];
        read(fd[0], msg, sizeof(msg));

        printf("Child received : %s\n", msg);

    } else{         // Parent process
        close(fd[0]);   // close read end
        char *txt = "Hello ji ki haal chaal";
        write(fd[1], txt, strlen(txt) + 1);   
    }
    return 0;

}
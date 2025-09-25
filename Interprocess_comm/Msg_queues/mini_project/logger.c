#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include "logmsg.h"

int main(){
    struct log_message  msg;
    FILE *logfile = fopen("system.log", "a");
    if (!logfile){
        perror("fopen failed");
        exit(1);
    }

    // create or get queue
    int qid = msgget(MSG_KEY, 0666 | IPC_CREAT);
    if(qid == -1){
        perror ("msgget failed");
        exit(1);
    }

    printf("Logger started. Writing to system.log ...\n");

    while(1){
        // Receive any type of message
        if(msgrcv(qid, &msg, sizeof(msg.text), 0, 0) == -1){
            perror("msgrcv failed");
            exit(1);
        }

        // special exit signal
        if(strcmp(msg.text, "exit") == 0){
          printf("Logger shutting down. \n");
          break;
        }
        
        fprintf(logfile, "LOG: %s\n", msg.text);
        fflush(logfile);
        
    }
    
    fclose(logfile);
    msgctl(qid, IPC_RMID, NULL);  // remove queue
    return 0;

}

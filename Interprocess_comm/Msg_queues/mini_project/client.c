#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <string.h>
#include <sys/msg.h>
#include "logmsg.h"

int main(){
	struct log_message msg;
	int qid = msgget(MSG_KEY, 0666 | IPC_CREAT);
	if(qid == -1){
		perror("msgget failed");
		exit(1);
	}

	while(1){
		printf("Enter log message (or 'exit' to quit): ");
		fgets(msg.text, sizeof(msg.text), stdin);

		msg.text[strcspn(msg.text, "\n")] = '\0';	
		msg.msg_type = 1;

		if(msgsnd(qid, &msg, sizeof(msg.text), 0) == -1) {
			perror("msgsnd failed");
			exit(1);
		}

		if(strcmp(msg.text, "exit") == 0) break;
	}
	return 0;
}



#ifndef LOGMSG_H
#define LOGMSG_H

#define MSG_KEY 1234

struct log_message {
	long msg_type;
	char text[100];
	
};

#endif

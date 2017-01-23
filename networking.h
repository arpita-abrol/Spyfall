#ifndef NETWORKING_H
#define NETWORKING_H

#define MESSAGE_BUFFER_SIZE 1000

struct user_data {
	char usr_pid[8];
	char username[8];
	char role[8];
	short spy;
};

void error_check( int i, char *s );
void get_user( char *username );

int server_setup();
int server_connect(int sd);

int client_connect( char *host, char *username );

#endif
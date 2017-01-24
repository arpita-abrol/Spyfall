#ifndef NETWORKING_H
#define NETWORKING_H

#define MESSAGE_BUFFER_SIZE 1000

struct player_info {
  int usrid;
  char username[20];
  char role[30];
  int spy; 
};

void error_check( int i, char *s );
void get_user( char *username );

int server_setup();
int server_connect(int sd);

int client_connect( char *host, char *username );

#endif
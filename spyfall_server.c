#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "networking.h"


void process( char * s );
void sub_server( int sd );

int players = 0;
int player_ids[5];
char *user;

int main() {

  int sd, connection;
  sd = server_setup();
    
  while (players < 5) {

    connection = server_connect( sd );
    player_ids[players] = connection;
    players++;

    int f = fork();
    if ( f == 0 ) {

      close(sd);
      sub_server( connection );

      exit(0);
    }
    else {
      close( connection );
    }
  }
  return 0;
}

void sub_server( int sd ) {

  char buffer[MESSAGE_BUFFER_SIZE];
  while (read( sd, buffer, sizeof(buffer) )) {

    printf("[%d] received: %s\n", getpid(), buffer );
    write( sd, buffer, sizeof(buffer));
  }
  
}

int choose_player(int sd) { 
  write(sd, "Which player would you like to interrogate?", 30);
  return 0;
}

void interrogate_player(int sd) {
  int usrid = choose_player(sd);
  char buffer[MESSAGE_BUFFER_SIZE];

  //Reads question from interrogator
  write(sd, "What would you like to ask?", 26);
  read(sd, buffer, sizeof(buffer));

  //Write question to player being interrogated
  write(usrid, "Interrogator ask:", 16);
  write(usrid, buffer, sizeof(buffer));

  //Read response from player
  read(usrid, buffer, sizeof(buffer));
}


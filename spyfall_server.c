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

void sub_server(int sd, int player_id);
void process (char *s);

int player_ids[5];
int USERNAME_SIZE;

int main() {

  printf("Welcome to Spyfall\n");
  printf("Connect clients to begin\n");
  
  int sd, connection;
  sd = server_setup();
    
  while (NUM_PLAYERS < 7) {

    connection = server_connect( sd );
    PLAYERS[NUM_PLAYERS].usrid = connection;
    //players++;

    int f = fork();
    if ( f == 0 ) {

      close(sd);
      sub_server( connection, NUM_PLAYERS );
      
      exit(0);
    }
    else {
      close( connection );
    }
  }
  return 0;
} 

void sub_server( int sd, int player_id ) {
   char buffer[MESSAGE_BUFFER_SIZE];
   read(sd, PLAYERS[player_id].username, USERNAME_SIZE);
   //printf("%s connected", username);
    while (read( sd, buffer, sizeof(buffer) )) {
      printf("[SERVER %d] received: %s\n", getpid(), buffer );
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
  read(sd, buffer, MESSAGE_BUFFER_SIZE);

  //Write question to player being interrogated
  write(usrid, "Interrogator ask:", 16);
  write(usrid, buffer, sizeof(buffer));

  //Read response from player
  read(usrid, buffer, MESSAGE_BUFFER_SIZE);
}


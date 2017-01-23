#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#include <ctype.h>

#include "networking.h"

//checks to make sure username is 5-15 chars and alphanumeric(a-z, A-Z, 0-9)
int check_username( char* username ) {
  int i = 0;
  char c[1];
  if( strlen(username) > 15 || strlen(username) < 5) {
    return 0;
  }
  for( ; i < strlen(username); i++ ) {
    strncpy(c, &username[i], 1);
    if( isalnum((int)c) != 0) {
      return 0;
    }
  }  
  return 1;
}


int main( int argc, char *argv[] ) {
  
  /*-----------------------------------------------
      Choose username
  -----------------------------------------------*/
  char buffer[MESSAGE_BUFFER_SIZE]; //buffer for messages
  short check = 0;
  char username[16];
  
  printf("Welcome to Spyfall.\n");
  //get username from person. check for alphanumeric and size. check for usage by others
  while( !check ) {
    printf("Please choose your username. Usernames can only be composed of alphanumeric characters and have between 5 and 15 characters.\n");
    fgets( buffer, sizeof(buffer), stdin );
    buffer[strcspn(buffer, "\n")] = 0;
    strcpy(username, buffer);
    check = check_username(username);
  }
  printf("Welcome, %s\n", username);
  
  //check if first player

  /*-----------------------------------------------
      Connecting to Server
  -----------------------------------------------*/
  
  char *host;
  if (argc != 2 ) {
    printf("host not specified, conneting to 127.0.0.1\n");
    host = "127.0.0.1";
  }
  else
    host = argv[1];
  
  int sd;

  sd = client_connect( host, username );

  /*-----------------------------------------------
      Send messages to server
  -----------------------------------------------*/ 
  
  while (1) {
    printf("enter message: ");
    fgets( buffer, sizeof(buffer), stdin );
    char *p = strchr(buffer, '\n');
    *p = 0;

    write( sd, buffer, sizeof(buffer) );
    read( sd, buffer, sizeof(buffer) );
    printf( "received: %s\n", buffer );
  }
  
  return 0;
}
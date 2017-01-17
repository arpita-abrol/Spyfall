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

int main( int argc, char *argv[] ) {

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

  sd = client_connect( host );
  
  /*-----------------------------------------------
      Choose username
  -----------------------------------------------*/
  char buffer[MESSAGE_BUFFER_SIZE]; //buffer for messages
  short check = 0;
  
  char *username[16];
  printf("Welcome to Spyfall. Please choose your username. Usernames can only be composed of alphanumeric characters and have between 5 and 15 characters.\n");
  //get username from person. check for alphanumeric and size. check for usage by others
  fgets( buffer, sizeof(buffer), stdin );
  while( !check ) {
    check = 1;
  }
  *username = strchr(buffer, '\n');
  printf("Welcome, %s\n", *username);
  
  //check if first
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
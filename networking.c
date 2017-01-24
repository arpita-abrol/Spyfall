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

int ctr = 0;

int error_check( int i, char *s ) {
  if ( i < 0 ) {
      printf("[%s] socket error %d: %s\n", s, errno, strerror(errno) );
    return 1;
  }
  return 0;
}

int server_setup() {
  
  int sd;
  int i;
  
  sd = socket( AF_INET, SOCK_STREAM, 0 );
  error_check( sd, "server" );
  
  struct sockaddr_in sock;
  sock.sin_family = AF_INET;
  sock.sin_addr.s_addr = INADDR_ANY;
  sock.sin_port = htons(9001);
  i = bind( sd, (struct sockaddr *)&sock, sizeof(sock) );
  error_check( i, "server" );
  
  return sd;
}

int server_connect(int sd) {
  int connection, i;

  i = listen(sd, 1);
  error_check( i, "server" );
  
  struct sockaddr_in sock1;
  unsigned int sock1_len = sizeof(sock1);
  connection = accept( sd, (struct sockaddr *)&sock1, &sock1_len );
  error_check( connection, "server" );
  
  printf("[server] connected to %s\n", inet_ntoa( sock1.sin_addr ) );
  
  return connection;
}


int client_connect() {

  int errors;

  char host[20];

  printf("Please enter the IP address of the server you wish to connect to: (ex. 127.0.0.1)\n");
  fgets(host, 20, stdin);

  int sd, i;
  
  sd = socket( AF_INET, SOCK_STREAM, 0 );
  errors = error_check( sd, "client" );
  if (errors) {
    return -1;
  }
  
  struct sockaddr_in sock;
  sock.sin_family = AF_INET;
  inet_aton( host, &(sock.sin_addr));
  sock.sin_port = htons(9001);
  
  printf("Connecting to: %s\n", host );
  i = connect( sd, (struct sockaddr *)&sock, sizeof(sock) );
  errors = error_check( i, "client");
  if (errors) {
    return -1;
  }
  
  return sd;
}

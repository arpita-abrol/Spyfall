#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "spyfall_client.h"


int client_connect( char *host ) {
  int sd, i;
  
  sd = socket( AF_INET, SOCK_STREAM, 0 );
  error_check( sd, "client socket" );
  
  struct sockaddr_in sock;
  sock.sin_family = AF_INET;
  inet_aton( host, &(sock.sin_addr));
  sock.sin_port = htons(9001);
  
  printf("[client] connecting to: %s\n", host );
  i = connect( sd, (struct sockaddr *)&sock, sizeof(sock) );
  error_check( i, "client connect");
  
  return sd;
}

int main() {
  printf("Welcome to Spyfall\n");
  printf("Please enter the IP address of the Spyfall server:");

  int ip_address = fgets( buffer, sizeof(buffer), stdin );

}

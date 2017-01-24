#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include "networking.h"
//#include "roles.c"

void sub_server(int sd, int player_id);
void process (char *s);

int player_ids[5];
int USERNAME_SIZE;
int NUM_PLAYERS = 0;


char LOCATIONS_ARR[30][20] = {"Airplane","Amusement Park","Bank","Beach","Carnival","Casino","Circus Tent", "Corporate Party", "Crusader Army", "Day Spa", "Embassy", "Hospital", "Hotel", "Military Base", "Movie Studio", "Nightclub", "Oceanliner", "Passenger Train", "Pirate Ship", "Polar Station", "Police Station", "Restaurant", "School", "Service Station", "Space Station", "Submarine", "Supermarket", "Theater", "University", "Zoo"};


int main() {

  printf("Welcome to Spyfall\n");
  //int loc = getLocation();
  // char *location_chosen  = LOCATIONS_ARR[loc];
  // printf("%s\n", location_chosen);
  printf("Connect clients to begin\n");
  
  int sd, connection;
  sd = server_setup();

    
  /*****************Create shared memory*******************/
   char c;
  int shmid;
  key_t key;
  char*shm, *s;

  key = 694;

  //Create shared memory segment
  if ((shmid = shmget(key, 1000, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
  }

  //Attach shared memory
  if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }

  //Write to shared memory
  s = shm;

    for (c = 'a'; c <= 'z'; c++)
        *s++ = c;
    *s = (char) NULL;
    
  /*******************************************************/
    
    
  while (NUM_PLAYERS < 8) {

    connection = server_connect( sd );
    PLAYERS[NUM_PLAYERS].usrid = connection;
    NUM_PLAYERS++;

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

  printf("The max number of players has connected. The game will now begin.");
  //printf("%s was selected as the location", LOCATIONS_ARR[loc]);
   
  return 0;
}

void sub_server( int sd, int player_id ) {


  /*****************Access shared memoy*******************/
  char c;
  int shmid;
  key_t key;
  char*shm, *s;

  key = 694;

  //Access shared memory segment
  if ((shmid = shmget(key, 1000, 0666)) < 0) {
    perror("shmget");
    exit(1);
  }

  //Attach shared memory
  if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
  }

  //Read from shared memory
  printf("%s\n", s);
  /*******************************************************/
 
  
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


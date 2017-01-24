#ifndef NETWORKING_H
#define NETWORKING_H

#define MESSAGE_BUFFER_SIZE 1000

//char LOCATIONS_ARR[30][20] = {"Airplane","Amusement Park","Bank","Beach","Carnival","Casino","Circus Tent", "Corporate Party", "Crusader Army", "Day Spa", "Embassy", "Hospital", "Hotel", "Military Base", "Movie Studio", "Nightclub", "Oceanliner", "Passenger Train", "Pirate Ship", "Polar Station", "Police Station", "Restaurant", "School", "Service Station", "Space Station", "Submarine", "Supermarket", "Theater", "University", "Zoo"};

struct player_info {
  int usrid;
  int usrpid;
  char username[20];
  char role[30];
  int spy; 
};

//int NUM_PLAYERS = 0;
char LOCATION[5];
struct player_info PLAYERS[7];


int error_check( int i, char *s );
void get_user( char *username );

int server_setup();
int server_connect(int sd);

int client_connect();

#endif

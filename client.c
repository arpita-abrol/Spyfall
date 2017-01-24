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

#include <ctype.h>

#include "client.h"
#include "networking.h"

static int game_active;

/*
  1 = Game start waiting screen
  2 = Player's turn Screen
  3 = Message input
 */
static int game_status;

int main() {
  
  char buffer[MESSAGE_BUFFER_SIZE];
  int sd;
  
  printf("Welcome to Spyfall\n");
  sd = connect_to_server();

  select_username();
  //create_status_memory();

  // int f = fork();
  //if (f == 0) {
    //communication_manager();
  // }
  
  game_active = 1;
  game_status = 2;

  while (game_active) {
    
    int user_selection;
    int valid_input = 0;

    if (game_status == 1) {
      printf("Please wait for the game to start");
      
     
    } else if (game_status == 2) {
      
      while (!valid_input) {
	print_turn_options();
	fgets(buffer, MESSAGE_BUFFER_SIZE, stdin);
	valid_input = is_valid_menu_selection(buffer);
	user_selection = atoi(buffer);
      }
      
      execute_turn_selection(user_selection, sd);
     

    } else if (game_status == 3) {
       while (1) {
	 printf("enter message: ");
	 fgets( buffer, sizeof(buffer), stdin );
	 char *p = strchr(buffer, '\n');
	 *p = 0;
	 
	 write( sd, buffer, sizeof(buffer) );
	 read( sd, buffer, sizeof(buffer) );
	 printf( "received: %s\n", buffer );
       }
    }

  }
  
}

/*
 * Connects client to server
 * 
 * Returns:
 * int: socket descriptor
 */
int connect_to_server() {
  int sd;
  while (sd <= 0) {
  sd = client_connect();
  if (sd < 0) {
    printf("Unable to connect to address entered\n");
  }
  }
  printf("Connection successful\n");
  return sd;
}

/*
 * Makes user select a username
 */
void select_username() {
  int check = 0;
  char buffer[100];
  char username[16];
  printf("Please choose your username. Usernames can only be composed of alphanumeric characters and have between 5 and 15 characters.\n");

  while (!check) {
    printf("enter username:\n");
    fgets( buffer, sizeof(buffer), stdin );
    buffer[strcspn(buffer, "\n")] = 0;
    strcpy(username, buffer);
    check = check_username(username);
    if (!check) {
      printf("Username is invalid, please try again");
    }
  }
}

/*
 * Create shared memory for game status
 */
/*
void create_status_memory() {
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
 }
*/

/*
 * Access shared memory for game status
 */
/*
void access_status_memory() {
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
}
*/

/*
 * Manages communications between client and server
 *
 * Params:
 * int sd: socket descriptor
 */
void communication_manager(int sd) {
  char buffer[100];
  
  //access_status_memory();
   while (read( sd, buffer, sizeof(buffer) )) {
      printf("[SERVER %d] received: %s\n", getpid(), buffer );
      write( sd, buffer, sizeof(buffer));    
    }  
}

/*
 * Send player status to server
 *
 * Params:
 * int status: status of player
 * int sd: socket descriptor
 */
void send_status(char* status, int sd) {
  write(sd, status, sizeof(status));
}


/*
 * Checks username validity
 * 5-15 chars and alphanumeric(a-z, A-Z, 0-9)
 * 
 * Params:
 * char* username: buffer with user inputed username
 */
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

/*
 * Prints menu options available to the player during their turn
 */
void print_turn_options() {
  printf("Please make a selection:");
  printf("\n1)Interrogate another player\n");
  if (1) {
    printf("2)Guess location\n");
  } else {
    printf("2)Guess spy\n");
  }
  printf("3)Show locations\n");
  printf("4)Show jobs\n");
}


/*
 * Print the locations for the game
 */
void print_locations() {
  printf("\nLocation:\n");
  printf("1)Airplane        2)Amusement Park   3)Bank             4)Beach            5)Carnival\n");
  printf("6)Casino          7)Circus Tent      8)Corporate Party  9)Crusader Army    10)Day Spa\n");
  printf("11)Embassy        12)Hospital        13)Hotel           14)Military Base   15)Movie Studio\n");
  printf("16)Nightclub      17)Oceanliner      18)Passenger Train 19)Pirate Ship     20)Polar Station\n");
  printf("21)Police Station 22)Restaurant      23)School          24)Service Station 25)Space Station\n");
  printf("26)Submarine      27)Supermarket     28)Theater         29)University      30)Zoo\n\n");
}

/*
 * Print jobs
 */
void print_jobs() {
  printf("\nJobs:\n");
  printf("Airplane: 1st Class Passenger, Air Mashal, Mechanic, Coach Passenger, Flight Attendant, Co-Pilot, Captain\n");
  printf("Bank: Armored Car Driver, Bank Manager, Loan Consultant, Bank Robber, Customer, Security Guard, Bank Teller\n");
  printf("Beach: Beach Bartender, Kite Surfer, Lifeguard, Thief, Beach Goer, Beach Photographer, Ice Cream Man\n");
  printf("Casino: Bartender, Head of Security, Bouncer, Pit Boss, Hustler, Dealer, Gamblr\n");
  printf("Cathedral: Priest, Begger, Sinner, Parishioner, Tourist, Deacon, Choir Singer\n");
  printf("Circus Tent: Acrobat, Animal Tamer, Magician, Audience Member, Fire Easter, Clown, Juggler\n");
  printf("Corporate Party: Entertainer, Manager, Party Crasher, Owner/CEO, Admin Assistant, Accountant, Delivery Boy\n");
  printf("Crusader Army: Monk, Imprisoned Arab, Servant, Bishop, Squire, Archer, Knight\n");
  printf("Day Spa: Customer, Stylist, Massage Tech, Manicurist, Makeup Artist, Dematologist, Beautifican\n");
  printf("Embassy: Security Guard, Admin Assistant, Ambassador, Government Official, Tourist, Regufee, Diplomat\n");
  printf("Hospital: Nurse, Doctor, Anesthesiologist, Intern, Patient, Therapist, Surgeon\n");
  printf("Hotel: Doorman, Security Guard, Hotel Manager, Housekeeper, Hotel Guest, Bartender, Valet\n");
  printf("Military Base: Deserter, Colonel, Medic, Solider, Sniper, Executive Officer, Tank Commander\n");
  printf("Movie Studio: Stuntman, Sound Engineer, Cameraman, Director, Costume Artist, Actor, Producer\n");
  printf("Ocean Liner: Rich Passenger, Cook, Captain, Bartender, Musician, Waiter, Ship's Mechanic\n");
  printf("Passenger Train: Mechanic, Border Patrol, Chef, Engineer, Steward, Ticket Taker, Passenger\n");
  printf("Pirate Ship: Cook, Sailor, Slave, Cannoneer, Bound Prisoner, Cabin Boy, Pirate Captain\n");
  printf("Polar Station: Medic, Geologist, Expedition Leader, Biologist, Radioman, Hydrolohist, Meteorologist\n");
  printf("Police Station: Detective, Lawyer, Journalist, Forensic Scientist, Evidence Archivist, Patrol Officer, Criminal\n");
  printf("Restaurant: Musician, Customer, Table Busser, Host, Head Chef, Food Critic, Server\n");
  printf("School: Teacher, Student, Principal, Security Guard, Janitor, Lunch Lady, Maintenance Man\n");
  printf("Service Station: Manager, Tire Specialist, Motorcyclist, Car Owner, Car Washer, Diagnostic Tech, Auto Mechanic\n");
  printf("Space Station: Engineer, Alien, Tourist, Pilot, Mission Commander, Scientist, Doctor\n");
  printf("Submarine: Cook, Captain, Sonar Operator, Weapons Technician, Sailor, Radioman, Naviagotr\n");
  printf("Supermarket: Customer, Cashier, Butcher, Janitor, Produce Manager, Food Sample Demo, Shelf Stocker\n");
  printf("University: Graduate Student, Professor, Dean, Psychologist, Maintenance Man, Student, Advisor\n");
  printf("Theater: Coat Check, Cue Card Prompter, Ticket Office Cashier, Theater Visitor, Director, Actor, Crewman\n\n");
}


/*
 * Checks if user made a valid menu selection
 * Params:
 * char[] buffer: buffer where user input is stored
 */
int is_valid_menu_selection(char *buffer) {
  int selection = atoi(buffer);

  if (selection == 0) {
    return 0;
  }

  if (game_status == 2) {
    return selection <= TURN_MENU_OPTIONS;
  }
  return 0;
}

/*
 * Executes the user's selection during turn
 * Params:
 * int selection: the menu option the user selected
 */
void execute_turn_selection(int selection, int sd) {
  if (selection == 1) {
    interrogate_player(sd);
  } else if (selection == 2) {
    guess_player(sd);
  } else if (selection == 3) {
    print_locations();
  } else if (selection == 4) {
    print_jobs();
  }
}

/*
 * Interrogate other players by aksing questions
 * Params:
 * int sd: socket descriptor
 */
void interrogate_player(int sd) {
  char buffer[100];
  
  printf("Who would you like to interrogate?\n");
  fgets(buffer, sizeof(buffer), stdin);
  write(sd, buffer, sizeof(buffer));

  printf("What would you like to ask?\n");
  fgets(buffer, sizeof(buffer), stdin);
  write(sd, buffer, sizeof(buffer));

  read(sd, buffer, sizeof(buffer));
  printf("Response: %s\n", buffer);
  
    
}

/*
 * Guess which of the players is the spy
 * Params:
 * int sd: socket descriptor
 */
void guess_player(int sd) {
  char buffer[100];

  printf("Which player do you think is the spy?\n");
  fgets(buffer, sizeof(buffer), stdin);
  write(sd, buffer, sizeof(buffer));
  printf("Response: %s\n", buffer);
}









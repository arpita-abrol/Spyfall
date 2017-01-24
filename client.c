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

#include "client.h"
#include "networking.c"

static int game_active;

/*
  1 = Game start waiting screen
  2 = Player's turn Screen
 */
static int game_status;

int main() {
  
  char buffer[MESSAGE_BUFFER_SIZE];
  int sd;
  
  printf("Welcome to Spyfall\n");
  sd = connect_to_server();

  game_active = 1;
  game_status = 1;

  while (is_game_active) {
    
    int user_selection;
    int valid_input = 0;
  
    if (game_status == 2) {
      
      while (!valid_input) {
	print_turn_options();
	fgets(buffer, MESSAGE_BUFFER_SIZE, stdin);
	valid_input = is_valid_menu_selection(buffer);
	user_selection = atoi(buffer);
      }
      
      execute_turn_selection(user_selection);
      is_game_active = 0;

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
 * Checks if user made a valid menu selection
 * Params:
 * char[] buffer: buffer where user input is stored
 */
int is_valid_menu_selection(char *buffer) {
  int selection = atoi(buffer);

  if (selection == 0) {
    return 0;
  }

  if (game_status == 1) {
    return selection <= TURN_MENU_OPTIONS;
  }
  return 0;
}

/*
 * Executes the user's selection during turn
 * Params:
 * int selection: the menu option the user selected
 */
void execute_turn_selection(int selection) {
  if (selection == 1) {
    printf("Interrogation is currently unavailable\n");
  } else if (selection == 2) {
    printf("Guessing is currently unavailable\n");
  } else if (selection == 3) {
    print_locations();
  }
}









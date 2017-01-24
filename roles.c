#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include "networking.h"
#include "roles.h"



int location;
int numPlayers;


void giveRole( int numPlayers, struct player_info players[7] ) {
	int usedNums[numPlayers];
	int num;
	int ctr;
	int i;
	for(i = 0; i < numPlayers; ){
	    num = rand() % 8;
	    for(ctr = 0; ctr < numPlayers; ctr++) {
	    	if( num != usedNums[ctr] ) {
	    		getRole( num, players, i );
	    		usedNums[i] = num;
	    		i++;
	    	}
	    }
  }
}

void getLocation() {
	srand(time(NULL));
	int r = rand() % 27;
	location = r;
	printf(" %d\n ", r);
}

void getRole( int roleNum, struct player_info players[7], int player ) {
	int lineNumber = location * 9 + roleNum;
	char line[256];
	static const char filename[] = "roles.txt";
	FILE *file = fopen(filename, "r");
	int ctr = 0;
	if ( file != NULL ) {
	    while (fgets(line, sizeof line, file) != NULL) {
	        if (ctr == lineNumber) {
	        	strtok(line, "\n");
	        	printf("%s\n", line);
	        	strcpy(players[player].role,line);
	        	break;
	        }
	        else {
	            ctr++;
	        }
	    }
	    fclose(file);
	}
}
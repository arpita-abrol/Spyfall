#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include "networking.h"
#include "roles.h"


int location;


void giveRole() {
	int usedNums[NUM_PLAYERS]; 
	int num;
	int ctr;
	int i;
	for(i = 0; i < NUM_PLAYERS; ){
	    num = rand() % 8;
	    for(ctr = 0; ctr < NUM_PLAYERS; ctr++) {
	    	if( num != usedNums[ctr] ) {
	    		if( i == 1 ) {
	    			PLAYERS[i].spy = 1;
	    		}
	    		getRole( num, i );
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

	char line[256];
	static const char filename[] = "roles.txt";
	FILE *file = fopen(filename, "r");
	int ctr = 0;
	if ( file != NULL ) {
	    while (fgets(line, sizeof line, file) != NULL) {
	        if (ctr == location) {
	        	strtok(line, "\n");
	        	printf("%s\n", line);
	        	LOCATION = line;
	        	break;
	        }
	        else {
	            ctr++;
	        }
	    }
	    fclose(file);
	}

	printf(" %d\n ", r);
}

void getRole( int roleNum, int player ) {
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
	        	strcpy(PLAYERS[player].role,line);
	        	break;
	        }
	        else {
	            ctr++;
	        }
	    }
	    fclose(file);
	}
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct user_info;

int * role(int players){
  int * assign;
  int i;
  time_t t;

  assign = (int *)calloc (players, sizeof(int));

  for (i = 0 ; i < players ; i++){
    assign[i] = 0;
  }
  sleep(1);
  srand((unsigned) time(&t));
  assign[rand() % players ] = 1;
  for (i = 0 ; i < players ; i++){
    printf("%d ", assign[i]);
  }
  printf("\n");
  return assign;
}

void chooserole (char * roles, int usednums[]){
  time_t t;
  srand((unsigned) time(&t));
  int players = sizeof(usednums)/sizeof(int);
  int randnum = rand() % players;
  int i,n;
  int playernums[players];
  for (i = 0; i < players ; i++){
    for (n = 0; n < players ; n++){
      if (usednums[n] == i){
	i++;
	n = 0;
      }
    }
    if (i <= players)
      playernums[i] = i;
  }
  
}



int main(){
  const char * beach[7];
  beach[0] = "a";
  beach[1] = "b";
  beach[2] = "c";
  beach[3] = "d";
  beach[4] = "e";
  beach[5] = "f";
  beach[6] = "g";

  int * decider = role(6);
  int i;
  char returnlist[6][2];
  int usednum[7];
  for(i = 0; i < 6; i++){
    printf("%d :" , i);
    if (decider[i] == 0){
      printf(" not spy\n");
      chooserole(beach,usednum);
    }
    else{
      printf(" spy\n");
      strcpy(returnlist[i], "spy");
    }
  }
  return 0;
}

    

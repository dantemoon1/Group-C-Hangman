#include <stdio.h>
#include <stdlib.h> //need to find a better way to generate random numbers


const char* pickword(){
	int r = rand() % 85; //get a random number between 0 and 84
	r++;
	FILE *f = fopen("words.txt","r"); //open the file
	int count = 0;
	char *word = malloc(100);
	if(f!=NULL){
		char line[100];
		while(fgets(line,sizeof line,f)!=NULL){ 
			if(count == r){ //if the line number equals the random number, return that word
				strcpy(word,line);
				return word;
			} else {
				count++;
			}
		}
		fclose(f);
	}
	return "error";
}

int main(void) {
	char s[100]; //menu input
	char n[100]; //name input
	while(1){
		printf("hello and welcome to hangman, please enter an option from below:\n	1. Single Player\n	2. Multiplayer\n	3. Exit\n");
		fgets(s, 3, stdin); //get input and store it in the array
		if(s[0]=='1'){ //singleplayer
			printf("please enter your name: ");
			fgets(n,100,stdin);
			char *word = pickword(); //this is the random word
			break;
		}
		if(s[0]=='2'){ //multiplayer
			printf("please enter your name: ");
			fgets(n,100,stdin);
			char *word = pickword(); //this is the random word
			break;
		}
		if(s[0]=='3'){ //exit
			break;
		}
	}
  return 0;
}
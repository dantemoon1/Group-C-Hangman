//Project for CST-237
//Creators: Autumn Benton, Dante Moon, Zihao Xu, Jose Diaz-Trinidad
//Finished on April 10, 2022
//Project Title: Hangman

//Who did what?
//  Dante Moon: Developed the beginning main menu and generated a random word choosen from a file. 
//  Autumn Benton: Developed the single player game screen and its operations
//  Jose Diaz-Trinidad: Assisted in developing the single player game and its operations as well as final debugging. 
//  Ziaho Xu: Developed the scoreboard for single play and muti player game


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> //need to find a better way to generate random numbers



// int misses;
// char guessed;
// int corrects;
// char correct[6] = {};

struct single{
  char name[100];
  int score;
};

struct muti{
  char name[100];
  int score;
};

int single_num=0;
int muti_num=0;
struct single player[50];
struct muti playerm[50];

int game(char word[]){
  int misses = 0;
  int corrects = 0;
  char guessed;
  char guessWrong[26] = {};
  int size = 0;
  bool running = true;
  int wait = 1;
  char holder;
  
  while(word[size] >= 'a' && word[size] <= 'z'){
    size += 1;
  }
  char guessWord[size];
  char correct[size];

  
  while(running){
    system("clear"); //clears the console
    printf("For testing purposes...\t");
    for(int i = 0; i < size; i++){
      printf("%c", word[i]);
    }
    printf("\nHangman\n\n");

    if(misses == 1){
      printf("-----\n");
      printf("|   |\n");
      printf("|   O\n");
      printf("|\n");
      printf("|\n");
      printf("-----\n");
    }
    else if(misses == 2){
      printf("-----\n");
      printf("|   |\n");
      printf("|   O\n");
      printf("|   |\n");
      printf("|\n");
      printf("-------\n");
    }
    else if(misses == 3){
      printf("-----\n");
      printf("|   |\n");
      printf("|   O\n");
      printf("|   |\n");
      printf("|  /\n");
      printf("-------\n");
    }
    else if(misses == 4){
      printf("-----\n");
      printf("|   | \n");
      printf("|   O \n");
      printf("|   | \n");
      printf("|  / \\ \n");
      printf("-------\n");
    }
    else if(misses == 5){
      printf("-----\n");
      printf("|   | \n");
      printf("|  \\O \n");
      printf("|   | \n");
      printf("|  / \\ \n");
      printf("-------\n");
    }
    else if(misses == 6){
      printf("-----\n");
      printf("|   | \n");
      printf("|  \\O/ \n");
      printf("|   | \n");
      printf("|  / \\ \n");
      printf("-------\n");
    }
    else{
      printf("-----\n");
      printf("|   |\n");
      printf("|\n");
      printf("|\n");
      printf("|\n");
      printf("-----\n");
    }

    printf("\n");
    for(int i = 0; i < size; i++){  //Displays the correctly guess letters
      if(correct[i] >= 'a' && correct[i] <= 'z'){
        printf("%c ", correct[i]);
      }
      else{
        printf("  ");
      }
    }
    printf("\n");
    for(int i = 0; i < size; i++){ //prnits lines that letters will sit on
      printf("_ ");
    }

    if(misses >= 6){  //ends game is man is hanged
      running = false;
      return 0;
    }
    else if(corrects >= size){  //ends game if word is guess letter by letter
      running = false;
      return 1;
    }

    bool tF = true;
    if(wait == 1){    //guessing a letter
      printf("\nGuess a letter: ");  //promts user to guess a letter
      
      scanf("%c", &guessed); //collects the guess
  
      for(int i = 0; i < sizeof(word); i++){  //if the letter guessed is in the word then the letter is removed from the word so it can't be guessed again
        if(word[i] == guessed){
          tF = false;
          correct[i] = guessed;
          word[i] = '0';
          //break;
          // JD: Break would cause other letters that are the same to not get set to found. Ex: parallel would only set the first l to be found. 
        }
      }
    
      if(tF){     //a collection of wrong guesses placed at their alphabetical placement
        if(guessWrong[guessed-97] == guessed){
          printf("You already guessed %c. Guess again. ", guessed);
        }
        else{
          guessWrong[guessed-97] = guessed;
          misses += 1; //counter for missed letter
        }
      }
      else{
        corrects += 1;  //counter for correct letters
      }
    }
    else if(wait == 2){ //guess the whole word
      tF = true;
      printf("\nGuess the word: ");
      scanf("%s", guessWord);
      for(int i = 0; i < size; i++){
        if((word[i] != guessWord[i]) == (correct[i] != guessWord[i])){
          tF = false;
          break;
        }
      }
      if(tF){
        return 1;
      }
      else{
        printf("\nYour guess was wrong. Keep guessing letters. ");
      }
    }
    else{
      printf("Invalid selection. ");
    }
    
    printf("\n\nWrong Guesses\n");  //Displays the wrong guesses
    for(int i = 0; i < sizeof(guessWrong); i++){
      if(guessWrong[i] > 96 || guessWrong[i] < 123){
        printf("%c ", guessWrong[i]);
      }
      else{
        printf(" ");
      }
    }
    printf("\n");
    for(int i = 0; i < sizeof(guessWrong); i++){ //displays lines for all the letters of the alphabet
      printf("_ ");
    }

    printf("\nPress 1 to guess a letter or 2 to guess the word. "); //user's option to solve the word or keep guessing letters
    scanf("%d", &wait);
    scanf("%c", &holder);

  }
}


const char* pickword(){
	time_t t;
	srand((unsigned) time(&t));
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

//sort the single player scoreboard
void score_manage_1(int pos){
  for(int i=0;i<single_num;i++){
    if(player[i].score<=player[pos].score){
      char tempn[100];
      int temp = player[pos].score;
      strcpy(tempn,player[pos].name);
      for(int k=single_num-1;k>i-1;k--){
        player[k].score = player[k-1].score;
        strcpy(player[k].name,player[k-1].name);
      }
      player[i].score = temp;
      strcpy(player[i].name,tempn);
    }
  }
}

//sort the muti player scoreboard
void score_manage_2(int pos){
  for(int i=0;i<muti_num;i++){
    if(playerm[i].score<=playerm[pos].score){
      char tempn[100];
      int temp = playerm[pos].score;
      strcpy(tempn,playerm[pos].name);
      for(int k=muti_num-1;k>i-1;k--){
        playerm[k].score = playerm[k-1].score;
        strcpy(playerm[k].name,playerm[k-1].name);
      }
      playerm[i].score = temp;
      strcpy(playerm[i].name,tempn);
    }
  }
}

int main(void) {
  char s[100]; //menu input
	char n[100]; //name input
	char n2[100]; //player2 name input
  char *word;
	char word1[100];
	char word2[100];
  char holder;
  
	while(1){
		printf("hello and welcome to hangman, please enter an option from below:\n	1. Single Player\n	2. Multiplayer\n	3. Scoreboard\n	4. Exit\n");
		fgets(s, 3, stdin); //get input and store it in the array
		
    if(s[0]=='1'){ //singleplayer
			printf("please enter your name: ");
			fgets(n,100,stdin);
      bool exist = false;
      int index = 0;

      //clear the \n from user input string
      size_t length = strlen(n);
      if(n[length-1] == '\n'){
        n[length-1] = '\0';
      }

      //check is name exist in scoreboard
      if(single_num != 0){
        for(int i=0;i<single_num;i++){
          if(strcmp(player[i].name,n)==0){
            exist = true;
            break;
          }
          index++;
        }
      }

      word = pickword(); //this is the random word

      //play the game and record the grade
      if(!exist){
        strcpy(player[single_num].name, n);
        player[single_num].score = 0;
        if(game(word) == 1){
          player[single_num].score++;
        }
        single_num++;
      }else{
        if(game(word) == 1){
          player[index].score++;
        }
      }

      score_manage_1(index);
      
      system("clear");
		}
		if(s[0]=='2'){ //multiplayer
      system("clear"); //clears the console

			printf("PLAYER 1 please enter your name: ");
      scanf("%s", n);
      printf("\nPLAYER 1 please enter a word for player 2 to guess: ");
      scanf("%s", word1);
      
      system("clear"); //clears the console

			printf("PLAYER 2 please enter your name: ");
      scanf("%s", n2);
			printf("\nPLAYER 2 please enter a word for player 1 to guess: ");
      scanf("%s", word2);

      system("clear"); //clears the console

      printf("%s is up first...", n);
      printf("\n\nPress enter to begin. ");
      scanf("%c", &holder);
      scanf("%c", &holder);

      int p1 = game(word2); //returns 1 if p1 wins, or 0 if they loose

      system("clear"); //clears the console 

      printf("%s is up next...", n2); 
      printf("\n\nPress enter to begin. ");
      scanf("%c", &holder);
      scanf("%c", &holder);
      
      int p2 = game(word1); //returns 1 if p2 wins, or 0 if they loose

      //record the score for muti-player game
      bool exist = false;
      int index = 0;

      //when p1 wins
      if(p1==1){
        size_t length = strlen(n);
        if(n[length-1] == '\n'){
           n[length-1] = '\0';
        }
        if(muti_num != 0){
          for(int i=0;i<muti_num;i++){
            if(strcmp(playerm[i].name,n)==0){
              exist = true;
              break;
            }
            index++;
          }
        }
        if(!exist){
          strcpy(playerm[muti_num].name, n);
          playerm[muti_num].score = 0;
          playerm[muti_num].score++;
          muti_num++;
        }else{
          playerm[index].score++;
        }
      }

      //when p2 wins
      if(p2==1){
        size_t length = strlen(n2);
        if(n2[length-1] == '\n'){
           n2[length-1] = '\0';
        }
        if(muti_num != 0){
          for(int i=0;i<muti_num;i++){
            if(strcmp(playerm[i].name,n2)==0){
              exist = true;
              break;
            }
            index++;
          }
        }
        if(!exist){
          strcpy(playerm[muti_num].name, n2);
          playerm[muti_num].score = 0;
          playerm[muti_num].score++;
          muti_num++;
        }else{
          playerm[index].score++;
        }
      }

      score_manage_2(index);
      
		}
		if(s[0]=='3'){ //scoreboard
      system("clear");

      int rtr =0;
      
      printf("\nScoreboard:\n\n");
      printf("Single player: \n");

      for(int i=0;i<single_num;i++){
        printf("%d.%s......%d\n", i+1, player[i].name, player[i].score);

        if(i==2)break;
      }

      printf("\nMutiple player: \n");
      for(int i=0;i<muti_num;i++){
        printf("%d.%s......%d\n", i+1, playerm[i].name, playerm[i].score);

        if(i==2)break;
      }
      
      printf("\nPress 1 to return: ");
      scanf("%d", &rtr);
      if(rtr == 1){
        system("clear");
      }
		}
		if(s[0]=='4'){ //exit
			break;
		}
  }

  
  
  return 0;
}

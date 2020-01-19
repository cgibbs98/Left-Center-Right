//Included libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Ifdef loads respective OS specifc libraries for sleep() function based on OS used with application
#ifdef _WIN32
	#include <Windows.h>
#else
	#include <unistd.h>
#endif

//Constants for default player and chip counts
#define DEFAULTPLAYERS 5
#define DEFAULTCHIPS 3
#define BORDER "----------------------------"
#define MAXPLAYERSIZE 25

//Struct for player which included their name and chip count
struct Player{
	char name[MAXPLAYERSIZE];
	int chips;
};

//Function Definitions
void changeCounts(int *p, int *c, int sel);
void viewInstructions();
int min(int a, int b);
int randomInt(int min, int max);
void pauseGame(double sec);
void playGame(int playercount, int chipcount);

//Main function
int main(){

	//Set default player and chip counts upon startup
	int playercount = DEFAULTPLAYERS;
	int chipcount = DEFAULTCHIPS;
	printf("\nWelcome to Left Center Right!\n");

	//Menu for game along with current settings
	int choice = 0;
	while(choice != 6){
	
		//Menu text
		printf("\nPlayer Count: %d \t Chip Count: %d", playercount, chipcount);
		printf("\nSelect a Choice Below:\n");
		printf("\n%s", BORDER);
		printf("\n1. Play with Above Settings");
		printf("\n2. Play with Random Settings");
		printf("\n3. View Instructions");
		printf("\n4. Change Settings");
		printf("\n5. Reset to Default Settings");
		printf("\n6. Quit");
		printf("\n%s", BORDER);
	
		//Menu choice input
		printf("\n");
		scanf("%d", &choice);
	
		//Evaulate menu choice
		switch(choice){
			//Play Game with current settings for player and chip counts	
			case 1:
				playGame(playercount, chipcount);
				break;
			//Play game with randomly generated player and chip counts	
			case 2:
				changeCounts(&playercount, &chipcount, 1);
				playGame(playercount, chipcount);
				break;
			//View game instructions	
			case 3:
				viewInstructions();
				break;
			//Change player and chip counts
			case 4:
				changeCounts(&playercount, &chipcount, 2);
				break;
			//Reset default player and chip counts	
			case 5:
				changeCounts(&playercount, &chipcount, 3);
				break;
			//Quit game	
			case 6:
				printf("\nGoodbye\n");
				break;
			//Invalid option
			default:
				printf("\nInvalid Choice\n");
		}//End of switch	
	
	}//End of while
	
//Terminate Program
printf("\n");
return 0;

}//End of main	










//Change player and chip counts for a variety of purposes
void changeCounts(int *p, int *c, int sel){
	
	//If function will use a random number based on current system time and min and max ranges
	if(sel == 1){
		*p = randomInt(3, 9);
		*c = randomInt(1, 9);
	}//End of if	
	
	//Else if function will prompt user for counts
	else if(sel == 2){
		
		//Set temporary variables in case user enters value beloe minimal count
		int tp = *p;
		int tc = *c;
		printf("\n");
		
		//Prompts user for player count and returns back to pre function call counts if below the minimal count needed
		printf("How many players will play? (Atleast 3 players are required)\n");
		scanf("%d", &*p);
		if(*p < 3){
			*p = tp;
			printf("\nAtleast 3 players are required. Returning to main menu\n");
			return;
		}//End of if
		
		//Prompts user for player count and returns back to pre function call counts if below the minimal count needed
		printf("How many chips will each player have? (Atleast 1 chip per player is required)\n");
		scanf("%d", &*c);
		if(*c < 1){
			*p = tp;
			*c = tc;
			printf("\nAtleast 1 chip per player is required. Returning to main menu\n");
			return;
		}//End of if
		printf("\nSuccessfully Changed Player and Chip Counts\n");
		
	}//End of else if
	
	//Else if function will set default counts based on declared constants
	else{
		*p = DEFAULTPLAYERS;
		*c = DEFAULTCHIPS;
		printf("\nReset Player and Chip Counts to Default Settings\n");
	}//End of else
	return;
	
}//End of changeCounts	

//View game instructions
void viewInstructions(){
	
	//Prints game instructions to user and prompts user to enter to go back
	printf("\nLeft Center Right is a game where your goal is to win an entire pool of chips");
	printf("\nEach player take turns rolling 1 dice per chip up to the starting chip count where a 50%% chance of a * will occur and another 50%% for either a L, C, or R will occur");
	printf("\n* means you don't lose any chips, C means a chip goes into the center chip pool, L and R means a chip is given to the player to the left and right of you respectively (Previous and Next player)");
	printf("\nIf a player has less chips than the starting chip count, the player only rolls 1 dice per chips remaining that turn");
	printf("\nA player without any chips will lose their turn, but can come back their next turn if given a chip through a L or R");
	printf("\nIf only 1 player has any number of chips, the game is over and that player wins the chip pool along with their current chips");
	printf("\n");
	
}//End of viewInstructions










//Minimum function for dice count
int min(int a, int b){
	
	//If current player's chips < initial chipcount, return current player's chips; Otherwise return initial chipcount
	if(a < b){
		return a;
	}//End of if
	return b;
	
}//End of min

//Random int function for various actions involving a random number
int randomInt(int min, int max){
	
	//Uses system time seed from playGame() to determine a random number within range of min and max
	int r = rand() % (min - (max + 1)) + min;
	return r;
	
}//End of randomInt

//Pause function for pausing execution to allow user to keep track of the game
void pauseGame(double sec){

	//Ifdef calls respective sleep function defined by OS
	fflush(stdout);
	#ifdef _WIN32
		Sleep((int)(sec*1000));
	#else
		usleep((int)(sec*1000000));
	#endif

}//End of pauseGame









//Play game
void playGame(int playercount, int chipcount){
	
	//Sets current system time as the random seed for the game
	srand(time(0));
	
	//Create players by dynamically creating array and filling out pregame counts
	struct Player* turns = calloc(playercount, sizeof(struct Player));
	int i = 0;
	char num[3];
	char plabel[] = "Player ";
	
	//Iterates array of Players to fill out pregame info
	for(i = 0; i < playercount; i++){
		sprintf(num, "%d", (i+1));
		strcpy(strcat(turns[i].name, num), strcat(turns[i].name, plabel));
		turns[i].chips = chipcount;
	}//End of for
	
	//Pregame loop variable delcarations
	int check = 1;
	int chippool = 0;
	int maxpool = playercount*chipcount;
	int turncount = 1;
	i = 0;
	int j = 0;
	int dicecount = 0;
	int hassome = 0;
	int winner = 0;
	
	//Game runs until only one person has chips left
	while(check == 1){
		
		//Print current game info and player with a small pause
		printf("\nTurn: %d",turncount);
		printf("\nCenter Chip Pool: %d/%d",chippool, maxpool);
		printf("\nCurrent Player: %s \t Current Chip Count: %d", turns[(i%playercount)].name, turns[(i%playercount)].chips);
		pauseGame(3);
		
		//Skips player since they don't have any chips remaining with a small pause
		if(turns[(i%playercount)].chips == 0){
			printf("\nTurn Skipped");
			pauseGame(1.5);
		}//End of if
		
		//Allows current player to roll respective number of dice where results are stored in dynamic array with a small pause
		else{
			
			//Preroll loop variable delcarations
			dicecount = min(turns[(i%playercount)].chips, chipcount);
			int* rolls = calloc(dicecount, sizeof(int));
			printf("\nRolls: ");
			
			//Loop for each dice roll, then displays result to user
			for(j = 0; j < dicecount; j++){
				
				//Dice roll occurs
				rolls[j] = randomInt(1, 6);
				
				//Prints respective result to user
				if(rolls[j] == 4){
					printf("%c", 'L');
				}//End of if
				else if(rolls[j] == 5){
					printf("%c", 'C');
				}//End of else if	
				else if(rolls[j] == 6){
					printf("%c", 'R');
				}//End of else if	
				else{
					printf("%c", '*');
				}//End of else	
			
			}//End of for
			pauseGame(1.5);
			
			//Performs respective LCR Actions
			for(j = 0; j < dicecount; j++){
				
				//L gives a chip to previous player
				if(rolls[j] == 4){
					turns[(((i+playercount)-1) % playercount)].chips++;
					turns[(i % playercount)].chips--;
				}//End of if
				
				//C sends chip into center chip pool
				else if(rolls[j] == 5){
					chippool++;
					turns[(i % playercount)].chips--;
				}//End of else if	
				
				//R gives a chip to next player
				else if(rolls[j] == 6){
					turns[(((i+playercount)+1) % playercount)].chips++;
					turns[(i % playercount)].chips--;
				}//End of else if	
			
			}//End of for
			
			//Frees memory from dynamic array once all rolls have occured
			free(rolls);
			
			//Checks if only one remaining player has chips left and determines the next player as the winner if true
			hassome = 0;
			winner = 0;
			for(j = 0; j < playercount; j++){
				
				//Checks player's chip count and record if they do
				if(turns[j].chips > 0){
					winner = j;
					hassome++;
				}//End of if	
				
				//Stops checking if more than one player has chips remaining
				if(hassome > 1){
					break;
				}//End of if	
				
			}//End of for
			
			//Ends game if only 1 player has chips reamining and calls that person the winner
			if(hassome == 1){
				break;
			}//End of if	
			
		}//End of else
		
		//Increment counter to next player and turn if going back to first player
		turncount = ((i+1)/playercount)+1;
		printf("\n");
		i++;
	}//End of while
	
	//Tells console the winner and frees memory from dynamic array once game ends
	printf("\n\n%s wins the game for %d chips in center pool with %d chips remaining!", turns[((winner)%playercount)].name, chippool, turns[((winner)%playercount)].chips);
	printf("\n");
	free(turns);
	
}//End of playGame
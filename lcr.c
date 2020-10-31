//Included libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

//Included headers
#include "file.h"
#include "player.h"
#include "utilities.h"

//Constants for fixed values that will never be changed
#define BORDER "--------------------------------"
#define MAXDIGITS 12
const int FIXEDWIDTHS[] = {2, 18, 15, 14, 12, 13, 13, 16};

//Global variables that will be changed throughout including struct for each player in the simulation
int playercount;
int chipcount;
int pauseenabled;
double longpause;
double shortpause;
int minplayerrand;
int maxplayerrand;
int minchiprand;
int maxchiprand;
int maxwidths[STATCOUNT];
int smallname;
Player* turns;

//Function Definitions
void settingsMenu();
void runSim();
void endGameMenu(Player* turns);
void printStatistics(Player* turns);

//Main function
int main(){

	//Load configuration for all default variables
	loadDefaults(&playercount, &chipcount, &pauseenabled, &longpause, &shortpause, &minplayerrand, &maxplayerrand, &minchiprand, &maxchiprand);
	printf("\n\nWelcome to the Left Center Right Simulator!\n");

	//Menu for game along with current settings
	int choice = 0;
	while(choice != 4){

		//Menu text
		printf("\nPlayer Count: %d \t Chip Count: %d", playercount, chipcount);
		printf("\nSelect a Choice Below:\n");
		printf("\n%s", BORDER);
		printf("\n1. Run Simulation");
		printf("\n2. View Instructions");
		printf("\n3. Change Settings");
		printf("\n4. Quit");
		printf("\n%s", BORDER);

		//Menu choice input
		printf("\n");
		scanf("%d", &choice);

		//Evaluate menu choice
		switch(choice){
			//Play Game with current settings for player and chip counts
			case 1:
				runSim();
				break;
			//View game instructions
			case 2:
				viewInstructions();
				break;
			//Change settings and counts
			case 3:
				settingsMenu();
				break;
			//Quit game
			case 4:
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

//Settings menu for changing count and other features
void settingsMenu(){
	
	//Menu for game along with current settings
	int choice = 0;
	while(choice != 6){

		//Menu text
		printf("\nPlayer Count: %d \t Chip Count: %d", playercount, chipcount);
		printf("\nSelect a Choice Below:\n");
		printf("\n%s", BORDER);
		printf("\n1. Set Random Counts");
		printf("\n2. Define Counts");
		printf("\n3. Reset to Default Counts");
		if(pauseenabled == 1){
			printf("\n4. Disable Simulation Pausing");
		}//End of if
		else{
			printf("\n4. Enable Simulation Pausing");
		}//End of else
		printf("\n5. Configure Startup Parameters");
		printf("\n6. Return to Main Menu");
		printf("\n%s", BORDER);

		//Menu choice input
		printf("\n");
		scanf("%d", &choice);

		//Evaluate menu choice
		switch(choice){
			//Randomly generate player and chip counts
			case 1:
				changeCounts(1, &playercount, &chipcount, minplayerrand, maxplayerrand, minchiprand, maxchiprand);
				break;
			//Let user hange player and chip counts
			case 2:
				changeCounts(2, &playercount, &chipcount, minplayerrand, maxplayerrand, minchiprand, maxchiprand);
				break;
			//Reset to default player and chip counts
			case 3:
				changeCounts(3, &playercount, &chipcount, minplayerrand, maxplayerrand, minchiprand, maxchiprand);
				break;
			//Enable or Disable Puasing in Simulation Mode
			case 4:
				pauseenabled = (pauseenabled + 1) % 2;
				break;
			//Run configuration mode to change startup and ingame values
			case 5:
				configureStartup();
				break;
			//Return to main menu
			case 6:
				break;
			//Invalid option
			default:
				printf("\nInvalid Choice\n");
		}//End of switch

	}//End of while
	
}//End of settingsMenu










//Run Simulation
void runSim(){

	//Sets current system time as the random seed for the game and resets array used for tracking widths, name sizes, and averages for statistics
	smallname = 8;
	resetArray(maxwidths, STATCOUNT);
	srand(time(0));

	//Create players by dynamically creating array and filling out pregame counts
	turns = calloc(playercount, sizeof(Player));
	int i = 0;
	int j = 0;
	char num[MAXDIGITS];
	char plabel[] = "Player ";

	//Iterates array of Players to fill out pregame info
	for(i = 0; i < playercount; i++){
		
		//Populate game information
		sprintf(num, "%d", (i+1));
		strcpy(strcat(turns[i].name, num), strcat(turns[i].name, plabel));
		smallname = min(smallname, strlen(turns[i].name));
		turns[i].chips = chipcount;
		
		//Populate stats array
		for(j = 0; j < STATCOUNT; j++){
			turns[i].stats[j] = 0;
		}//End of for
		
	}//End of for

	//Pregame loop variable declarations
	int check = 1;
	int chippool = 0;
	int maxpool = playercount*chipcount;
	int turncount = 1;
	i = 0;
	j = 0;
	int dicecount = 0;
	int hassome = 0;
	int winner = 0;
	char numcheck[MAXDIGITS];

	//Game runs until only one person has chips left
	while(check == 1){

		//Print current game info and player with a small pause
		printf("\nTurn: %d",turncount);
		printf("\nCenter Chip Pool: %d/%d",chippool, maxpool);
		printf("\nCurrent Player: %s \t Current Chip Count: %d", turns[(i%playercount)].name, turns[(i%playercount)].chips);
		pauseSim(longpause, pauseenabled);

		//Skips player since they don't have any chips remaining with a small pause
		if(turns[(i%playercount)].chips == 0){
			turns[(i % playercount)].stats[6]++;
			sprintf(numcheck, "%d", turns[(i % playercount)].stats[6]);
			maxwidths[6] = max(maxwidths[6], strlen(numcheck));
			printf("\nTurn Skipped");
			pauseSim(longpause, pauseenabled);
		}//End of if

		//Allows current player to roll respective number of dice where results are stored in dynamic array with a small pause
		else{

			//Preroll loop variable delcarations
			turns[(i % playercount)].stats[5]++;
			sprintf(numcheck, "%d", turns[(i % playercount)].stats[5]);
			maxwidths[5] = max(maxwidths[5], strlen(numcheck));
			dicecount = min(turns[(i%playercount)].chips, chipcount);
			int* rolls = calloc(dicecount, sizeof(int));
			printf("\nRolls: ");

			//Loop for each dice roll, then displays result to user
			turns[(i % playercount)].stats[4] += dicecount;
			sprintf(numcheck, "%d", turns[(i % playercount)].stats[4]);
			maxwidths[4] = max(maxwidths[4], strlen(numcheck));
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
			pauseSim(shortpause, pauseenabled);

			//Performs respective LCR Actions with a small pause
			for(j = 0; j < dicecount; j++){

				//L gives a chip to previous player
				if(rolls[j] == 4){
					turns[(((i+playercount)-1) % playercount)].chips++;
					turns[(i % playercount)].chips--;
					turns[(i % playercount)].stats[0]++;
					sprintf(numcheck, "%d", turns[(i % playercount)].stats[0]);
					maxwidths[0] = max(maxwidths[0], strlen(numcheck));
					printf("\nOne chip given to %s", turns[(((i+playercount)-1) % playercount)].name);
				}//End of if

				//C sends chip into center chip pool
				else if(rolls[j] == 5){
					chippool++;
					turns[(i % playercount)].chips--;
					turns[(i % playercount)].stats[1]++;
					sprintf(numcheck, "%d", turns[(i % playercount)].stats[1]);
					maxwidths[1] = max(maxwidths[1], strlen(numcheck));
					printf("\nOne chip moved to center pool");
				}//End of else if

				//R gives a chip to next player
				else if(rolls[j] == 6){
					turns[(((i+playercount)+1) % playercount)].chips++;
					turns[(i % playercount)].chips--;
					turns[(i % playercount)].stats[2]++;
					sprintf(numcheck, "%d", turns[(i % playercount)].stats[2]);
					maxwidths[2] = max(maxwidths[2], strlen(numcheck));
					printf("\nOne chip given to %s", turns[(((i+playercount)+1) % playercount)].name);
				}//End of else if

				//* Does nothing
				else{
					turns[(i % playercount)].stats[3]++;
					sprintf(numcheck, "%d", turns[(i % playercount)].stats[3]);
					maxwidths[3] = max(maxwidths[3], strlen(numcheck));
				}//End of else

			}//End of for
			pauseSim(longpause, pauseenabled);

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

			//Ends game if only 1 player has chips remaining and calls that person the winner
			if(hassome == 1){
				break;
			}//End of if

		}//End of else

		//Increment counter to next player and turn if going back to first player
		turncount = ((i+1)/playercount)+1;
		printf("\n");
		i++;
	}//End of while

	//Tells console the winner and send array to player menu where it can be freed from there for the next game
	printf("\n\n%s wins the game for %d chips in center pool with %d chips remaining!", turns[((winner)%playercount)].name, chippool, turns[((winner)%playercount)].chips);
	printf("\n");
	endGameMenu(turns);
	
}//End of playGame










//Menu that is disp[layed once the game ends
void endGameMenu(Player* turns){
	
	//Menu for game along with current settings
	int choice = 0;
	while( (choice != 1) && (choice != 3) ){

		//Menu text
		printf("\nSelect a Choice Below:\n");
		printf("\n%s", BORDER);
		printf("\n1. Run Simulation Again");
		printf("\n2. View Statistics");
		printf("\n3. Return to Main Menu");
		printf("\n%s", BORDER);

		//Menu choice input
		printf("\n");
		scanf("%d", &choice);

		//Shows user statistics for the game
		if(choice == 2){
			printStatistics(turns);
		}//End of if
		//If user makes invalid choice
		else if((choice < 1) || (choice > 3)){
			printf("\nInvalid Choice\n");
		}//End of else if

	}//End of while
	
	//Frees memory from dynamic array since it isn't needed anymore
	free(turns);
	
	//If user chooses to play again
	if(choice == 1){
		runSim();
	}//End of if
	
}//End of endGameMenu

//Function that prints statistics for the last game
void printStatistics(Player* turns){
	
	//Prints each player's stats with one row for each player and the average at the bottom
	int i = 0;
	int j = 0;
	int width = 0;
	char statprint[MAXDIGITS];
	printf("\n| Player's Name | Left Count | Center Count | Right Count | Dot Count | Dice Rolls | Good Turns | Skipped Turns |\n\n");
	for(i = 0; i < (playercount+3); i++){
		
		//Calculates and prints averages of each stat to the screen
		if(i == playercount){
			
			//Prints average label
			printf("\n%*s", (int)(FIXEDWIDTHS[0] + 8), "Average:");
			
			//Calculates and prints each average to the screen
			for(j = 0; j < STATCOUNT; j++){
				
				//Converts stat to string and calculates spacing needed on screen
				sprintf(statprint, "%.*f", maxwidths[j], average(turns, j, playercount));
				width = FIXEDWIDTHS[(j+1)];
				
				//Prints a rounded version of the average to the user and frees dynamic array of values
				printf("%*s", (int)width, statprint);
			}//End of for
			
		}//End of if
		
		//Calculates and prints median of each stat to the screen
		else if(i == playercount+1){
			
			//Prints median label
			printf("\n%*s", (int)(FIXEDWIDTHS[0] + 8), "Median:");
			
			//Calculates and prints each median to the screen
			for(j = 0; j < STATCOUNT; j++){
				
				//Converts stat to string and calculates spacing needed on screen
				sprintf(statprint, "%.*f", maxwidths[j], median(turns, j, playercount));
				width = FIXEDWIDTHS[(j+1)];
				
				//Prints a rounded version of the median to the user and frees dynamic array of values
				printf("%*s", (int)width, statprint);
			}//End of for
			
		}//End of else if
		
		//Calculates and prints range of each stat to the screen
		else if(i == playercount+2){
			
			//Prints range label
			printf("\n%*s", (int)(FIXEDWIDTHS[0] + 8), "Range:");
			
			//Calculates and prints each range to the screen
			for(j = 0; j < STATCOUNT; j++){
				
				//Converts stat to string and calculates spacing needed on screen
				sprintf(statprint, "%.*f", maxwidths[j], range(turns, j, playercount));
				width = FIXEDWIDTHS[(j+1)];
				
				//Prints a rounded version of the range to the user and frees dynamic array of values
				printf("%*s", (int)width, statprint);
			}//End of for
			
		}//End of else if
		
		//Prints each player's statistics if any players left
		else{
			
			//Print's player name
			printf("%*s", (int)(FIXEDWIDTHS[0] + strlen(turns[i].name)), turns[i].name);
			
			//Prints each player's individual statistics
			for(j = 0; j < STATCOUNT; j++){
				
				//Converts stat to string and calculates spacing needed on screen
				sprintf(statprint, "%d", turns[i].stats[j]);
				width = FIXEDWIDTHS[(j+1)];
				
				//Subtracts smallest name length to accomdate spacing for 1st stat
				if(j == 0){
					width -= (strlen(turns[i].name) - smallname);
				}//End of if
				
				//Prints stat to screen
				printf("%*s", (int)width, statprint);
			
			}//End of for
			printf("\n");
			
		}//End of else
		
	}//End of for
	printf("\n");
	
}//End of printStatistics
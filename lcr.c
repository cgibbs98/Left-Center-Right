//Included libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

//Constants for fixed values that will never be changed
#define STATCOUNT 7
#define BORDER "-------------------------------"
#define MAXPLAYERSIZE 26
#define MAXDIGITS 12
#define MAXFILELOAD 128
const int FIXEDWIDTHS[] = {2, 18, 15, 14, 12, 13, 13, 16};

//Global variables that will be changed throughout
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

//Struct for player which included their name and chip count
struct Player{
	//Game Values
	char name[MAXPLAYERSIZE];
	int chips;
	//Stats Values Array
	int stats[STATCOUNT];
	//stats[0] = leftcount,
	//stats[1] = centercount,
	//stats[2] = rightcount,
	//stats[3] = dotcount,
	//stats[4] = rollcount,
	//stats[5] = turncount,
	//stats[6] = skipcount;
};

//Function Definitions
void loadDefaults();
void setDefinedDefaults();
void settingsMenu();
void changeCounts(int sel);
void configureStartup();
void viewInstructions();
int min(int a, int b);
int max(int a, int b);
double average(struct Player* turns, int index);
int randomInt(int min, int max);
void pauseGame(double sec);
void resetArray();
void playGame();
void endGameMenu(struct Player* turns);
void printStatistics(struct Player* turns);

//Main function
int main(){

	//Load configuration for all default variables
	loadDefaults();
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
				playGame();
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










//Function that loads defulats for pause enabled, player + chip counts, rand ranges, and pause lengths
void loadDefaults(){
	
	//Loads file and calls function to set defined defaults and return to main function if file doesn't load
	printf("\nLoading game paramters");
	FILE *fp;
	if(fp = fopen("config.txt", "r")){
		//Gathers every variable needed
		char fbuffer[MAXFILELOAD];
		fgets(fbuffer, MAXFILELOAD, (FILE*)fp);
		char* token1 = strtok(fbuffer, " ");
		token1 = strtok(NULL, " = ");
		playercount = atoi(token1);
		
		fgets(fbuffer, MAXFILELOAD, (FILE*)fp);
		char* token2 = strtok(fbuffer, " ");
		token2 = strtok(NULL, " = ");
		chipcount = atoi(token2);
		
		fgets(fbuffer, MAXFILELOAD, (FILE*)fp);
		char* token3 = strtok(fbuffer, " ");
		token3 = strtok(NULL, " = ");
		pauseenabled = atoi(token3);
		
		fgets(fbuffer, MAXFILELOAD, (FILE*)fp);
		char* token4 = strtok(fbuffer, " ");
		token4 = strtok(NULL, " = ");
		minplayerrand = atoi(token4);
		
		fgets(fbuffer, MAXFILELOAD, (FILE*)fp);
		char* token5 = strtok(fbuffer, " ");
		token5 = strtok(NULL, " = ");
		maxplayerrand = atoi(token5);
		
		fgets(fbuffer, MAXFILELOAD, (FILE*)fp);
		char* token6 = strtok(fbuffer, " ");
		token6 = strtok(NULL, " = ");
		minchiprand = atoi(token6);
		
		fgets(fbuffer, MAXFILELOAD, (FILE*)fp);
		char* token7 = strtok(fbuffer, " ");
		token7 = strtok(NULL, " = ");
		maxchiprand = atoi(token7);
		
		fgets(fbuffer, MAXFILELOAD, (FILE*)fp);
		char* token8 = strtok(fbuffer, " ");
		token8 = strtok(NULL, " = ");
		longpause = atof(token8);
		
		fgets(fbuffer, MAXFILELOAD, (FILE*)fp);
		char* token9 = strtok(fbuffer, " ");
		token9 = strtok(NULL, " = ");
		shortpause = atof(token9);
		
		//Closes file once done loading every value
		fclose(fp);
	}
	else{
		setDefinedDefaults();
		return;
	}
	
}//End of loadDefaults

//Function that loads defined defaults if file is non-existant
void setDefinedDefaults(){
	
	//Manually sets defined values to pre defined values and creates new file
	printf("\nCould not find configuration file; Setting program defined defaults and creating new configuration file instead.");
	FILE *fp = fopen("config.txt", "w+"); 
	playercount = 5;
	fprintf(fp, "PLAYERCOUNT = %d\n", playercount);
	chipcount = 3;
	fprintf(fp, "CHIPCOUNT = %d\n", chipcount);
	pauseenabled = 0;
	fprintf(fp, "PAUSEENABLED = %d\n", pauseenabled);
	minplayerrand = 3;
	fprintf(fp, "MINPLAYERRAND = %d\n", minplayerrand);
	maxplayerrand = 9;
	fprintf(fp, "MAXPLAYERRAND = %d\n", maxplayerrand);
	minchiprand = 1;
	fprintf(fp, "MINCHIPRAND = %d\n", minchiprand);
	maxchiprand = 9;
	fprintf(fp, "MAXCHIPRAND = %d\n", maxchiprand);
	longpause = 3.0;
	fprintf(fp, "LONGPAUSE = %f\n", longpause);
	shortpause = 1.5;
	fprintf(fp, "SHORTPAUSE = %f", shortpause);
	fclose(fp);
	
}//End of setDefinedDefaults










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
				changeCounts(1);
				break;
			//Let user hange player and chip counts
			case 2:
				changeCounts(2);
				break;
			//Reset to default player and chip counts
			case 3:
				changeCounts(3);
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

//Change player and chip counts for a variety of purposes
void changeCounts(int sel){

	//If function will use a random number based on current system time and min and max ranges
	if(sel == 1){
		//Sets current system time as the random seed for random player and chip counts
		srand(time(0));
		playercount = randomInt(minplayerrand, maxplayerrand);
		chipcount = randomInt(minchiprand, maxchiprand);
	}//End of if

	//Else if function will prompt user for counts
	else if(sel == 2){

		//Set temporary variables in case user enters value beloe minimal count
		int tp = playercount;
		int tc = chipcount;
		printf("\n");

		//Prompts user for player count and returns back to pre function call counts if below the minimal count needed
		printf("How many players will play? (Atleast 3 players are required)\n");
		scanf("%d", &playercount);
		if(playercount < 3){
			playercount = tp;
			printf("\nAtleast 3 players are required. Returning to settings menu\n");
			return;
		}//End of if
		else{
			printf("Successfully changed player count\n");
		}//End of else

		//Prompts user for player count and returns back to pre function call counts if below the minimal count needed
		printf("How many chips will each player have? (Atleast 1 chip per player is required)\n");
		scanf("%d", &chipcount);
		if(chipcount < 1){
			chipcount = tc;
			printf("\nAtleast 1 chip per player is required. Returning to settings menu\n");
			return;
		}//End of if
		else{
			printf("Successfully changed chip count\n");
		}//End of else
		printf("\n");

	}//End of else if
	
	//Else function resets to default counts
	else{
		playercount = 5;
		chipcount = 3;
	}//End of else
	return;

}//End of changeCounts

//Change startup paramters/values for config.txt file
void configureStartup(){

	//Prompts the user for each input
	int p1 = 0;
	printf("\n1. Set Player Count (Atleast 3 players are required)");
	printf("\n");
	scanf("%d", &p1);
	if(p1 < 3){
		printf("\nAtleast 3 players are required. Returning to settings menu\n");
		return;
	}//End of if
	int p2 = 0;
	printf("\n2. Set Chip Count (Atleast 1 chip per player is required)");
	printf("\n");
	scanf("%d", &p2);
	if(p2 < 1){
		printf("\nAtleast 1 chip per player is required. Returning to settings menu\n");
		return;
	}//End of if
	int p3 = 0;
	printf("\n3. Set Whether Simulation Pausing will be Enabled or Not (Must be 1 for Enabled, 0 for Disabled)");
	printf("\n");
	scanf("%d", &p3);
	if((p3 < 0) || (p3 > 1)){
		printf("\nMust be 1 for Enabled, 0 for Disabled. Returning to settings menu\n");
		return;
	}//End of if
	int p4 = 0;
	printf("\n4. Set Minimum Value Generated from Random Player Count Function (Atleast 3 players are required)");
	printf("\n");
	scanf("%d", &p4);
	if(p4 < 3){
		printf("\nAtleast 3 players are required. Returning to settings menu\n");
		return;
	}//End of if
	int p5 = 0;
	printf("\n5. Set Maximum Value Generated from Random Player Count Function (Atleast 3 players are required and > minimum value)");
	printf("\n");
	scanf("%d", &p5);
	if(p5 < 3){
		printf("\nAtleast 3 players are required. Returning to settings menu\n");
		return;
	}//End of if
	if(p5 <= p4){
		printf("\nValue must be > minimum value. Returning to settings menu\n");
		return;
	}//End of if
	int p6 = 0;
	printf("\n6. Set Minimum Value Generated from Random Chip Count Function (Atleast 1 chip per player is required)");
	printf("\n");
	scanf("%d", &p6);
	if(p6 < 1){
		printf("\nAtleast 1 chip per player is required. Returning to settings menu\n");
		return;
	}//End of if
	int p7 = 0;
	printf("\n7. Set Maximum Value Generated from Random Chip Count Function (Atleast 1 chip per player is required and > minimum value)");
	printf("\n");
	scanf("%d", &p7);
	if(p7 < 1){
		printf("\nAtleast 1 chip per player is required. Returning to settings menu\n");
		return;
	}//End of if
	if(p7 <= p6){
		printf("\nValue must be > minimum value. Returning to settings menu\n");
		return;
	}//End of if
	double p8 = 0;
	printf("\n8. Set Value for Amount of Seconds for Long Pauses (Must be > 0.0 seconds)");
	printf("\n");
	scanf("%lf", &p8);
	if(p8 < 0.0){
		printf("\nValue must be > 0.0 seconds. Returning to settings menu\n");
		return;
	}//End of if
	double p9 = 0;
	printf("\n9. Set Value for Amount of Seconds for Short Pauses (Must be > 0.0 seconds and < long pause value)");
	printf("\n");
	scanf("%lf", &p9);
	if(p9 < 0.0){
		printf("\nValue must be > 0.0 seconds. Returning to settings menu\n");
		return;
	}//End of if
	if(p9 >= p8){
		printf("\nValue must be < long pause value. Returning to settings menu\n");
		return;
	}//End of if

	//Saves new values in config.txt file
	printf("\nSaving changes to config.txt file\n");
	printf("Successfully saved changes. (Changes take effect next time program is executed)\n");
	FILE *fp = fopen("config.txt", "w+");
	fprintf(fp, "PLAYERCOUNT = %d\n", p1);
	fprintf(fp, "CHIPCOUNT = %d\n", p2);
	fprintf(fp, "PAUSEENABLED = %d\n", p3);
	fprintf(fp, "MINPLAYERRAND = %d\n", p4);
	fprintf(fp, "MAXPLAYERRAND = %d\n", p5);
	fprintf(fp, "MINCHIPRAND = %d\n", p6);
	fprintf(fp, "MAXCHIPRAND = %d\n", p7);
	fprintf(fp, "LONGPAUSE = %lf\n", p8);
	fprintf(fp, "SHORTPAUSE = %lf", p9);
	fclose(fp);

}//End of configureStartup

//View game instructions
void viewInstructions(){

	//Prints game instructions to user and prompts user to enter to go back
	printf("\nLeft Center Right is a game where your goal is to win an entire pool of chips which this program will simulate");
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

//Maximum function for highest count and name length
int max(int a, int b){

	//If count's string length > highest string length, return new highest count or name length; Otherwise keep current count or name length
	if(a > b){
		return a;
	}//End of if
	return b;

}//End of max

//Average function to calculate average of stats
double average(struct Player* turns, int index){
	
	//Uses a loop to calculate average and divides it by size before returning it to the user
	double avg = 0;
	int i = 0;
	for(i = 0; i < playercount; i++){
		avg += turns[i].stats[index];
	}//End of for
	avg /= (double)playercount;
	return avg;
	
}//End of average

//Random int function for various actions involving a random number
int randomInt(int min, int max){

	//Uses system time seed from playGame() to determine a random number within range of min and max
	int r = rand() % (min - (max + 1)) + min;
	return r;

}//End of randomInt

//Pause function for pausing execution to allow user to keep track of the game
void pauseGame(double sec){

	//If pausing is enabled usleep function is called after printing string form before the function call
	if(pauseenabled == 1){
		fflush(stdout);
		usleep((int)(sec*1000000));
	}//End of if

}//End of pauseGame

//Function to reset statsics array widths amd averages to 0
void resetArray(){
	
	//Loops thorugh each element of the array and resets it to 0
	int i = 0;
	for(i = 0; i < STATCOUNT; i++){
		maxwidths[i] = 0;
	}//End of for
	
}//End of resetArray









//Play game
void playGame(){

	//Sets current system time as the random seed for the game and resets array used for tracking widths, name sizes, and averages for statistics
	smallname = 8;
	resetArray();
	srand(time(0));

	//Create players by dynamically creating array and filling out pregame counts
	struct Player* turns = calloc(playercount, sizeof(struct Player));
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
		pauseGame(longpause);

		//Skips player since they don't have any chips remaining with a small pause
		if(turns[(i%playercount)].chips == 0){
			turns[(i % playercount)].stats[6]++;
			sprintf(numcheck, "%d", turns[(i % playercount)].stats[6]);
			maxwidths[6] = max(maxwidths[6], strlen(numcheck));
			printf("\nTurn Skipped");
			pauseGame(longpause);
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
			pauseGame(shortpause);

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
			pauseGame(longpause);

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
void endGameMenu(struct Player* turns){
	
	//Menu for game along with current settings
	int choice = 0;
	while( (choice != 1) && (choice != 3) ){

		//Menu text
		printf("\nSelect a Choice Below:\n");
		printf("\n%s", BORDER);
		printf("\n1. Play Again");
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
		playGame();
	}//End of if
	
}//End of endGameMenu


//Function that prints statistics for the last game
void printStatistics(struct Player* turns){
	
	//Prints each player's stats with one row for each player and the average at the bottom
	int i = 0;
	int j = 0;
	int width = 0;
	char statprint[MAXDIGITS];
	printf("\n| Player's Name | Left Count | Center Count | Right Count | Dot Count | Dice Rolls | Good Turns | Skipped Turns |\n\n");
	for(i = 0; i < (playercount+1); i++){
		
		//Calculates and prints averages of each stat to the screen
		if(i == playercount){
			
			//Prints average label
			printf("\n%*s", (int)(FIXEDWIDTHS[0] + 8), "Average:");
			
			//Calculates and prints each average to the screen
			for(j = 0; j < STATCOUNT; j++){
				
				//Converts stat to string and calculates spacing needed on screen
				sprintf(statprint, "%.*f", maxwidths[j], average(turns, j));
				width = FIXEDWIDTHS[(j+1)];
				
				//Prints a rounded version of the average to the user
				printf("%*s", (int)width, statprint);
			}//End of for
			
		}//End of if
		
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


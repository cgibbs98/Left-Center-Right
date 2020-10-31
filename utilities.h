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
double average(Player* turns, int index, int count){
	
	//Uses a loop to calculate average and divides it by size before returning it to the user
	double avg = 0;
	int i = 0;
	for(i = 0; i < count; i++){
		avg += turns[i].stats[index];
	}//End of for
	avg /= (double)count;
	return avg;
	
}//End of average

//Median function to calculate median of stats
double median(Player* turns, int index, int count){
	
	//Basic insertion sort to sort each struct's current array
	int i = 0;
	int j = 0;
	int key = 0;
	for(i = 1; i < count; i++) { 
        key = turns[i].stats[index]; 
        j = i-1;
        while (j >= 0 && turns[j].stats[index] > key) { 
            turns[j+1].stats[index] = turns[j].stats[index]; 
            j = j-1; 
        } //End of while
        turns[j+1].stats[index] = key; 
    }//End of for
	
	//Calculates median
	double med = 0;
	if(count % 2 == 0){
		med = (turns[(count/2)-1].stats[index] + turns[(count/2)].stats[index]) / (double)2;
	}//End of if
	else{
		med = turns[(count/2)].stats[index];
	}//End of else
	return med;
	
}//End of median

//Range function to return range of stats
double range(Player* turns, int index, int count){
	
	//Calculates range by getting last and first elements from already sorted array and subtracting them
	double range = turns[count-1].stats[index] - turns[0].stats[index];
	return range;
	
}//End of range

//Random int function for various actions involving a random number
int randomInt(int min, int max){

	//Uses system time seed from playGame() to determine a random number within range of min and max
	int r = rand() % (min - (max + 1)) + min;
	return r;

}//End of randomInt

//Pause function for pausing execution to allow user to keep track of the game
void pauseSim(double sec, int enabled){

	//If pausing is enabled usleep function is called after printing string form before the function call
	if(enabled == 1){
		fflush(stdout);
		usleep((int)(sec*1000000));
	}//End of if

}//End of pauseGame

//Function to reset statistics array widths amd averages to 0
int* resetArray(int* maxwidths, int count){
	
	//Loops thorugh each element of the array and resets it to 0
	int i = 0;
	for(i = 0; i < count; i++){
		maxwidths[i] = 0;
	}//End of for
	return maxwidths;
	
}//End of resetArray











//Change player and chip counts for a variety of purposes
void changeCounts(int sel, int *playercount, int *chipcount, int minplayerrand, int maxplayerrand, int minchiprand, int maxchiprand){

	//If function will use a random number based on current system time and min and max ranges
	if(sel == 1){
		//Sets current system time as the random seed for random player and chip counts
		srand(time(0));
		*playercount = randomInt(minplayerrand, maxplayerrand);
		*chipcount = randomInt(minchiprand, maxchiprand);
	}//End of if

	//Else if function will prompt user for counts
	else if(sel == 2){

		//Set temporary variables in case user enters value beloe minimal count
		int tp = *playercount;
		int tc = *chipcount;
		printf("\n");

		//Prompts user for player count and returns back to pre function call counts if below the minimal count needed
		printf("How many players will play? (Atleast 3 players are required)\n");
		scanf("%d", &*playercount);
		if(*playercount < 3){
			*playercount = tp;
			printf("\nAtleast 3 players are required. Returning to settings menu\n");
			return;
		}//End of if
		else{
			printf("Successfully changed player count\n");
		}//End of else

		//Prompts user for player count and returns back to pre function call counts if below the minimal count needed
		printf("How many chips will each player have? (Atleast 1 chip per player is required)\n");
		scanf("%d", &*chipcount);
		if(*chipcount < 1){
			*chipcount = tc;
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
		*playercount = 5;
		*chipcount = 3;
	}//End of else
	return;

}//End of changeCounts

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
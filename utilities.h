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
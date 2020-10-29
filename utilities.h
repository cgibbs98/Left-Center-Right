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
double average(int* array, int max){
	
	//Uses a loop to calculate average and divides it by size before returning it to the user
	double avg = 0;
	int i = 0;
	for(i = 0; i < max; i++){
		avg += array[i];
	}//End of for
	avg /= (double)max;
	return avg;
	
}//End of average

//Median function to calculate median of stats
double median(int* array, int count){
	
	//Basic insertion sort to sort array
	int i = 0;
	int j = 0;
	int key = 0;
    for(i = 1; i < count; i++) { 
        key = array[i]; 
        j = i-1;
        while (j >= 0 && array[j] > key) { 
            array[j+1] = array[j]; 
            j = j-1; 
        } //End of while
        array[j+1] = key; 
    }//End of for
	
	//Calculates median
	double med = 0;
	if(count % 2 == 0){
		med = (array[(count/2)-1] + array[(count/2)]) / (double)2;
	}//End of if
	else{
		med = array[(count/2)];
	}//End of else
	return med;
	
}//End of median

//Range function to return range of stats
double range(int* array, int count){
	
	//Calculates range by getting min and max of array and subtracting both values
	int min = array[0];
	int max = array[0];
	int i = 0;
	for(i = 1; i < count; i++){
		if(array[i] < min){
			min = array[i];
		}//End of if
		if(array[i] > max){
			max = array[i];
		}//End of if
	}//End of for
	double range = max-min;
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
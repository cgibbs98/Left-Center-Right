//Constants for fixed values that will never be changed
#define STATCOUNT 7
#define MAXPLAYERSIZE 26

//Struct for player which included their name and chip count
typedef struct{
	//Game Values
	char name[MAXPLAYERSIZE];
	int chips;
	//Stats Values Array
	int stats[STATCOUNT];
	/*
	stats[0] = leftcount,
	stats[1] = centercount,
	stats[2] = rightcount,
	stats[3] = dotcount,
	stats[4] = rollcount,
	stats[5] = turncount,
	stats[6] = skipcount;
	*/
}Player;
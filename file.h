//Constants for fixed values that will never be changed
#define MAXFILELOAD 128

//Function that loads defulats for pause enabled, player + chip counts, rand ranges, and pause lengths
void loadDefaults(int *playercount, int *chipcount, int *pauseenabled, double *longpause, double *shortpause, int *minplayerrand, int *maxplayerrand,int *minchiprand, int *maxchiprand){
	
	//Loads file and calls function to set defined defaults and return to main function if file doesn't load
	printf("\nLoading game paramters");
	FILE *fp;
	if(fp = fopen("config.txt", "r")){
		//Gathers every variable needed
		char fbuffer[MAXFILELOAD];
		fgets(fbuffer, MAXFILELOAD, (FILE*)fp);
		char* token1 = strtok(fbuffer, " ");
		token1 = strtok(NULL, " = ");
		*playercount = atoi(token1);
		
		fgets(fbuffer, MAXFILELOAD, (FILE*)fp);
		char* token2 = strtok(fbuffer, " ");
		token2 = strtok(NULL, " = ");
		*chipcount = atoi(token2);
		
		fgets(fbuffer, MAXFILELOAD, (FILE*)fp);
		char* token3 = strtok(fbuffer, " ");
		token3 = strtok(NULL, " = ");
		*pauseenabled = atoi(token3);
		
		fgets(fbuffer, MAXFILELOAD, (FILE*)fp);
		char* token4 = strtok(fbuffer, " ");
		token4 = strtok(NULL, " = ");
		*minplayerrand = atoi(token4);
		
		fgets(fbuffer, MAXFILELOAD, (FILE*)fp);
		char* token5 = strtok(fbuffer, " ");
		token5 = strtok(NULL, " = ");
		*maxplayerrand = atoi(token5);
		
		fgets(fbuffer, MAXFILELOAD, (FILE*)fp);
		char* token6 = strtok(fbuffer, " ");
		token6 = strtok(NULL, " = ");
		*minchiprand = atoi(token6);
		
		fgets(fbuffer, MAXFILELOAD, (FILE*)fp);
		char* token7 = strtok(fbuffer, " ");
		token7 = strtok(NULL, " = ");
		*maxchiprand = atoi(token7);
		
		fgets(fbuffer, MAXFILELOAD, (FILE*)fp);
		char* token8 = strtok(fbuffer, " ");
		token8 = strtok(NULL, " = ");
		*longpause = atof(token8);
		
		fgets(fbuffer, MAXFILELOAD, (FILE*)fp);
		char* token9 = strtok(fbuffer, " ");
		token9 = strtok(NULL, " = ");
		*shortpause = atof(token9);
		
		//Closes file once done loading every value
		fclose(fp);
		
	}//End of if
	else{
		
		//Manually sets defined values to pre defined values and creates new file
		printf("\nCould not find configuration file; Setting program defined defaults and creating new configuration file instead.");
		FILE *fp = fopen("config.txt", "w+"); 
		*playercount = 5;
		fprintf(fp, "PLAYERCOUNT = %d\n", *playercount);
		*chipcount = 3;
		fprintf(fp, "CHIPCOUNT = %d\n", *chipcount);
		*pauseenabled = 0;
		fprintf(fp, "PAUSEENABLED = %d\n", *pauseenabled);
		*minplayerrand = 3;
		fprintf(fp, "MINPLAYERRAND = %d\n", *minplayerrand);
		*maxplayerrand = 9;
		fprintf(fp, "MAXPLAYERRAND = %d\n", *maxplayerrand);
		*minchiprand = 1;
		fprintf(fp, "MINCHIPRAND = %d\n", *minchiprand);
		*maxchiprand = 9;
		fprintf(fp, "MAXCHIPRAND = %d\n", *maxchiprand);
		*longpause = 3.0;
		fprintf(fp, "LONGPAUSE = %f\n", *longpause);
		*shortpause = 1.5;
		fprintf(fp, "SHORTPAUSE = %f", *shortpause);
		fclose(fp);
		return;
		
	}//End of else
	
}//End of loadDefaults

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
	printf("\n9. Set Value for Amount of Seconds for Short Pauses (Must be > 0.0 seconds and <= long pause value)");
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
	FILE *fp = fopen("config1.txt", "w+");
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
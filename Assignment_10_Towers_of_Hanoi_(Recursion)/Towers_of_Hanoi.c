/************************************************************************/
/**************************** PROLOGUE **********************************/
/*	Univeristy of California Extension, Santa Cruz						*/
/*	Advanced C Programming - Section (082)								*/
/*	Instructor: Rajainder A. Yeldandi									*/
/*	Author: Nakul Bagewadi												*/
/*	Assignment# 10														*/
/*	Topic: Recursion													*/
/*	File name: Towers_of_Hanoi											*/
/*	Date: 5/9/2016														*/
/*	Objective: Execute 'Towers of Hanoi' with 4,5,6 discs				*/
/*	Comments:															*/
/************************************************************************/				

#include <stdio.h>
#include <stdlib.h>

// pointer to write file
FILE *wrFile;


void Move_Disc(unsigned int Disc, char *I_TOWER, char *T_TOWER, char *A_TOWER, unsigned int Disc_Max)
{
	if(Disc == 1) 
	{
		if(Disc == Disc_Max)
		{
			printf ("\n>> Final move. Moving disc %u from %s to %s", Disc, I_TOWER, T_TOWER);
			fprintf(wrFile, "\n>> Final move. Moving disc %u from %s to %s", Disc, I_TOWER, T_TOWER);
			Disc_Max--;
		}
		else
		{
			printf ("\nMoving disc %u from %s to %s", Disc, I_TOWER, T_TOWER);
			fprintf(wrFile, "\nMoving disc %u from %s to %s", Disc, I_TOWER, T_TOWER);
		}
	}
	else
	{
		Move_Disc((Disc-1), I_TOWER, A_TOWER, T_TOWER, Disc_Max);

		if(Disc == Disc_Max)
		{
			printf ("\n>> Final move. Moving disc %u from %s to %s", Disc, I_TOWER, T_TOWER);
			fprintf(wrFile, "\n>> Final move. Moving disc %u from %s to %s", Disc, I_TOWER, T_TOWER);
			Disc_Max--;
		}
		else
		{
			printf ("\nMoving disc %u from %s to %s", Disc, I_TOWER, T_TOWER);
			fprintf(wrFile, "\nMoving disc %u from %s to %s", Disc, I_TOWER, T_TOWER);
		}

		Move_Disc((Disc - 1), A_TOWER, T_TOWER, I_TOWER, Disc_Max);
	}
}


/***** main() *****/
void main()
{
	int discs;

	// open file to write
	wrFile = fopen ("Towers_of_Hanoi.txt", "w");
	if (wrFile == NULL)	printf("\n\nError opening writing file"); 
	
	do
	{
		printf("\n\nEnter the number of discs to begin or -1 to quit: ");
		scanf("%u", &discs);

		if(discs != -1)
		{
			printf("\n\nUser put %u discs in the 'INITIAL' Tower of the game.\n\n", discs);
			fprintf(wrFile, "\n\nUser put %u discs in the 'INITIAL' Tower of the game.\n\n", discs);

			Move_Disc(discs, "INITIAL_TOWER", "TARGET_TOWER", "AUX_TOWER", discs);

			printf("\nGAME OVER !!!\n");
			fprintf(wrFile, "\nGAME OVER !!!\n");
		}
	}
	while(discs != -1);

	printf("\n\nYou chose to quit.\n\n");
	fprintf(wrFile, "\n\nYou chose to quit.\n\n");

	fclose (wrFile);						// close the write file
		
	printf("\nPress any key and hit [Enter] to exit: ");
	scanf("%d", &discs);
	return;
}
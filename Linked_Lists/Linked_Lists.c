/************************************************************************/
/**************************** PROLOGUE **********************************/
/*	Univeristy of California Extension, Santa Cruz						*/
/*	Advanced C Programming - Section (082)								*/
/*	Instructor: Rajainder A. Yeldandi									*/
/*	Author: Nakul Bagewadi												*/
/*	Assignment# 11														*/
/*	Topic: Linked List													*/
/*	File name: Queue													*/
/*	Date: 5/20/2016														*/
/*	Objective:	Implement a linked list									*/
/*	Comments:															*/
/************************************************************************/
/************************************************************************/
			

#include <stdio.h>
#include <stdlib.h>

/***** global variables *****/
// individual linked list element as a structure
struct listnode {
	int number;
	struct listnode *nextptr;
};

typedef struct listnode MyNode;
typedef struct listnode* MyNodePtr;

// pointers to read and write files
FILE *rdFile, *wrFile;


// this function checks if the linked list is empty, if yes, returns a 1
int IsListEmpty(MyNodePtr ListPtr)
{
	return (ListPtr == NULL);
}


// this function inserts an element in the linked list, if successful, returns a 1
int Insert(MyNodePtr *RootPtr, int mynumber)
{
	
	MyNodePtr NewPtr, PrevPtr, CurrPtr;

	NewPtr = (MyNodePtr) malloc (sizeof(MyNode));

	if(NewPtr != NULL)								// dynamic memory allocation successful 
	{
		NewPtr->number = mynumber;					// assign the value to be inserted to the new node
		NewPtr->nextptr = NULL;
		PrevPtr = NULL;
		CurrPtr = *RootPtr;							// dereference pointer to pointer, points to the root of the linked list					
		
		while((CurrPtr != NULL) && (mynumber > CurrPtr->number))	// traverse thru the list & insert node in ascending order
		{
			PrevPtr = CurrPtr;
			CurrPtr = CurrPtr->nextptr;
		} 
		
		if(PrevPtr == NULL)							// inserting the first node in the linked list
		{
			NewPtr->nextptr = *RootPtr;				// dereference pointer to pointer,
			*RootPtr = NewPtr;						// dereference pointer to pointer,
		}
		else
		{
			PrevPtr->nextptr = NewPtr;
			NewPtr-> nextptr = CurrPtr;
		}
		return 1;
	}
	else											// dynamic memory allocation unsuccessful 
	{
		printf ("%s", "\n\nUnable to insert. Cannot allocate memory for a new node.");
		fprintf(wrFile, "\n\nUnable to insert. Cannot allocate memory for a new node.");
		return -1;
	}
}

// this function removes an element in the linked list, if successful, returns a 1
int Remove(MyNodePtr *RootPtr, int mynumber)
{
	
	MyNodePtr TempPtr, PrevPtr, CurrPtr;

	if(mynumber == (*RootPtr)->number)
	{
		TempPtr = *RootPtr;
		*RootPtr = (*RootPtr)->nextptr;
		free (TempPtr);
		return (mynumber);
	}
	else
	{
		PrevPtr = *RootPtr;
		CurrPtr = (*RootPtr)->nextptr;
		while ((CurrPtr != NULL) && (CurrPtr->number != mynumber))
		{
			PrevPtr = CurrPtr;
			CurrPtr = CurrPtr ->nextptr;
		}
		if (CurrPtr != NULL)
		{
			TempPtr = CurrPtr;
			PrevPtr->nextptr = CurrPtr ->nextptr;
			CurrPtr = CurrPtr->nextptr;
			free (TempPtr);
			return (mynumber);
		}
	}
	return -1;
}


// this function prints the linked list nodes
void Print_LinkedList(MyNodePtr ListPtr)
{
	if(ListPtr == NULL) 
	{
		printf ("%s", "\nLinked List is empty.");
		fprintf(wrFile, "\nLinked List is empty.");
	}
	else
	{
		while(ListPtr != NULL)
		{
			printf ("%d -> ", ListPtr->number);
			fprintf(wrFile, "%d -> ", ListPtr->number);

			ListPtr = ListPtr->nextptr;
		}
		printf ("%s", "NULL\n\n");
		fprintf(wrFile, "NULL\n\n");
	}
}

// this function reverses the linked list nodes
MyNodePtr Reverse_LinkedList(MyNodePtr ListPtr)
{
	MyNodePtr Reverse_ListPtr = NULL, Temp_ListPtr = NULL;
	
	if(ListPtr == NULL) 
	{
		printf ("%s", "\nCannot reverse an empty linked list.");
		fprintf(wrFile, "\nCannot reverse an empty linked list.");
	}
	else
	{
		while(ListPtr != NULL)
		{
			Temp_ListPtr = ListPtr;
			ListPtr = ListPtr->nextptr;
			Temp_ListPtr->nextptr = Reverse_ListPtr;
			Reverse_ListPtr = Temp_ListPtr;

			//Print_LinkedList(Reverse_ListPtr);				// print the linked list nodes
		}
		//printf ("%s", "NULL\n\n");
		//fprintf(wrFile, "NULL\n\n");
	}

	return(Reverse_ListPtr);
}

/***** main() *****/
void main()
{
	int i, delete_number, add_num, removed_number;
	char ch, num[10];

	MyNodePtr MyRootPtr = NULL, Reverse_MyRootPtr = NULL;

	// open file to write
	wrFile = fopen ("LinkedList_Operations.txt", "w");
	if (wrFile == NULL)	printf("\n\nError opening writing file"); 

	// read from input file
	rdFile = fopen ("LinkedList_Input.txt", "r");
	if (rdFile == NULL)	printf("\n\nError opening reading file"); 
	else
	{
		do 
		{
			ch = fgetc(rdFile);								// read a character from the input file
			
			if((ch >= -1 && ch <= 32) || (ch >= 58 && ch <= 255)) continue;		// ignore all characters except numbers
			
			else if(ch >= 48 && ch <= 57);					// read only if digits, assume inputs are integers
			{
				i = 0;			
				do
				{
					num[i++] = ch;
					ch = fgetc(rdFile);						// read a character from the input file
				}
				while(ch >= 48 && ch <= 57);				// read only if digits, assume inputs are integers

				add_num = atoi(num);						// convert string into integer number
				Insert(&MyRootPtr, add_num);				// insert a new node in the linked list
				Print_LinkedList(MyRootPtr);				// print the linked list nodes
				if(add_num == 50)
				{
					i=0;
				}
				for(i=0;i<10;i++) num[i] = 255;				// reset num[] array
			}
		}
		while (ch != EOF);									// read until end of file is reached
		printf("\n\n------------------------------------------------------------------------------\n\n");
		fprintf(wrFile, "\n\n------------------------------------------------------------------------------\n\n");
	}
	
	// Reverse linked list and print
	Reverse_MyRootPtr = Reverse_LinkedList(MyRootPtr);		// reverse the linked list nodes
	printf("\nReversing and printing the linked list.\n");
	fprintf(wrFile, "\nReversing and printing the linked list.\n");
	Print_LinkedList(Reverse_MyRootPtr);					// print the linked list nodes
	MyRootPtr = Reverse_LinkedList(Reverse_MyRootPtr);		// print the linked list nodes
	//Print_LinkedList(MyRootPtr);							// print the linked list nodes
	printf("\n\n------------------------------------------------------------------------------\n\n");
	fprintf(wrFile, "\n\n------------------------------------------------------------------------------\n\n");

	do
	{
		printf("\nEnter the node to be deleted from the linked list or -1 to quit: ");
		fprintf(wrFile, "\nEnter the node to be deleted from the linked list or -1 to quit: ");
		scanf("%d", &delete_number);
		printf("\n");
		fprintf(wrFile, "\n");
		if(delete_number == -1) 
		{
			printf("\nYou chose to quit.");
			fprintf(wrFile, "\nYou chose to quit.");
			
			continue;
		}
		
		removed_number = Remove(&MyRootPtr, delete_number);	// remove a node from the linked list
		if(removed_number == -1)
		{
			printf ("\n\nYou entered %d. Unable to remove the number as it does not exist in the linked list.\n\n", delete_number);
			fprintf(wrFile, "\n\nYou entered %d. Unable to remove the number as it does not exist in the linked list.\n\n", delete_number);
		}
		else
		{
			printf("\n\nYou entered %d. Removed %d from the linked list.\n\n", removed_number, removed_number);
			fprintf(wrFile, "\n\nYou entered %d. Removed %d from the linked list.\n\n", removed_number, removed_number);
			Print_LinkedList(MyRootPtr);					// print the linked list nodes
		}
	}
	while(delete_number != -1);

	fclose (rdFile);										// close the read file
	fclose (wrFile);										// close the write file
		
	printf("\nPress any key and hit [Enter] to exit: ");
	scanf("%d", &i);
	return;
}
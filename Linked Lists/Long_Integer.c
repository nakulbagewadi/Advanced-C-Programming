/************************************************************************/
/**************************** PROLOGUE **********************************/
/*	Univeristy of California Extension, Santa Cruz						*/
/*	Advanced C Programming - Section (082)								*/
/*	Instructor: Rajainder A. Yeldandi									*/
/*	Author: Nakul Bagewadi												*/
/*	Assignment# 16														*/
/*	Topic: Long Integer													*/
/*	File name: Queue													*/
/*	Date: 5/22/2016														*/
/*	Objective:	Add two long integers using linked lists				*/
/*	Comments:															*/
/************************************************************************/
/************************************************************************/
			

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_NODE_LEN 5
#define NUM_TO_BE_ADDED 2
#define MAX_NUM_LEN 50

/***** global variables *****/
// individual linked list element as a structure
struct listnode {
	unsigned long int number;
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
int Insert(MyNodePtr *RootPtr, unsigned long int mynumber)
{
	
	MyNodePtr NewPtr, PrevPtr, CurrPtr;

	NewPtr = (MyNodePtr) malloc (sizeof(MyNode));

	if(NewPtr != NULL)								// dynamic memory allocation successful 
	{
		NewPtr->number = mynumber;					// assign the value to be inserted to the new node
		NewPtr->nextptr = NULL;
		PrevPtr = NULL;
		CurrPtr = *RootPtr;							// dereference pointer to pointer, points to the root of the linked list					
		/*
		while((CurrPtr != NULL) && (mynumber > CurrPtr->number))	// traverse thru the list & insert node in ascending order
		{
			PrevPtr = CurrPtr;
			CurrPtr = CurrPtr->nextptr;
		} 
		*/
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
unsigned long int Remove(MyNodePtr *RootPtr, unsigned long int mynumber)
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
			printf ("%d ", ListPtr->number);
			fprintf(wrFile, "%d ", ListPtr->number);

			ListPtr = ListPtr->nextptr;
		}
		printf ("%s", "NULL\n\n");
		fprintf(wrFile, "NULL\n\n");
	}
}

// this function prints the linked list nodes as a single number
void Print_Number(MyNodePtr ListPtr)
{
	int i;
	unsigned long int num[MAX_NODE_LEN] = {0};
	int print_leading_zeros = 0;

	if(ListPtr == NULL) 
	{
		printf ("%s", "\nLinked List is empty.");
		fprintf(wrFile, "\nLinked List is empty.");
	}
	else
	{
		do
		{
			if(print_leading_zeros) 
			{
				//  (number, char* or string name, base of number system to be converted into)
				itoa(ListPtr->number, num, 10);

				if(strlen(num) < MAX_NODE_LEN)
				{
					for(i = (MAX_NODE_LEN - strlen(num)); i > 0; i--)
					{
						printf ("0");
						fprintf(wrFile, "0");
					}
				}
			}
			printf ("%d", ListPtr->number);
			fprintf(wrFile, "%d", ListPtr->number);

			ListPtr = ListPtr->nextptr;

			print_leading_zeros = 1;
		}
		while(ListPtr != NULL);

		printf ("\n");
		fprintf(wrFile, "\n");
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

// this function adds the two numbers from linked list elements, if successful returns 1
int Add_Numbers(MyNodePtr ListPtr1, MyNodePtr ListPtr2, MyNodePtr *ResPtr)
{
	unsigned int carry = 0;
	unsigned long int divide_mod = (int)pow((double)10,(double)MAX_NODE_LEN);

	MyNodePtr NewPtr;

	// check if both linked lists are empty, if yes there is nothing to add, result is zero
	if(ListPtr1 == NULL && ListPtr2 == NULL) 
	{
		printf ("%s", "\nNumbers as linked lists are empty.");
		fprintf(wrFile, "\nNumbers as linked lists are empty.");
		return(-1);
	}
	else
	{
		// add until both list nodes are NULL
		while(ListPtr1 != NULL || ListPtr2 != NULL || carry == 1)
		{

			NewPtr = (MyNodePtr) malloc (sizeof(MyNode));

			if(NewPtr != NULL)											// dynamic memory allocation successful 
			{
				NewPtr->number = 0;										// assign the value to be inserted to the new node
				NewPtr->nextptr = NULL;

				if(ListPtr1 != NULL && ListPtr2 != NULL)				// if both nodes exist, add both nodes with the result
				{
					NewPtr->number = ListPtr1->number + ListPtr2->number + carry;
					carry = NewPtr->number/divide_mod;
					NewPtr->number = NewPtr->number % divide_mod;
					
					ListPtr1 = ListPtr1->nextptr;
					ListPtr2 = ListPtr2->nextptr;
				}
				else if(ListPtr1 != NULL && ListPtr2 == NULL)			// if only list_1 node exists, add only that node with result
				{
					NewPtr->number = ListPtr1->number + carry;
					carry = NewPtr->number/divide_mod;
					NewPtr->number = NewPtr->number % divide_mod;
					
					ListPtr1 = ListPtr1->nextptr;
				}
				else if(ListPtr1 == NULL && ListPtr2 != NULL)			// if only list_2 node exists, add only that node with result
				{
					NewPtr->number = ListPtr2->number + carry;
					carry = NewPtr->number/divide_mod;
					NewPtr->number = NewPtr->number % divide_mod;
					
					ListPtr2 = ListPtr2->nextptr;
				}
				else if(ListPtr1 != NULL && ListPtr2 != NULL && carry)	// if both lists are over but we have a carryover for the MSB
				{
					NewPtr->number = carry;
				}

				
				NewPtr->nextptr = *ResPtr;								// dereference pointer to pointer,
				*ResPtr = NewPtr;										// dereference pointer to pointer,
				
				Print_LinkedList(*ResPtr);

			} // if
			else														// dynamic memory allocation unsuccessful 
			{
				printf ("%s", "\n\nCannot allocate memory for a new node.");
				fprintf(wrFile, "\n\nCannot allocate memory for a new node.");
				return (-1);
			} // else
		} // while
	} // else
	
	return(1);
}


/***** main() *****/
void main()
{
	int i = 0, j = 0, k = 0, t = 0, node_num = 0, index = 0;
	char ch, num[MAX_NODE_LEN] = {0}, Numbers[NUM_TO_BE_ADDED][MAX_NUM_LEN] = {0}, Num_Len[NUM_TO_BE_ADDED] = {0};

	MyNodePtr NumberList_Ptr[NUM_TO_BE_ADDED + 1] = {NULL, NULL, NULL}; // Number_Ptr[0] = Number_1, Number_Ptr[1] = Number_2, Number_Ptr[2] = Answer
	MyNodePtr Rev_NumberList_Ptr[NUM_TO_BE_ADDED + 1] = {NULL, NULL, NULL};	

	// open file to write
	wrFile = fopen ("LongInteger_Operations.txt", "w");
	if (wrFile == NULL)	printf("\n\nError opening writing file"); 

	// read from input file
	rdFile = fopen ("LongInteger_Input.txt", "r");
	if (rdFile == NULL)	printf("\n\nError opening reading file"); 
	else
	{
		ch = fgetc(rdFile);									// read a character from the input file
		do 
		{
			// ignore all characters except digits, increment index to read next number
			if((ch >= -1 && ch <= 32) || (ch >= 58 && ch <= 255))
			{ 
				index++; 
				ch = fgetc(rdFile);							// read a character from the input file
				continue; 
			}
			
			else if(ch >= 48 && ch <= 57);					// read only if digits, assume inputs are integers
			{
				i = 0;			
				do
				{
					Numbers[index][i++] = ch;
					ch = fgetc(rdFile);						// read a character from the input file
				}
				while((ch >= 48 && ch <= 57));				// read only if digits & 5 digits in each linked list
				Numbers[index][i++] = '\0';					// append NULL character to terminate array
			}
		}
		while (ch != EOF);									// read until end of file is reached
	}
	
	// read array contents into linked list nodes, read in groups of 5
	for(index=0; index < NUM_TO_BE_ADDED; index++)
	{
		Num_Len[index] = strlen(Numbers[index]);
		
		printf("\nShowing accumulation of linked list for number# %d\n\n", index+1);
		fprintf(wrFile, "\nShowing accumulation of linked list for number# %d\n\n", index+1);
		
		k = Num_Len[index] % MAX_NODE_LEN;					// for MSb

		for(j=0; j < k; j++)
		{
			num[t++] = Numbers[index][j];
			if(j < k-1) continue;
			
			node_num = atoi(num);							// convert string into integer number
			Insert(&NumberList_Ptr[index], node_num);		// insert a new node in the linked list
			Print_LinkedList(NumberList_Ptr[index]);		// print the linked list nodes
			
			for(t=0; t < MAX_NODE_LEN; t++) num[t] = 0;		// clear num[] array
			t = 0;
		}

		for(; j < Num_Len[index]; j++)
		{
			num[t++] = Numbers[index][j];
			if(t < MAX_NODE_LEN) continue;

			node_num = atoi(num);							// convert string into integer number
			Insert(&NumberList_Ptr[index], node_num);		// insert a new node in the linked list
			Print_LinkedList(NumberList_Ptr[index]);		// print the linked list nodes
			
			for(t=0; t < MAX_NODE_LEN; t++) num[t] = 0;		// clear num[] array
			t = 0;
		}
		printf("\n------------------------------------------------------------------------------\n");
		fprintf(wrFile, "\n------------------------------------------------------------------------------\n");
	}

	// reverse the linked lists for number 1 and 2 to print digits in original order
	for(index=0; index < NUM_TO_BE_ADDED; index++)
	{
		// Reverse linked list and print
		Rev_NumberList_Ptr[index] = Reverse_LinkedList(NumberList_Ptr[index]);
		
		printf("\nNumber_%d as read from the input file: ", index+1);
		fprintf(wrFile, "\nNumber_%d as read from the input file: ", index+1);		
		Print_Number(Rev_NumberList_Ptr[index]);
		printf("\n");
		fprintf(wrFile, "\n");
		
		NumberList_Ptr[index] = Reverse_LinkedList(Rev_NumberList_Ptr[index]);
		
		printf("\nShowing how number_%d is stored as a linked list\n\n", index+1);
		fprintf(wrFile, "\nShowing how number_%d is stored as a linked list\n\n", index+1);
		Print_LinkedList(NumberList_Ptr[index]);
		printf("\n------------------------------------------------------------------------------\n");
		fprintf(wrFile, "\n------------------------------------------------------------------------------\n");
	}

	printf("\nShowing accumulation of linked list nodes for the result\n\n");
	fprintf(wrFile, "\nShowing accumulation of linked list nodes for the result\n\n");

	// add the two numbers
	Add_Numbers(NumberList_Ptr[0], NumberList_Ptr[1], &NumberList_Ptr[2]);
	
	printf("\n------------------------------------------------------------------------------\n");
	fprintf(wrFile, "\n------------------------------------------------------------------------------\n");
	// print result as a number
	printf("\nResult of adding the two numbers is: ");
	fprintf(wrFile, "\nResult of adding the two numbers is: ");
	Print_Number(NumberList_Ptr[2]);

	// print result as a linked list
	printf("\nShowing how result is stored as linked list nodes\n\n");
	fprintf(wrFile, "\nShowing how result is stored as linked list nodes\n\n");
	Print_LinkedList(NumberList_Ptr[2]);

	fclose (rdFile);										// close the read file
	fclose (wrFile);										// close the write file
		
	printf("\nPress any key and hit [Enter] to exit: ");
	scanf("%d", &i);
	return;
}
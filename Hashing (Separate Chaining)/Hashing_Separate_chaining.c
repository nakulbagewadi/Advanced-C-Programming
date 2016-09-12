/************************************************************************/
/**************************** PROLOGUE **********************************/
/*	Univeristy of California Extension, Santa Cruz						*/
/*	Advanced C Programming - Section (082)								*/
/*	Instructor: Rajainder A. Yeldandi									*/
/*	Author: Nakul Bagewadi												*/
/*	Assignment# 15														*/
/*	Topic: Hashing														*/
/*	File name: Hashing_Separate_chaining								*/
/*	Date: 6/17/2016														*/
/*	Objective:	Build a hash table										*/
/*	Comments:															*/
/************************************************************************/
/************************************************************************/
			
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define HASHTABLESIZE 15
#define MAXNODES 100

/***** global variables *****/
// individual linked list element as a structure
struct listnode {
	unsigned long int key;
	unsigned long int record;
	struct listnode *nextptr;
};

typedef struct listnode MyNode;
typedef struct listnode* MyNodePtr;

// pointers to read and write files
FILE *rdFile, *wrFile;

// Hashing function, add each digit in the key and then modulo with hash table size
int HashFunction(int MyKey)
{
	int sum = 0, rem = 0;
	
	while(MyKey > 0)
	{
		rem = MyKey % 10;
		sum += rem;
		MyKey /= 10;
	}
	return (sum % HASHTABLESIZE);
}

// this function checks if the linked list is empty, if yes, returns a 1
int IsListEmpty(MyNodePtr ListPtr)
{
	return (ListPtr == NULL);
}

// this function inserts an element in the linked list, if successful, returns a 1
int InsertInHashTable(MyNodePtr *HashTablePtr[], int hash_table_index, int current_key)
{

	MyNodePtr NewPtr, PrevPtr, CurrPtr;

	NewPtr = (MyNodePtr) malloc (sizeof(MyNode));

	if(NewPtr != NULL)								// dynamic memory allocation successful 
	{
		NewPtr->key = current_key;					// assign the value to be inserted to the new node
		NewPtr->record = current_key/1000;			// assume some record value
		NewPtr->nextptr = NULL;
		
		if(HashTablePtr[hash_table_index] == NULL)	// if no key is present in the hash table at that index, insert the new key
		{
			HashTablePtr[hash_table_index] = NewPtr;
		}
		else										// if collision occurs, add current key in the linked list
		{
			NewPtr->nextptr = HashTablePtr[hash_table_index];
			HashTablePtr[hash_table_index] = NewPtr;
		}
		return (1);
	}
	else											// dynamic memory allocation unsuccessful 
	{
		printf ("%s", "\n\nUnable to insert. Cannot allocate memory for a new node.");
		fprintf(wrFile, "\n\nUnable to insert. Cannot allocate memory for a new node.");
		exit(1);
	}
}

// this function removes a key in the hash table, if successful, returns a 1
int RemoveFromHashTable(MyNodePtr *HashTablePtr[], int hash_table_index, unsigned long int remove_key)
{
	int found = 0;
	MyNodePtr TempPtr, PrevPtr, CurrPtr;

	if(HashTablePtr[hash_table_index] == NULL)	// if no key is present in the hash table at that index, key is not present in the table
	{
		return (-1);
	}
	else
	{
		CurrPtr = HashTablePtr[hash_table_index];
		PrevPtr = HashTablePtr[hash_table_index];

		if(CurrPtr->key == remove_key)
		{
			HashTablePtr[hash_table_index] = CurrPtr->nextptr;
			free(CurrPtr);
			found = 1;
			return(found);						// key found
		}
		else
		{
			CurrPtr = CurrPtr->nextptr;
			while(CurrPtr != NULL)
			{
				if(CurrPtr->key == remove_key)
				{
					PrevPtr->nextptr = CurrPtr->nextptr;

					free(CurrPtr);
					found = 1;
					return(found);				// key found
				}
				else
				{
					CurrPtr = CurrPtr->nextptr;
					PrevPtr = PrevPtr->nextptr;
				}
			}
			return(found);						// key not present in the hash table
		}
	}
}


// this function prints the hash table
void Print_HashTable(MyNodePtr *HashTablePtr[])
{
	int i;
	MyNodePtr TempPtr;

	for(i=0; i<HASHTABLESIZE; i++)
	{
		if(HashTablePtr[i] == NULL) 
		{
			printf ("HashTable[%d] -> NULL\n\n", i);
			fprintf(wrFile, "HashTable[%d] -> NULL\n\n", i);
		}
		else
		{
			TempPtr = HashTablePtr[i];

			printf ("HashTable[%d] -> ", i);
			fprintf(wrFile, "HashTable[%d] -> ", i);

			while(TempPtr != NULL)
			{
				printf ("%u -> ", TempPtr->key);
				fprintf(wrFile, "%u -> ", TempPtr->key);

				TempPtr = TempPtr->nextptr;
			}
			printf ("%s", "NULL\n\n");
			fprintf(wrFile, "NULL\n\n");
		}
	}
}

/***** main() *****/
void main()
{
	int i, successful, key, hashed_key;
	unsigned long int random_num, delete_key;
	char ch, num[10];

	MyNodePtr HashTable[HASHTABLESIZE] = {NULL};
	MyNodePtr CurrentNodePtr = NULL;

/*****  UNCOMMENT THIS CODE BLOCK TO GENERATE RANDOM KEYS EVERYTIME PROGRAM IS RUN...

	// open file to write 100 random numbers as keys
	wrFile = fopen ("Input_keys.txt", "w");
	if (wrFile == NULL)	printf("\n\nError opening reading file"); 

	// generate 100 random numbers as keys and write to input file
	srand((unsigned int)time(NULL));
	for(i=0; i < MAXNODES; i++)
	{
		random_num = (i+1) * rand(); 
		printf ("%u\n", random_num);
		fprintf(wrFile, "%u\n", random_num);
	}

	fclose (wrFile);										// close the write file
*****/

	// open file to log the operations performed on the keys
	wrFile = fopen ("Hashing_Operations.txt", "w");
	if (wrFile == NULL)	printf("\n\nError opening writing file"); 

	// read from input file generated above
	rdFile = fopen ("Input_keys.txt", "r");
	if (rdFile == NULL)	printf("\n\nError opening reading file"); 
	else
	{
		do 
		{
			ch = fgetc(rdFile);								// read a character from the input file
			
			if((ch >= -1 && ch <= 32) || (ch >= 58 && ch <= 255)) continue;			// ignore all characters except numbers
			
			else if(ch >= 48 && ch <= 57);					// read only if digits, assume inputs are integers
			{
				i = 0;			
				do
				{
					num[i++] = ch;
					ch = fgetc(rdFile);						// read a character from the input file
				}
				while(ch >= 48 && ch <= 57);				// read only if digits, assume inputs are integers

				key = atoi(num);							// convert string into key

				hashed_key = HashFunction(key);				// generate the Hashed(key)

				printf ("Key = %u & HashedKey = %d\n", key, hashed_key);
				fprintf(wrFile, "Key = %u & HashedKey = %d\n", key, hashed_key);

				InsertInHashTable(HashTable, hashed_key, key);	// insert the hashed key in the the hash table

				for(i=0;i<10;i++) num[i] = 255;				// reset num[] array
			}
		}
		while (ch != EOF);									// read until end of file is reached
	}

	printf("\n\n------------------------------------------------------------------------------\n\n");
	fprintf(wrFile, "\n\n------------------------------------------------------------------------------\n\n");
	printf ("Printing Hash Table contents: \n");
	fprintf(wrFile, "Printing Hash Table contents: \n");
	Print_HashTable(HashTable);
	printf("\n\n------------------------------------------------------------------------------\n\n");
	fprintf(wrFile, "\n\n------------------------------------------------------------------------------\n\n");

	do
	{
		printf("\nEnter the node to be deleted from the Hash Table above or -1 to quit: ");
		fprintf(wrFile, "\nEnter the node to be deleted from the Hash Table above or -1 to quit: ");
		scanf("%u", &delete_key);
		printf("\n");
		fprintf(wrFile, "\n");

		if(delete_key == -1) 
		{
			printf("\nYou chose to quit.");
			fprintf(wrFile, "\nYou chose to quit.");
			continue;
		}
		
		hashed_key = HashFunction(delete_key);									// generate the Hashed(key)

		printf ("Delete_key = %u & HashedDeleteKey = %d\n", delete_key, hashed_key);
		fprintf(wrFile, "Delete_key = %u & HashedDeleteKey = %d\n", delete_key, hashed_key);
		successful = RemoveFromHashTable(HashTable, hashed_key, delete_key);	// remove a node from the linked list

		if(successful == -1)
		{
			printf ("\n\nYou entered %u. Unable to remove the key as it does not exist in the Hash table.\n\n", delete_key);
			fprintf(wrFile, "\n\nYou entered %u. Unable to remove the key as it does not exist in the Hash table.\n\n", delete_key);
		}
		else
		{
			printf("\n\nYou entered key: %d. Removed key: %d from the hash table index: %d.\n\n", delete_key, delete_key, hashed_key);
			fprintf(wrFile, "\n\nYou entered key: %d. Removed key: %d from the hash table index: %d.\n\n", delete_key, delete_key, hashed_key);
			Print_HashTable(HashTable);
		}
	}
	while(delete_key != -1);
	

	fclose (rdFile);										// close the read file
	fclose (wrFile);										// close the write file
	
	printf("\nPress any key and hit [Enter] to exit: ");
	scanf("%d", &i);
	return;
}
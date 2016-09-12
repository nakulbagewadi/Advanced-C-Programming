/************************************************************************/
/**************************** PROLOGUE **********************************/
/*	Univeristy of California Extension, Santa Cruz						*/
/*	Advanced C Programming - Section (082)								*/
/*	Instructor: Rajainder A. Yeldandi									*/
/*	Author: Nakul Bagewadi												*/
/*	Assignment# 16														*/
/*	Topic: Playing cards												*/
/*	File name: SequencingCards											*/
/*	Date: 5/16/2016														*/
/*	Objective:	Shuffle a suit of cards and display as per an algorithm	*/
/*	Comments:															*/
/************************************************************************/
/************************************************************************/
			

#include <stdio.h>
#include <stdlib.h>

/***** #define *****/
#define QUEUE_SIZE 40
#define NO_OF_CARDS 13
#define EMPTYQUEUE -1

/***** global variables *****/
// queue structure
typedef struct queue {
	int front_ptr, rear_ptr;
	char elements[QUEUE_SIZE];
} MyQueue;

// pointers to read and write files
FILE *rdFile, *wrFile;


// this function checks if the queue is empty, if yes, returns a 1
int IsQueueEmpty(MyQueue *queue)
{
	if(queue->front_ptr == queue->rear_ptr) return 1;
	else									return 0;
}

// this function checks if the queue is full, if yes, returns a 1
int IsQueueFull(MyQueue *queue)
{
	if(queue->rear_ptr == queue->front_ptr) return 1;
	else									return 0;
}

// this function inserts an element in the queue, if successful, returns a 1
int Insert(MyQueue *queue, char card)
{
	if(queue->front_ptr == QUEUE_SIZE - 1) queue->rear_ptr = 0;
	else								   (queue->rear_ptr)++;
	
	if(!IsQueueFull(queue)) 
	{

		queue->elements[queue->rear_ptr] = card;

		printf("\nINSERTing %c in the queue", card);
		fprintf(wrFile, "\nINSERTing %c in the queue", card);
	}
	else
	{
		printf ("%s", "\n\nCannot insert into a full queue");
		fprintf(wrFile, "\n\nCannot insert into a full queue");
		exit (1);
	}
	return 1;
}

// this function removes an element from the queue
char Remove(MyQueue *queue)
{
	if(!IsQueueEmpty(queue)) 
	{
		if(queue->front_ptr == QUEUE_SIZE - 1) queue->front_ptr = 0;
		else								   (queue->front_ptr)++;

		printf("\nREMOVing %c from the queue", queue->elements[queue->front_ptr]);
		fprintf(wrFile, "\nREMOVing %c from the queue", queue->elements[queue->front_ptr]);

		return(queue->elements[queue->front_ptr]);
	}
	else
	{
		printf ("%s", "\n\nCannot remove from an empty queue");
		fprintf(wrFile, "\n\nCannot remove from an empty queue");
		exit (1);
	}
}

// this function prints the queue contents from front_ptr to rear_ptr
void Print_Queue(MyQueue *queue)
{
	int print;
	print = queue->front_ptr;

	printf("contents: ");
	fprintf(wrFile, "contents: ");

	do		
	{
		print++;
		printf("%c ", queue->elements[print]);
		fprintf(wrFile, " %c", queue->elements[print]);

		if(print == QUEUE_SIZE - 1) print = 0;
	}
	while(print != queue->rear_ptr);
}

// this function gets the original card queue copy and shuffled card queue pointer to shuffle the cards from original sequence
// and place them in the shuffled queue...
void Shuffle_Cards(MyQueue MyCards, MyQueue *ShuffledPtr)
{
	MyQueue *MyCardsPtr;
	char cards;
	int i = 1;

	MyCardsPtr = &MyCards;

	do
	{
		cards = MyCardsPtr->elements[MyCardsPtr->rear_ptr];		// remove card from the rear of original sequence
		(MyCardsPtr->rear_ptr)--;								// adjust rear pointer to point to 'current' last card	
		
		ShuffledPtr->elements[(ShuffledPtr->front_ptr)--] = cards;
		if(ShuffledPtr->front_ptr == EMPTYQUEUE) ShuffledPtr->front_ptr = QUEUE_SIZE - 1;
		
		cards = ShuffledPtr->elements[ShuffledPtr->rear_ptr];
		(ShuffledPtr->rear_ptr)--;								// remove card from the rear of the shuffled queue
		
		ShuffledPtr->elements[(ShuffledPtr->front_ptr)--] = cards;
		if(ShuffledPtr->front_ptr == EMPTYQUEUE) ShuffledPtr->front_ptr = QUEUE_SIZE - 1;
				
		printf("\nShuffling iteration %d, Shuffled queue ", i);
		fprintf(wrFile, "\nShuffling iteration %d, Shuffled queue ", i++);
		Print_Queue(ShuffledPtr);
	} 
	while (MyCardsPtr->front_ptr != MyCardsPtr->rear_ptr);
}

// this function puts the top card of the shuffled set to the bottom and opens the next card, until only one card is left
void Play_Cards(MyQueue *ShuffledPtr)
{
	char cards;
	int i = 0;
	
	printf("\nOpening cards: ");
	fprintf(wrFile, "\nOpening cards: ");
	
	do
	{
		cards = ShuffledPtr->elements[++(ShuffledPtr->front_ptr)];
		ShuffledPtr->elements[++(ShuffledPtr->rear_ptr)] = cards;
		
		printf("%c ", ShuffledPtr->elements[++(ShuffledPtr->front_ptr)]);
		fprintf(wrFile, "%c ", ShuffledPtr->elements[ShuffledPtr->front_ptr]);
		i++;
	} 
	while (i < NO_OF_CARDS);
}

// A 2 3 4 5 6 7 8 9 0 J Q K 
// Q 2 3 A 5 6 J 8 9 4 7 K 0
/***** main() *****/
void main()
{
	int i, sequence_number = 0;
	char ch;

	MyQueue MyCardsQueue, ShuffledCardsQueue, *My_Q_Ptr, *Shuffled_Q_Ptr;

	My_Q_Ptr = &MyCardsQueue;
	Shuffled_Q_Ptr = &ShuffledCardsQueue;

	My_Q_Ptr->front_ptr = EMPTYQUEUE;						// initialize front & rear pointers
	My_Q_Ptr->rear_ptr = EMPTYQUEUE;							
	Shuffled_Q_Ptr->front_ptr = QUEUE_SIZE - 1;						
	Shuffled_Q_Ptr->rear_ptr = QUEUE_SIZE - 1;						

	// open file to write
	wrFile = fopen ("Cards_Sequence.txt", "w");
	if (wrFile == NULL)	printf("\n\nError opening writing file"); 

	// read from input file
	rdFile = fopen ("Cards_Input.txt", "r");
	if (rdFile == NULL)	printf("\n\nError opening reading file"); 
	else
	{
		printf("\n\n---------------------------- Next card sequence ----------------------------\n");
		fprintf(wrFile, "\n\n---------------------------- Next card sequence ----------------------------\n");
		do 
		{
			ch = fgetc(rdFile);								// read space and ignore
			
			if((ch >= 0 && ch <= 9) || (ch >= 11 && ch <= 32)) continue; // ignore space, carriage return, escape, etc from the ASCII table
			
			else if((ch >= 48 && ch <= 57) || ch=='A' || ch =='a' || ch =='J' || ch =='j' || ch =='Q' || ch =='q' || ch =='K' || ch =='k')
			{
				Insert(My_Q_Ptr, ch);						// Insert the card into the queue
				printf("\nOriginal queue ");
				fprintf(wrFile, "\nOriginal queue ");
				Print_Queue(My_Q_Ptr);						// print the current queue contents
			}
			else if(ch == 10)								// 'line feed' character
			{
				Shuffle_Cards(MyCardsQueue, &ShuffledCardsQueue);		// Pass original card queue copy & shuffled queue address
				
				printf("\nAfter shuffling, Shuffled queue ");
				fprintf(wrFile, "\nAfter shuffling, Shuffled queue ");
				Print_Queue(Shuffled_Q_Ptr);							// print the queue contents

				Play_Cards(Shuffled_Q_Ptr);								// remove top card put at bottom show next top card...
				
				printf("\n\n---------------------------- Next card sequence ----------------------------\n");
				fprintf(wrFile, "\n\n---------------------------- Next card sequence ----------------------------\n");

				My_Q_Ptr->front_ptr = EMPTYQUEUE;						// initialize front & rear pointers
				My_Q_Ptr->rear_ptr = EMPTYQUEUE;							
				Shuffled_Q_Ptr->front_ptr = QUEUE_SIZE - 1;						
				Shuffled_Q_Ptr->rear_ptr = QUEUE_SIZE - 1;						
			}
			else
			{}
		} 
		while (ch != EOF);									// read until end of file is reached
	}
	
	fclose (rdFile);										// close the read file
	fclose (wrFile);										// close the write file
		
	printf("\nPress any key and hit [Enter] to exit: ");
	scanf("%d", &i);
	return;
}